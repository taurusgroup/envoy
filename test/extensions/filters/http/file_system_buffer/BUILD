load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_test",
    "envoy_package",
)

licenses(["notice"])  # Apache 2

envoy_package()

envoy_cc_test(
    name = "fragment_test",
    srcs = ["fragment_test.cc"],
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/filters/http/file_system_buffer:fragment",
        "//test/extensions/common/async_files:mocks",
        "//test/mocks/buffer:buffer_mocks",
        "//test/test_common:status_utility_lib",
    ],
)

envoy_cc_test(
    name = "file_system_buffer_test",
    srcs = [
        "config_test.cc",
        "filter_test.cc",
    ],
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/filters/http/file_system_buffer:config",
        "//test/extensions/common/async_files:mocks",
        "//test/mocks/server:server_mocks",
        "//test/mocks/upstream:upstream_mocks",
    ],
)
