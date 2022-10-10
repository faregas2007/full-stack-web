load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_cc",
    urls = ["https://github.com/bazelbuild/rules_cc/releases/download/0.0.4/rules_cc-0.0.4.tar.gz"],
    sha256 = "af6cc82d87db94585bceeda2561cb8a9d55ad435318ccb4ddfee18a43580fb5d",
    strip_prefix = "rules_cc-0.0.4",
)

http_archive(
    name = "bazel_skylib",
    sha256 = "97e70364e9249702246c0e9444bccdc4b847bed1eb03c5a3ece4f83dfe6abc44",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.0.2/bazel-skylib-1.0.2.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.0.2/bazel-skylib-1.0.2.tar.gz",
    ],
)

PROTOBUF_COMMIT = "fde7cf7358ec7cd69e8db9be4f1fa6a5c431386a" # 3.13.0
http_archive(
    name = "com_google_protobuf",
    sha256 = "e589e39ef46fb2b3b476b3ca355bd324e5984cbdfac19f0e1625f0042e99c276",
    strip_prefix = "protobuf-%s" % PROTOBUF_COMMIT,
    urls = [
        "https://storage.googleapis.com/grpc-bazel-mirror/github.com/google/protobuf/archive/%s.tar.gz" % PROTOBUF_COMMIT,
        "https://github.com/google/protobuf/archive/%s.tar.gz" % PROTOBUF_COMMIT,
    ],
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

# gRPC. Official release 1.33.2. Name is required by Google APIs.
http_archive(
    name = "com_github_grpc_grpc",
    sha256 = "2060769f2d4b0d3535ba594b2ab614d7f68a492f786ab94b4318788d45e3278a",
    strip_prefix = "grpc-1.33.2",
    patches = ["//ml_metadata/third_party:grpc.patch"],
    urls = ["https://github.com/grpc/grpc/archive/v1.33.2.tar.gz"],
)
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()

# Needed by Protobuf.
bind(
    name = "grpc_lib",
    actual = "@com_github_grpc_grpc//:grpc++",
)

# Needed by Protobuf.
bind(
    name = "grpc_lib",
    actual = "@com_github_grpc_grpc//:grpc++",
)

# For commandline flags used in gRPC server
git_repository(
    name = "com_github_gflags_gflags",
    # v2.2.2
    commit = "e171aa2d15ed9eb17054558e0b3a6a413bb01067",
    remote = "https://github.com/gflags/gflags.git",
)


