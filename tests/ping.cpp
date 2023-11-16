#include <gtest/gtest.h>
#include <ulfcom/ulfcom.hpp>

TEST(ping, assert_nullptr_arguments) {
  ASSERT_DEATH(ulfcom::ping(nullptr, nullptr), ".*");
  ASSERT_DEATH(ulfcom::ping(nullptr, "version"), ".*");
  ASSERT_DEATH(ulfcom::ping("device_name", nullptr), ".*");
}