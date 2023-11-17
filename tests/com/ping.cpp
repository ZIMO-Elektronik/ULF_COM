#include <gtest/gtest.h>
#include <ulf/com.hpp>

TEST(ping, assert_nullptr_arguments) {
  ASSERT_DEATH(ulf::com::ping(nullptr, nullptr), ".*");
  ASSERT_DEATH(ulf::com::ping(nullptr, "version"), ".*");
  ASSERT_DEATH(ulf::com::ping("device_name", nullptr), ".*");
}

TEST(ping, device_name_and_version) {
  auto p{ulf::com::ping("DeviceName", "1.2.3")};
  std::string_view sv{cbegin(p), size(p)};
  EXPECT_EQ(sv, "DeviceName v1.2.3\r");
}

TEST(ping, truncated_device_name) {
  auto p{ulf::com::ping("TruncateThisVeryVeryVeryLongDeviceName", "1.2.3")};
  std::string_view sv{cbegin(p), size(p)};
  EXPECT_EQ(sv, "TruncateThisVeryVeryVeryLongDevi v1.2.3\r");
}

TEST(ping, truncated_version) {
  auto p{ulf::com::ping("DeviceName", "1.2.3.4.5.6.7.8.9.10.11.12.13.14.15")};
  std::string_view sv{cbegin(p), size(p)};
  EXPECT_EQ(sv, "DeviceName v1.2.3.4.5.6.7.8.9.10.11.12.13.14\r");
}