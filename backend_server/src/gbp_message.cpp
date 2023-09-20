#include "gbp_message.hpp"

/**
 * @func: construct UConnect object according to truck num
 * @param: {truck_num}total truck number
 * @return: a unique pointer to hold UConnect 
 */
std::unique_ptr<UConnect> gbp_message::construct_UConnect(int truck_num, int worldid) {
  std::unique_ptr<UConnect> uconnect_ptr(new UConnect());
  if (worldid == -1) {
    for (int i = 0; i < truck_num; i++) {
      UInitTruck * truck = uconnect_ptr->add_trucks();
      truck->set_id(i);
      truck->set_x(i);
      truck->set_y(i);
    }
  }
  else if (worldid != -1) {
    uconnect_ptr->set_worldid(worldid);
  }
  uconnect_ptr->set_isamazon(false);
  debug_print("constructed: " + uconnect_ptr->DebugString());
  return uconnect_ptr;
}

/**
 * @func: Construct GoPickup message
 * @param: {int truck_id, int whid, int seqnum} Required fields received from amazon
 * @return: Unique Pointer to Allocated UGoPickup message
 */
std::unique_ptr<UGoPickup> gbp_message::construct_UGoPickup(int truck_id,
                                                            int whid,
                                                            int seqnum) {
  std::unique_ptr<UGoPickup> pickup_ptr(new UGoPickup());
  pickup_ptr->set_seqnum(seqnum);
  pickup_ptr->set_truckid(truck_id);
  pickup_ptr->set_whid(whid);
  debug_print("constructed: " + pickup_ptr->DebugString());
  return pickup_ptr;
}

/**
 * @func: Construct UGoDeliver message
 * @param: {int package_id,
              int truck_id,
              int dest_x,
              int dest_y,
              int seqnum}  
 * @return: {std::unique_ptr<UGoDeliver> gbp_message} 
 */
std::unique_ptr<UGoDeliver> gbp_message::construct_UGoDeliver(
    const std::vector<int> & package_ids,
    int truck_id,
    const std::vector<int> & dest_xs,
    const std::vector<int> & dest_ys,
    int seqnum) {
  std::unique_ptr<UGoDeliver> deliver_ptr(new UGoDeliver());
  deliver_ptr->set_seqnum(seqnum);
  deliver_ptr->set_truckid(truck_id);
  for (size_t i = 0; i < package_ids.size(); i++) {
    UDeliveryLocation * dest = deliver_ptr->add_packages();
    dest->set_packageid(package_ids[i]);
    dest->set_x(dest_xs[i]);
    dest->set_y(dest_ys[i]);
  }
  debug_print("constructed: " + deliver_ptr->DebugString());
  return deliver_ptr;
}

/**
 * @func: Generate UQuery message
 * @param: {x`}  
 * @return: {} 
 */
std::unique_ptr<UQuery> gbp_message::construct_UQuery(int truckid, int seqnum) {
  std::unique_ptr<UQuery> query_ptr(new UQuery());
  query_ptr->set_seqnum(seqnum);
  query_ptr->set_truckid(truckid);
  return query_ptr;
}

/**
 * @func: Construct the UCommands message
 * @param: {UGoPickup * pickup, UGoDeliver * delivery} The world socket;
 * pointer to pickup object; pointer to delivery obejct;(They can be NULL)
 * @return: unique pointer hold the UCommands
 */
std::unique_ptr<UCommands> gbp_message::construct_UCommands(UGoPickup * pickup,
                                                            UGoDeliver * delivery,
                                                            UQuery * query) {
  std::unique_ptr<UCommands> commands_ptr(new UCommands());
  if (pickup) {
    commands_ptr->add_pickups()->CopyFrom(*pickup);
  }
  if (delivery) {
    commands_ptr->add_deliveries()->CopyFrom(*delivery);
  }
  if (query) {
    commands_ptr->add_queries()->CopyFrom(*query);
  }
  debug_print("constructed: " + commands_ptr->DebugString());
  return commands_ptr;
}

//Message sent to Amazon

std::unique_ptr<UTAConnect> gbp_message::construct_UTAConnect(int worldid) {
  std::unique_ptr<UTAConnect> connect_ptr(new UTAConnect());
  connect_ptr->set_worldid(worldid);
  return connect_ptr;
}

std::unique_ptr<UTAArrived> gbp_message::construct_UTAArrived(
    const std::vector<int> & packageids,
    int truckid,
    int whid,
    int seqnum) {
  std::unique_ptr<UTAArrived> arrive_ptr(new UTAArrived());
  for (size_t i = 0; i < packageids.size(); i++) {
    arrive_ptr->add_packageid(packageids[i]);
  }
  arrive_ptr->set_seqnum(seqnum);
  arrive_ptr->set_truckid(truckid);
  arrive_ptr->set_whid(whid);
  return arrive_ptr;
}

std::unique_ptr<UTAOutDelivery> gbp_message::construct_UTAOutDelivery(int packageid,
                                                                      int x,
                                                                      int y,
                                                                      int seqnum) {
  std::unique_ptr<UTAOutDelivery> delivery_ptr(new UTAOutDelivery());
  delivery_ptr->set_packageid(packageid);
  delivery_ptr->set_x(x);
  delivery_ptr->set_y(y);
  delivery_ptr->set_seqnum(seqnum);
  return delivery_ptr;
}

std::unique_ptr<UTACommands> gbp_message::contruct_UTACommands(
    UTAArrived * arrived,
    UTAOutDelivery * outfordelivery,
    UTADelivered * delivered) {
  std::unique_ptr<UTACommands> commands_ptr(new UTACommands());
  if (arrived) {
    commands_ptr->add_arrive()->CopyFrom(*arrived);
  }
  if (outfordelivery) {
    commands_ptr->add_todeliver()->CopyFrom(*outfordelivery);
  }
  if (delivered) {
    commands_ptr->add_delivered()->CopyFrom(*delivered);
  }
  return commands_ptr;
}

std::unique_ptr<UCommands> gbp_message::construct_world_acks(int64_t ack) {
  std::unique_ptr<UCommands> commands_ptr(new UCommands());
  commands_ptr->add_acks(ack);
  return commands_ptr;
}

std::unique_ptr<UTACommands> gbp_message::construct_amazon_acks(int64_t ack) {
  std::unique_ptr<UTACommands> commands_ptr(new UTACommands());
  commands_ptr->add_acks(ack);
  return commands_ptr;
}
