load("rules_cc//cc:defs.bzl", "cc_library")
load("rules_proto//cc:defs.bzl", "proto_libary")

cc_proto_library(
	name = "database_config_cc_proto",
	deps = [":database_config_proto"],
)

proto_library(
	name = "database_config_proto",
	srcs = ["database_config.proto"],
	deps = [
	  "@com_google_protobuf//:any_proto"
	]
)
