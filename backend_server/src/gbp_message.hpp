#include <memory>
#include <string>
#include <vector>

#include "uta.pb.h"
#include "utils.hpp"
#include "world.pb.h"

namespace gbp_message {
  //Message send to World
  std::unique_ptr<UConnect> construct_UConnect(int truck_num, int worldid = -1);
  std::unique_ptr<UGoPickup> construct_UGoPickup(int truck_id, int whid, int seqnum);
  std::unique_ptr<UGoDeliver> construct_UGoDeliver(const std::vector<int> & package_ids,
                                                   int truck_id,
                                                   const std::vector<int> & dest_xs,
                                                   const std::vector<int> & dest_ys,
                                                   int seqnum);
  std::unique_ptr<UQuery> construct_UQuery(int truckid, int seqnum);
  std::unique_ptr<UCommands> construct_UCommands(UGoPickup * pickup,
                                                 UGoDeliver * delivery,
                                                 UQuery * query);

  //Message send to Amazon
  std::unique_ptr<UTAConnect> construct_UTAConnect(int worldid);
  std::unique_ptr<UTAArrived> construct_UTAArrived(const std::vector<int> & packageids,
                                                   int truckid,
                                                   int whid,
                                                   int seqnum);
  template<typename T>
  std::unique_ptr<T> construct_Delivery(int packageid, int seqnum) {
    std::unique_ptr<T> delivery_ptr(new T());
    delivery_ptr->set_packageid(packageid);
    delivery_ptr->set_seqnum(seqnum);
    return delivery_ptr;
  }
  std::unique_ptr<UTAOutDelivery> construct_UTAOutDelivery(int packageid,
                                                           int x,
                                                           int y,
                                                           int seqnum);
  std::unique_ptr<UTACommands> contruct_UTACommands(UTAArrived * arrived,
                                                    UTAOutDelivery * outfordelivery,
                                                    UTADelivered * delivered);
  std::unique_ptr<UCommands> construct_world_acks(int64_t ack);
  std::unique_ptr<UTACommands> construct_amazon_acks(int64_t ack);
}  // namespace gbp_message
