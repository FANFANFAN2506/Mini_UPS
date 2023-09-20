#ifndef COMM
#define COMM
#define UPS_WORLD_PORT "12345"
#define LISTEN_AMAZON_PORT "32345"
#define LISTEN_FRONTEND_PORT "42345"
#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_set>

#include "my_exception.hpp"
#include "send_recv.hpp"
#include "seqnum_cache.hpp"
#include "socket.hpp"
#include "utils.hpp"

class Communicator {
 private:
  std::string world_hostname;
  google::protobuf::io::FileOutputStream * world_out;
  google::protobuf::io::FileInputStream * world_in;
  google::protobuf::io::FileOutputStream * amazon_out;
  google::protobuf::io::FileInputStream * amazon_in;
  int amazon_listen_fd;
  int front_listen_fd;
  std::atomic<int64_t> seqnum;
  std::unordered_set<int64_t> world_acks;
  std::unordered_set<int64_t> amazon_acks;
  seqnum_cache world_seqs;   //to check if duplicate package
  seqnum_cache amazon_seqs;  //to check if duplicate package
  std::mutex mtx;
  int64_t worldid;

  void listen_amazon_connection() {
    debug_print("Try to connect with amazon");
    this->amazon_listen_fd = my_socket::create_tcp_listener_fd(LISTEN_AMAZON_PORT);
    if (this->amazon_listen_fd == -1) {
      throw my_exception("Create listening port with amazon failed");
    }
    std::string amazon_ip;
    int amazon_fd = my_socket::accpect_connection(amazon_listen_fd, amazon_ip);
    debug_print("accept connection from amazon with ip:" + amazon_ip);
    this->amazon_out = new google::protobuf::io::FileOutputStream(amazon_fd);
    this->amazon_in = new google::protobuf::io::FileInputStream(amazon_fd);
  }

  void listen_front_connection() {
    this->front_listen_fd = my_socket::create_tcp_listener_fd(LISTEN_FRONTEND_PORT);
    if (this->front_listen_fd == -1) {
      throw my_exception("Create listening port with frontend failed");
    }
    debug_print("create listening port for frontend succeeds");
  }

 public:
  Communicator(std::string world_hostname) :
      world_hostname(world_hostname),
      world_out(NULL),
      world_in(NULL),
      amazon_out(NULL),
      amazon_in(NULL),
      seqnum(0),
      world_seqs(200),
      amazon_seqs(200),
      worldid(-1) {
    std::thread t1(&Communicator::listen_front_connection, this);
    std::thread t2(&Communicator::listen_amazon_connection, this);
    std::thread t3(&Communicator::connect_to_world, this);
    t1.join();
    t2.join();
    t3.join();
    debug_print("Communicator setup");
  }

  void connect_to_world() {
    int world_fd = my_socket::connect_to_host(world_hostname.c_str(), UPS_WORLD_PORT);
    if (world_fd == -1) {
      throw my_exception("Cannot establish connection with world server");
    }
    delete this->world_out;
    delete this->world_in;
    this->world_out = new google::protobuf::io::FileOutputStream(world_fd);
    this->world_in = new google::protobuf::io::FileInputStream(world_fd);
    debug_print("connect to world");
  }

  google::protobuf::io::FileOutputStream * getWorldOut() { return world_out; }
  google::protobuf::io::FileOutputStream * getAmazonOut() { return amazon_out; }
  google::protobuf::io::FileInputStream * getWorldIn() { return world_in; }
  google::protobuf::io::FileInputStream * getAmazonIn() { return amazon_in; }

  //add 1, return the value before added
  int64_t get_and_increase_seqnum() {
    return seqnum.fetch_add(1, std::memory_order_seq_cst);
  }

  bool check_world_ack_recved(int64_t my_seqnum) {
    std::lock_guard<std::mutex> lg(mtx);
    if (world_acks.count(my_seqnum) == 1) {
      world_acks.erase(my_seqnum);
      return true;
    }
    return false;
  }

  bool check_amazon_ack_recved(int64_t my_seqnum) {
    std::lock_guard<std::mutex> lg(mtx);
    if (amazon_acks.count(my_seqnum) == 1) {
      amazon_acks.erase(my_seqnum);
      return true;
    }
    return false;
  }

  void add_world_ack(int64_t ack) {
    std::lock_guard<std::mutex> lg(mtx);
    world_acks.emplace(ack);
  }

  void add_amazon_ack(int64_t ack) {
    std::lock_guard<std::mutex> lg(mtx);
    amazon_acks.emplace(ack);
  }

  bool check_world_duplicate(int64_t seq) {
    std::lock_guard<std::mutex> lg(mtx);
    return world_seqs.contains(seq);
  }

  bool check_amazon_duplicate(int64_t seq) {
    std::lock_guard<std::mutex> lg(mtx);
    return amazon_seqs.contains(seq);
  }

  void record_world_seq(int64_t seq) { world_seqs.add(seq); }

  void record_amazon_seq(int64_t seq) { amazon_seqs.add(seq); }

  int64_t getWorldid() const { return this->worldid; }

  void setWorldid(int64_t worldid) { this->worldid = worldid; }

  int front_accept() {
    std::string front_ip;
    int front_fd = my_socket::accpect_connection(front_listen_fd, front_ip);
    debug_print("accept connection from front end with ip:" + front_ip);
    return front_fd;
  }

  ~Communicator() {
    delete world_out;
    delete world_in;
    delete amazon_out;
    delete amazon_in;
    close(amazon_listen_fd);
    close(front_listen_fd);
  }
};
#endif
