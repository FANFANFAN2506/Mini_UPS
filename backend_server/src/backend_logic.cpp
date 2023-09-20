#include "backend_logic.hpp"
#define SLEEP_TIME 500
#define SIM_SPEED 500

void backend_logic::init_phase(Communicator & comm) {
  int64_t worldid = _connect_world(comm);
  Dbconnection db;
  db.droptable();
  for (size_t i = 0; i < TRUCK_NUM; i++) {
    db.add_truck(i, i, i);
  }
  comm.setWorldid(worldid);
  UCommands init_speed_com;
  init_speed_com.set_simspeed(SIM_SPEED);
  sendMesgTo(init_speed_com, comm.getWorldOut());
  _send_uta_connect(comm, worldid);
  debug_print("setup success");
}

int64_t backend_logic::_connect_world(Communicator & comm) {
  std::unique_ptr<UConnect> Uconnect_ptr =
      gbp_message::construct_UConnect(TRUCK_NUM, comm.getWorldid());
  UConnected connected;
  do {
    sendMesgTo(*Uconnect_ptr, comm.getWorldOut());
    recvMesgFrom(connected, comm.getWorldIn());
    debug_print(connected.DebugString());
  } while (connected.result() != "connected!");
  return connected.worldid();
}

void backend_logic::_send_uta_connect(Communicator & comm, int64_t worldid) {
  std::unique_ptr<UTAConnect> utac = gbp_message::construct_UTAConnect(worldid);
  AUConnected auc;
  sendMesgTo(*utac, comm.getAmazonOut());
  recvMesgFrom(auc, comm.getAmazonIn());
  if (auc.worldid() != worldid) {
    std::cout << "UPS expects worldid: " << worldid
              << "but Amazon sends: " << auc.worldid() << std::endl;
    throw my_exception("amazon bad setup");
  }
}

void backend_logic::operation_phase(Communicator & comm) {
  std::thread world_thread(_listen_from_world, std::ref(comm));
  std::thread amazon_thread(_listen_from_amazon, std::ref(comm));
  std::thread front_thread(_listen_from_frontend, std::ref(comm));
  world_thread.join();
  amazon_thread.join();
  front_thread.join();
}

void backend_logic::_listen_from_world(Communicator & comm) {
  while (true) {
    UResponses uresp;
    bool res = recvMesgFrom(uresp, comm.getWorldIn());
    debug_print("!!!!!!Receive from World" + uresp.DebugString());
    if (!res) {  //fail to recv message from world, reconnect
      _reconnect_world(comm);
      continue;
    }
    //acks
    for (int i = 0; i < uresp.acks_size(); i++) {
      int64_t ack = uresp.acks(i);
      comm.add_world_ack(ack);
    }
    //UFinished
    for (int i = 0; i < uresp.completions_size(); i++) {
      UFinished ufinished = uresp.completions(i);
      std::thread t(_handleUFinished, std::ref(comm), ufinished);
      t.detach();
    }
    //UDeliveryMade
    for (int i = 0; i < uresp.delivered_size(); i++) {
      UDeliveryMade delivered = uresp.delivered(i);
      std::thread t(_handleUDeliveryMade, std::ref(comm), delivered);
      t.detach();
    }
    //finish TODO
    //truckstatus TODO
    //error
    for (int i = 0; i < uresp.error_size(); i++) {
      UErr error = uresp.error(i);
      int64_t err_seq = error.seqnum();
      _send_world_ack(comm, err_seq);
      if (comm.check_world_duplicate(err_seq)) {
        continue;
      }
      else {
        comm.record_world_seq(err_seq);
        std::cout << "ERROR!!!!!!!" << std::endl << error.DebugString() << std::endl;
      }
    }
  }
}

