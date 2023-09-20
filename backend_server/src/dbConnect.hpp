#include <chrono>
#include <iostream>
#include <mutex>
#include <pqxx/pqxx>
#include <string>
#include <thread>

class Dbconnection {
 private:
  pqxx::connection * C;

  pqxx::connection * connectTodb();
  //utils:
  std::string sanitize_string(std::string & in);
  void executeSQL(std::string & sql);
  void querySQL(std::string & sql, pqxx::result & R);
  void add_shipment(int PackageId,
                    std::string PackageName,
                    std::string UpsAccount,
                    int whid,
                    int dest_x,
                    int dest_y);
  void update_shipment_status(int shipment_id, std::string new_status);
  void update_truck_status(int truck_id, std::string new_status);
  void update_truck_whid(int truck_id, int whid);
  int find_available_truck(int & whid, int PackageId);
  void non_trans_table(std::string & sql);
  void execute_querySQL(std::string & sql, pqxx::result & R);

 public:
  Dbconnection() { C = connectTodb(); }
  ~Dbconnection() { delete C; }
  void add_truck(int truck_id, int x, int y);
  int add_new_order(int PackageId,
                    std::string PackageName,
                    std::string UpsAccount,
                    int whid,
                    int dest_x,
                    int dest_y);
  void after_arrive(int truck_id,
                    std::vector<int> & pacakgeid_arr,
                    int & whid,
                    int x,
                    int y);
  void after_loaded(int truck_id,
                    std::vector<int> & packageid,
                    std::vector<int> & x,
                    std::vector<int> & y);
  void ack_Godelivery(int truck_id);
  void after_delivered(int packageid);
  bool update_position(int packageid, int x, int y);
  void update_truck_position(int truck_id, int x, int y);
  //For debugging
  void droptable();
  void printdb();
};

// pqxx::connection * connectTodb();

void update_status(pqxx::connection * C, int package_id, std::string new_status);
