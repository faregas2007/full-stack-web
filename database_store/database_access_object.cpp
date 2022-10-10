#include <iostream>
#include <glog/logging.h>

#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "gflags/gflags.h"

#include "database_access_object.h"
#include "protos/database_config.pb.h"

namespace full_stack_web 
{
  Status CheckConfig(const database_config &config) {
	std::vector<std::string> config_errors;
	if (config.host().empty() == config.socket().empty()) {
	  config_errors.push_back("One host or socket must be specified.");
	}
	if(config.db().empty()) {
	  config_errors.push_back("database is empty. It must be specified.");
	}
	if (!config_errors.empty()) {
	  return absl::InvalidArgumentError(absl::StrJoin(config_errors, ":"));
	}
	return absl::OkStatus();
  }

  database_access_object :: database_access_object(const database_config &config) : config_(config) {
	CHECK_EQ(absl::OkStatus(), CheckConfig(config));
	std::cout <<"constructor " << std::endl;
  }

  database_access_object :: ~database_access_object() {
	CHECK_EQ(absl::OkStatus(), close());
	std::cout <<"destructor " << std::endl;
  }

  void database_access_object :: connect_impl() {
	db_ = mysql_init(db_);
	if(!db_){
	  LOG(ERROR) << "mysql_init error" << mysql_errno(db_) << ":" << mysql_error(db_);
	}
	
	// constructor issue. 
	db_ = mysql_real_connect(
	  db_,
	  config_.host().empty() ? nullptr : config_.host().c_str(),
	  config_.user().empty() ? nullptr : config_.user().c_str(),
	  config_.passwd().empty() ? nullptr : config_.passwd().c_str(),
	  /*db_name=*/nullptr,
	  config_.port(),
	  config_.socket().empty() ? nullptr : config_.socket().c_str(),
	  /*client_flags*/0UL);

	if (!db_) {
	  LOG(ERROR) << "MySQL database was not initialized" << mysql_errno(db_) << ":" << mysql_error(db_);
	}
  
	if (config_.skip_db_creation() == 0){
	  const std::string create_database_cmd = absl::StrCat("create database if not exists ", config_.db());
	  run_query(create_database_cmd);
	  skip_db_creation_  = config_.skip_db_creation(); 
	}

	if (config_.db().empty()) {
	  db_name_ = config_.db();
	  const std::string change_db = absl::StrCat("use ", config_.db());
	  run_query(change_db);
	}
  }

  void database_access_object :: close_impl(){
	if (db_ != nullptr) {
	  DiscardResultSet();
	  mysql_close(db_);
	  db_ = nullptr; 
	}
  }

  Status database_access_object :: connect(){
	if (is_connected_) {
	  return absl::FailedPreconditionError(
		  "The connection has already opended. Close() the current connection before Connect() again"
	  );
	}
	connect_impl();
	is_connected_ = true;
	return absl::OkStatus();
  }

  Status database_access_object :: close() {
	if (!is_connected_) {
	  return absl::FailedPreconditionError(
		  "The connection has already closed. Connect() database before Close() again"
	  );
	}
	close_impl();
	is_connected_ = false;
	return absl::OkStatus();
  }

  void database_access_object :: DiscardResultSet() { 
	mysql_free_result(result_set_);
	result_set_ = nullptr;
  }

  void database_access_object :: run_query(const std::string query) {
	DiscardResultSet();
	mysql_query(db_, query.c_str());
	result_set_ = mysql_store_result(db_);
	if (!result_set_ && mysql_field_count(db_) != 0) {
	  absl::StatusCode::kInternal;
	  LOG(ERROR) << "mysql_query return unexpected null result " << ": " << mysql_errno(db_) << " : " <<mysql_error(db_);
	  
	}
  }
}