void backend_logic::_listen_from_amazon(Communicator & comm) {
  while (true) {
    ATUCommands atucommands;
    bool res = recvMesgFrom(atucommands, comm.getAmazonIn());
    debug_print("!!!!!Receive from amazon " + atucommands.DebugString());
    if (!res) {
      throw my_exception("Fail to recv commands from amazon");
    }
    //ATURequestPickUp
    for (int i = 0; i < atucommands.topickup_size(); i++) {
      ATURequestPickUp topickup = atucommands.topickup(i);
      std::thread t(_handleATURequestPickUp, std::ref(comm), topickup);
      t.detach();
    }
    //ATULoaded
    for (int i = 0; i < atucommands.loaded_size(); i++) {
      ATULoaded loaded = atucommands.loaded(i);
      std::thread t(_handleATULoaded, std::ref(comm), loaded);
      t.detach();
    }
    //AUErr
    for (int i = 0; i < atucommands.err_size(); i++) {
      AUErr err = atucommands.err(i);
      int64_t err_seq = err.seqnum();
      _send_amazon_ack(comm, err_seq);
      if (comm.check_amazon_duplicate(err_seq)) {
        continue;
      }
      else {
        comm.record_amazon_seq(err_seq);
        std::cout << "ERROR!!!!!!!" << std::endl << err.DebugString() << std::endl;
      }
    }
    //acks
    for (int i = 0; i < atucommands.acks_size(); i++) {
      int64_t ack = atucommands.acks(i);
      comm.add_amazon_ack(ack);
    }
  }
}

void backend_logic::_listen_from_frontend(Communicator & comm) {
  while (true) {
    int front_fd = comm.front_accept();
    std::thread t(_change_address, front_fd);
    t.detach();
  }
}

void backend_logic::_change_address(int front_fd) {
  char buff[1024];
  int n = recv(front_fd, buff, sizeof(buff), 0);
  std::string json_str(buff, n);
  nlohmann::json json_obj = nlohmann::json::parse(json_str);
  std::string package_id = json_obj["id"];
  std::string x = json_obj["x"];
  std::string y = json_obj["y"];
  debug_print("recv json with packageid: " + package_id + " x: " + x + " y: " + y);
  //db
  close(front_fd);
}

void backend_logic::_handleATURequestPickUp(Communicator & comm,
                                            ATURequestPickUp topickup) {
  int64_t a_seq = topickup.seqnum();
  _send_amazon_ack(comm, a_seq);
  if (comm.check_amazon_duplicate(a_seq)) {
    return;
  }
  else {
    comm.record_amazon_seq(a_seq);
  }
  Dbconnection db;
  int64_t whid = topickup.whid();
  int truckid = db.add_new_order(topickup.packageid(),
                                 topickup.product_name(),
                                 topickup.has_ups_account() ? topickup.ups_account() : "",
                                 whid,
                                 topickup.destination().x(),
                                 topickup.destination().y());
  if (truckid == -1) {
    return;
  }
  int seqnum = comm.get_and_increase_seqnum();
  std::unique_ptr<UGoPickup> pickup =
      gbp_message::construct_UGoPickup(truckid, whid, seqnum);
  std::unique_ptr<UCommands> commands =
      gbp_message::construct_UCommands(pickup.get(), NULL, NULL);
  do {
    sendMesgTo(*commands, comm.getWorldOut());
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
  } while (!comm.check_world_ack_recved(seqnum));
  debug_print("!!!!!UGo Pickup ucommands to world" + commands->DebugString());
}

void backend_logic::_handleATULoaded(Communicator & comm, ATULoaded loaded) {
  int64_t a_seq = loaded.seqnum();
  _send_amazon_ack(comm, a_seq);
  if (comm.check_amazon_duplicate(a_seq)) {
    return;
  }
  else {
    comm.record_amazon_seq(a_seq);
  }
  std::vector<int> package_ids;
  std::vector<int> dest_xs;
  std::vector<int> dest_ys;
  int truckid = loaded.truckid();
  int seqnum = comm.get_and_increase_seqnum();
  Dbconnection db;
  db.after_loaded(truckid, package_ids, dest_xs, dest_ys);
  std::unique_ptr<UGoDeliver> delivery =
      gbp_message::construct_UGoDeliver(package_ids, truckid, dest_xs, dest_ys, seqnum);
  std::unique_ptr<UCommands> command =
      gbp_message::construct_UCommands(NULL, delivery.get(), NULL);
  _send_out_delivery(comm, package_ids, dest_xs, dest_ys);
  do {
    sendMesgTo(*command, comm.getWorldOut());
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
  } while (!comm.check_world_ack_recved(seqnum));
  debug_print("!!!!Send out UGoDeliver to World" + command->DebugString());
  //sendOUTDelivery
  db.ack_Godelivery(truckid);
}

