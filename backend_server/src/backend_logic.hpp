#include <chrono>
#include <thread>

#include "Communicator.hpp"
#include "dbConnect.hpp"
#include "gbp_message.hpp"
#include "json.hpp"
#include "send_recv.hpp"
#include "utils.hpp"

#define TRUCK_NUM 10

namespace backend_logic {
  void init_phase(Communicator & comm);
  int64_t _connect_world(Communicator & comm);
  void _send_uta_connect(Communicator & comm, int64_t worldid);
  void operation_phase(Communicator & comm);
  void _listen_from_world(Communicator & comm);
  void _listen_from_amazon(Communicator & comm);
  void _listen_from_frontend(Communicator & comm);
  void _reconnect_world(Communicator & comm);
  void _handleUFinished(Communicator & comm, UFinished ufinished);
  void _send_world_ack(Communicator & comm, int64_t ack);
  void _handleUDeliveryMade(Communicator & comm, UDeliveryMade delivered);
  void _send_uta_delivered(Communicator & comm, int64_t packageid);
  void _handleATURequestPickUp(Communicator & comm, ATURequestPickUp topickup);
  void _handleATULoaded(Communicator & comm, ATULoaded loaded);
  void _send_amazon_ack(Communicator & comm, int64_t ack);
  void _send_out_delivery(Communicator & comm,
                          const std::vector<int> & package_ids,
                          const std::vector<int> & x,
                          const std::vector<int> & y);
  void _send_uta_arrived(Communicator & comm, UTAArrived & utaa, int64_t seqnum);
  void _change_address(int front_fd);
}  // namespace backend_logic
