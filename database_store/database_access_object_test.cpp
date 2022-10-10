#include <glog/logging.h>
#include "protos/database_config.pb.h"
#include "database_access_object.h"
#include "gflags/gflags.h"
#include "mysql/mysql.h"


//DEFINE_string(host, "localhost", "host");
//DEFINE_string(user, "nguyen", "user name");
//DEFINE_string(passwd, "", "password");
//DEFINE_string(db, "", "name of database");
//DEFINE_int32(port, 0, "listening port");
//DEFINE_string(socket, "", "socket or TCP/IP protocol");
//DEFINE_bool(skip_db_creation, false, " skip database creation");

// include gtest latter
// issue with authorication with mysql server 
int main() {
  full_stack_web :: database_config config; 
  //config.set_host(FLAGS_host);
  //config.set_user(FLAGS_user);
  //config.set_passwd(FLAGS_passwd);
  //config.set_db(FLAGS_db);
  //config.set_port(FLAGS_port);
  //config.set_socket(FLAGS_socket);
  //config.set_skip_db_creation(FLAGS_skip_db_creation);
  //gflags :: ParseCommandLineFlags(&argc, &argv, true); 
  config.set_host("localhost");
  config.set_user("nguyen");
  config.set_passwd("");
  config.set_db("mysql_db_test");
  config.set_port(0);
  config.set_socket("");
  config.set_skip_db_creation(false);
  
  full_stack_web :: database_access_object dao;
  dao.connect();
  return 0;
}