void backend_logic::_send_out_delivery(Communicator & comm,
                                       const std::vector<int> & package_ids,
                                       const std::vector<int> & xs,
                                       const std::vector<int> & ys) {
  for (size_t i = 0; i < package_ids.size(); i++) {
    int package_id = package_ids[i];
    int x = xs[i];
    int y = ys[i];
    int seqnum = comm.get_and_increase_seqnum();
    std::unique_ptr<UTAOutDelivery> utao =
        gbp_message::construct_UTAOutDelivery(package_id, x, y, seqnum);
    std::unique_ptr<UTACommands> command =
        gbp_message::contruct_UTACommands(NULL, utao.get(), NULL);
    do {
      sendMesgTo(*command, comm.getAmazonOut());
      std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    } while (!comm.check_amazon_ack_recved(seqnum));
    debug_print("!!!!Send Outfor Delivery to Amazon" + command->DebugString());
  }
}

void backend_logic::_handleUFinished(Communicator & comm, UFinished ufinished) {
  int64_t seqnum = ufinished.seqnum();
  _send_world_ack(comm, seqnum);
  if (comm.check_world_duplicate(seqnum)) {
    return;
  }
  else {
    comm.record_world_seq(seqnum);
  }
  std::string status = ufinished.status();
  int32_t truckid = ufinished.truckid();
  int32_t t_location_x = ufinished.x();
  int32_t t_location_y = ufinished.y();
  if (status == "ARRIVE WAREHOUSE") {
    //send UTAArrived
    std::vector<int> packageids;
    int whid = -1;
    int64_t my_seq = comm.get_and_increase_seqnum();
    Dbconnection db;
    db.after_arrive(truckid, packageids, whid, t_location_x, t_location_y);
    std::unique_ptr<UTAArrived> utaa =
        gbp_message::construct_UTAArrived(packageids, truckid, whid, my_seq);
    _send_uta_arrived(comm, *utaa, my_seq);
    debug_print("!!!!send UTAarrived to AMazon" + utaa->DebugString());
  }
  else if (status == "idle") {
    return;
  }
}

void backend_logic::_send_uta_arrived(Communicator & comm,
                                      UTAArrived & utaa,
                                      int64_t seqnum) {
  std::unique_ptr<UTACommands> commands =
      gbp_message::contruct_UTACommands(&utaa, NULL, NULL);
  do {
    sendMesgTo(*commands, comm.getAmazonOut());
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
  } while (!comm.check_amazon_ack_recved(seqnum));
}

void backend_logic::_handleUDeliveryMade(Communicator & comm, UDeliveryMade delivered) {
  int64_t seqnum = delivered.seqnum();
  _send_world_ack(comm, seqnum);
  if (comm.check_world_duplicate(seqnum)) {
    return;
  }
  else {
    comm.record_world_seq(seqnum);
  }
  //  int32_t truckid = delivered.truckid();
  int64_t packageid = delivered.packageid();
  Dbconnection db;
  db.after_delivered(packageid);
  _send_uta_delivered(comm, packageid);
}

void backend_logic::_send_uta_delivered(Communicator & comm, int64_t packageid) {
  int64_t my_seq = comm.get_and_increase_seqnum();
  std::unique_ptr<UTADelivered> tuad =
      gbp_message::construct_Delivery<UTADelivered>(packageid, my_seq);
  std::unique_ptr<UTACommands> command =
      gbp_message::contruct_UTACommands(NULL, NULL, tuad.get());
  do {
    sendMesgTo(*command, comm.getAmazonOut());
    debug_print("Waiting for ack " + std::to_string(my_seq));
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
  } while (!comm.check_amazon_ack_recved(my_seq));
  debug_print("!!!!!Send UTADelivered to Amazon" + command->DebugString());
}

void backend_logic::_send_world_ack(Communicator & comm, int64_t ack) {
  std::unique_ptr<UCommands> ack_commands = gbp_message::construct_world_acks(ack);
  sendMesgTo(*ack_commands, comm.getWorldOut());
}

void backend_logic::_send_amazon_ack(Communicator & comm, int64_t ack) {
  std::unique_ptr<UTACommands> ack_commands = gbp_message::construct_amazon_acks(ack);
  sendMesgTo(*ack_commands, comm.getAmazonOut());
}

void backend_logic::_reconnect_world(Communicator & comm) {
  comm.connect_to_world();
  _connect_world(comm);
}
