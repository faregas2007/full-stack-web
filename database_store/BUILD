load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
	name = "database_access_object_test",
	srcs = ["database_access_object_test.cpp"],
	deps = [
	  ":database_access_object",
	  "@com_github_gflags_gflags//:gflags",
	  "@com_google_absl//absl/status",
	  "@com_google_glog//:glog",
	],
)

cc_library(
	name = "database_access_object",
	srcs = ["database_access_object.cpp"],
	hdrs = ["database_access_object.h"],
	deps = [
	  "//protos:database_config_cc_proto",
	  "@com_google_absl//absl/strings",
	  "@com_google_absl//absl/status",
	  "@com_github_gflags_gflags//:gflags",
	  "@com_google_glog//:glog",

	],
	includes = [
	  "usr/includes/mysql/*.h"
	],
	linkopts = [
	  "-lmysqlclient",
	  "-lzstd",
	  "-lssl",
	  "-lcrypto",
	  "-lresolv",
	  "-lm",
	],
)
