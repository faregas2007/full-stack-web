load("@rules_cc//cc:defs.bzl", "cc_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

cc_proto_library(
	name = "database_config_cc_proto",
	deps = [":database_config_proto"], 
	visibility = [
	  "//database_store:__pkg__",
	],
)

proto_library(
	name = "database_config_proto",
	srcs = ["database_config.proto"],
	deps = [
	  "@com_google_protobuf//:any_proto"
	],
)
