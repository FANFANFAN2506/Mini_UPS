#include "dbConnect.hpp"
static std::mutex dblock;
//Private methods:

/**
 * @func: Connect to the destination database
 * @param: {void}  
 * @return: {pqxx::connection *} a pointer to the connection with the database
 */
pqxx::connection * Dbconnection::connectTodb() {
  pqxx::connection * C;
  try {
    C = new pqxx::connection("dbname=upsdb user=postgres password=passw0rd");
    if (C->is_open()) {
      // std::cout << "Connected to databse!" << C->dbname() << std::endl;
    }
    else {
      std::cout << "Cannot connect to database" << std::endl;
      return NULL;
    }
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << std::endl;
    return NULL;
  }
  return C;
}

/**
 * @func: Sanitize the input string
 * @param: {std::string & in} input string to be sanitized
 * @return: {std::string}  output cleaned string 
 */
std::string Dbconnection::sanitize_string(std::string & in) {
  pqxx::nontransaction N(*C);
  return N.esc(in);
}

/**
 * @func: Construct a work class to do execute transaction
 * @param: {std::string sql}  Given sql sentence to be executed
 * @return: {void} 
 */
void Dbconnection::executeSQL(std::string & sql) {
  try {
    pqxx::work W(*C);
    W.exec(sql);
    W.commit();
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
}

void Dbconnection::execute_querySQL(std::string & sql, pqxx::result & R) {
  try {
    pqxx::work W(*C);
    R = W.exec(sql);
    W.commit();
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
}

/**
 * @func: Query the SQL write the result into the given R
 * @param: {std::string & sql, pqxx::result & R} Given sql and result to be updated
 * @return: {void} 
 */
void Dbconnection::querySQL(std::string & sql, pqxx::result & R) {
  pqxx::nontransaction N(*C);
  R = N.exec(sql);
  // std::cout << sql << std::endl;
}

/**
 * @func: Add a new shipment to the database
 * @param: {int PackageId  : package id
            std::string PackageName : package name
            std::string UpsAccount: Ups account(if null, pass in {std::string("")})
            int whid: warehouse id
            int dest_x: destination x
            int dest_y: destination y}  
 * e.g add_shipment(C, 2, std::string("RX6095XT"), std::string(""), 1, 10, 10, 2);
 * @return: {void} 
 */
void Dbconnection::add_shipment(int PackageId,
                                std::string PackageName,
                                std::string UpsAccount,
                                int whid,
                                int dest_x,
                                int dest_y) {
  std::string find_user =
      "SELECT username FROM auth_user WHERE username = '" + UpsAccount + "';";
  pqxx::result R;
  querySQL(find_user, R);
  if (R.size() == 0) {
    UpsAccount = "";
  }
  std::string sql;
  sql = "INSERT INTO upsapp_shipment(packageid, packagename, whid, dest_x, dest_y, "
        "status,upsaccount_id) VALUES (" +
        std::to_string(PackageId) + ", '" + sanitize_string(PackageName) + "', ";
  sql += std::to_string(whid) + ", " + std::to_string(dest_x) + ", " +
         std::to_string(dest_y) + ", 'picking', ";
  if (UpsAccount.size() != 0) {
    sql += "'" + sanitize_string(UpsAccount) + "');";
  }
  else {
    sql += "NULL);";
  }
  executeSQL(sql);
}

/**
 * @func: Update the shipment status
 * @param: {int id, std::string new_status}package id to be changed, new_status string
  *       ('picking'),
          ('loading'),
          ('delivering'),
          ('arrived')
 * @return: {void} 
 */
void Dbconnection::update_shipment_status(int shipment_id, std::string new_status) {
  std::string sql;
  sql = "UPDATE upsapp_shipment SET status = '" + new_status +
        "' WHERE packageid = " + std::to_string(shipment_id) + ";";
  executeSQL(sql);
}

/**
 * @func: Update the truck status
 * @param: {int truck_id,, std::string new_status}truck id to be changed, new_status string
        ('idle'),
        ('traveling'),
        ('arrivewarehouse'),
        ('delivering')
 * @return: {void} 
 */
void Dbconnection::update_truck_status(int truck_id, std::string new_status) {
  std::string sql;
  sql = "UPDATE upsapp_truck SET status = '" + new_status +
        "' WHERE truckid = " + std::to_string(truck_id) + ";";
  executeSQL(sql);
}

/**
 * @func: Update the truck warehouseid
 * @param: {int truck_id, int whid}truck id to be changed, new whid
 * if whid<0, set it to null, else set it to the value given
 * @return: {void} 
 */
void Dbconnection::update_truck_whid(int truck_id, int whid) {
  std::string sql;
  if (whid >= 0) {
    sql = "UPDATE upsapp_truck SET whid = '" + std::to_string(whid) +
          "' WHERE truckid = " + std::to_string(truck_id) + ";";
  }
  else {
    sql = "UPDATE upsapp_truck SET whid = NULL WHERE truckid = " +
          std::to_string(truck_id) + ";";
  }

  executeSQL(sql);
}

void Dbconnection::update_truck_position(int truck_id, int x, int y) {
  std::string sql =
      "UPDATE upsapp_truck SET loca_x = " + std::to_string(x) +
      ", loca_y = " + std::to_string(y) +
      " WHERE truckid IN (SELECT truckid FROM upsapp_truck WHERE truckid =" +
      std::to_string(truck_id) + ");";
  std::cout << sql << std::endl;
  executeSQL(sql);
}

/**
 * @func: Find idle and delivering trucks, might be waiting for a truck
 * @param: {void}  
 * @return: {int} available truck id
 */
int Dbconnection::find_available_truck(int & whid, int PackageId) {
  std::string sql =
      "UPDATE upsapp_truck SET whid = " + std::to_string(whid) +
      ", status = 'traveling' WHERE truckid IN (SELECT "
      "truckid FROM upsapp_truck WHERE status = 'idle' OR status = "
      "'delivering' ORDER BY status DESC LIMIT 1 FOR UPDATE) RETURNING truckid;";
  pqxx::result available_truck;
  do {
    execute_querySQL(sql, available_truck);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  } while (available_truck.size() == 0);
  return available_truck[0][0].as<int>();
}

/**
 * @func: The method to execute the non-transaction sql (e.q query)
 * @param: {pqxx::connection * C, std::string & sql} connection pointer and the sql to be executed  
 * @return: {void} 
 */
void Dbconnection::non_trans_table(std::string & sql) {
  pqxx::nontransaction N(*C);
  pqxx::result R(N.exec(sql));
  int r_num = R.columns();
  std::cout << R.column_name(0);
  for (int i = 1; i < r_num; i++) {
    std::cout << " " << R.column_name(i);
  }
  std::cout << std::endl;
  for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
    for (int i = 0; i < r_num; i++) {
      if (!c[i].is_null()) {
        std::cout << c[i].as<std::string>();
      }
      else {
        std::cout << "null";
      }
      if (i == r_num - 1) {
        std::cout << std::endl;
      }
      else {
        std::cout << " ";
      }
    }
  }
}

//Public methods:

/**
 * @func: Add a truck to db
 * @param: {int truck_id, int x, int y} The truck_id, and its x and y coordination 
 * @return: {void } 
 */
void Dbconnection::add_truck(int truck_id, int x, int y) {
  std::string sql;
  sql = "INSERT INTO upsapp_truck(truckid, status, loca_x, loca_y) VALUES (" +
        std::to_string(truck_id) + ", 'idle', " + std::to_string(x) + ", " +
        std::to_string(y) + ");";
  executeSQL(sql);
}

/**
 * @func: If return -1, then no need to send GoPickup, else Send GoPickup with the returned truckid
 * @param: {int PackageId,
            std::string PackageName,
            std::string UpsAccount,
            int whid,
            int dest_x,
            int dest_y}  
 * @return: {int} available truckid
 */
int Dbconnection::add_new_order(int PackageId,
                                std::string PackageName,
                                std::string UpsAccount,
                                int whid,
                                int dest_x,
                                int dest_y) {
  std::lock_guard<std::mutex> lg(dblock);
  add_shipment(PackageId, PackageName, UpsAccount, whid, dest_x, dest_y);
  std::string find_truck_sql = "SELECT truckid FROM upsapp_truck WHERE status = "
                               "'traveling' AND whid =" +
                               std::to_string(whid) + ";";
  pqxx::result traveling_truck;
  querySQL(find_truck_sql, traveling_truck);
  if (traveling_truck.size() == 0) {
    //No truck is traveling to the warehouse
    int truck_id = find_available_truck(whid, PackageId);
    return truck_id;
  }
  else {
    //There is one traveling to
    return -1;
  }
}

/**
 * @func: Return all packages and whid at the same warehouse as the given truck_id
 * @param: {int truck_id: The truck_id arrived at warehouse
            std::vector<int> & pacakgeid_arr: Empty packageid array to be filled
            int & whid} Empty whid to be filled   
 * @return: {void} 
 */
void Dbconnection::after_arrive(int truck_id,
                                std::vector<int> & packageid_arr,
                                int & whid,
                                int x,
                                int y) {
  //Cannot update two tables at the same time
  std::lock_guard<std::mutex> lg(dblock);
  update_truck_status(truck_id, "arrivewarehouse");
  update_truck_position(truck_id, x, y);
  std::string find_packages =
      "UPDATE upsapp_shipment SET truck_id = " + std::to_string(truck_id) +
      ", status = 'loading' WHERE packageid IN (SELECT upsapp_shipment.packageid"
      " FROM upsapp_shipment, upsapp_truck WHERE "
      "upsapp_truck.whid = upsapp_shipment.whid AND upsapp_truck.truckid=" +
      std::to_string(truck_id) +
      " AND upsapp_shipment.status = 'picking' FOR UPDATE) RETURNING "
      "upsapp_shipment.whid, "
      "upsapp_shipment.packageid;";
  pqxx::result packages;
  execute_querySQL(find_packages, packages);
  whid = packages[0][0].as<int>();
  for (pqxx::result::const_iterator c = packages.begin(); c != packages.end(); ++c) {
    packageid_arr.push_back(c[1].as<int>());
  }
}

void Dbconnection::after_loaded(int truck_id,
                                std::vector<int> & packageid_arr,
                                std::vector<int> & x,
                                std::vector<int> & y) {
  //Here we don't update the truck status to delivering also we don't remove the whid for truck yet
  //we do this when recv ack
  std::string find_packages = "UPDATE upsapp_shipment SET status = 'delivering' "
                              "WHERE packageid IN (SELECT "
                              "packageid FROM upsapp_shipment WHERE truck_id = " +
                              std::to_string(truck_id) +
                              " AND status = 'loading' FOR UPDATE) RETURNING "
                              "upsapp_shipment.packageid, dest_x, dest_y;";
  pqxx::result packages;
  execute_querySQL(find_packages, packages);
  for (pqxx::result::const_iterator c = packages.begin(); c != packages.end(); ++c) {
    std::string result = "package id" + std::to_string(c[0].as<int>()) + " x " +
                         std::to_string(c[1].as<int>()) + " y " +
                         std::to_string(c[2].as<int>());
    std::cout << result << std::endl;
    packageid_arr.push_back(c[0].as<int>());
    x.push_back(c[1].as<int>());
    y.push_back(c[2].as<int>());
  }
}

void Dbconnection::ack_Godelivery(int truck_id) {
  std::string update_truck =
      "UPDATE upsapp_truck SET status = 'delivering', whid = NULL WHERE truckid=" +
      std::to_string(truck_id) + ";";
  executeSQL(update_truck);
}

void Dbconnection::after_delivered(int packageid) {
  std::string update_shipment =
      "UPDATE upsapp_shipment SET status = 'arrived' WHERE packageid =" +
      std::to_string(packageid) + ";";
  executeSQL(update_shipment);
}

void Dbconnection::droptable() {
  std::string sql1 = "DELETE FROM upsapp_shipment;";
  std::string sql2 = "DELETE FROM upsapp_truck;";
  executeSQL(sql1);
  executeSQL(sql2);
  // std::cout << "delete all from tables" << std::endl;
}

bool Dbconnection::update_position(int packageid, int x, int y) {
  pqxx::result packages;
  std::string sql =
      "UPDATE upsapp_shipment SET dest_x = " + std::to_string(x) +
      ", dest_y = " + std::to_string(y) +
      " WHERE packageid IN (SELECT packageid FROM upsapp_shipment WHERE packageid =" +
      std::to_string(packageid) +
      " AND status <> 'delivering' AND status <> 'arrived') RETURNING packageid;";
  execute_querySQL(sql, packages);
  if (packages.size() == 0) {
    return false;
  }
  else {
    return true;
  }
}

/**
 * @func: Print the database shipment and truck
 * @param: {pqxx::connection * C} connection pointer
 * @return: {void} 
 */
void Dbconnection::printdb() {
  std::string sql1, sql2;
  sql1 = "SELECT * FROM upsapp_shipment;";
  sql2 = "SELECT * FROM upsapp_truck;";
  non_trans_table(sql1);
  non_trans_table(sql2);
}
