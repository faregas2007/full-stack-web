#pragma once 

#include "protos/database_config.pb.h"
#include "absl/status/status.h"
#include "mysql/mysql.h"

using absl::Status; 

class database_access_object {
	private:
	  MYSQL *db_ = nullptr;
	  MYSQL_RES *result_set_ = nullptr;
	  std::string db_name_;
	  const database_config config_;

	  bool skip_db_creation_ = false;
	  bool is_connected_ = false;

	  void connect_impl();
	  void close_impl();

	  void DiscardResultSet();
	  void run_query(const std::string query);
	public:
	  database_access_object();
	  database_access_object(const database_config& config); 
	  ~database_access_object();

	  Status connect();
	  Status close();
};

namespace full_stack_web {
  class database_access_object;
}

