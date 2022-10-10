# libmysqlclient-dev: contains mysql-api-c 
# mysql-server: mysqlserver 
# libssl-dev: ssl/tls lib, also contains libcrypto 
# libresolv-wrapper: resolving dns name. 
# libpthreadpool-dev: multi-threadings c/c++ lib   
apt-get install bazel -y
apt-get install libmysqlient-dev mysql-client mysql-server -y 
apt-get install libssl-dev libresolv-wrapper libpthreadpool-dev  -y 


# proto_cc class generated 
wdr=$PWD 
bazel build //protos:database_config_cc_proto 
cp -f wdr/database_config.pb.* wdr/protos/
bazel build //datastore:database_access_object_test

# test 
bazel run //datastore:database_access_object_test 
# user granting permission to mysql server.
# mysql -u "username" -p "password" 
