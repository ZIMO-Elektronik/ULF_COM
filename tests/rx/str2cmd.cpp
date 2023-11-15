#include <gtest/gtest.h>
#include <ulfcom/ulfcom.hpp>

TEST(str2cmd, empty_string) { EXPECT_TRUE(ulfcom::rx::str2cmd("")); }

TEST(str2cmd, wrong_string) {
  auto b{ulfcom::rx::str2cmd("123")};
  EXPECT_FALSE(b);
  EXPECT_EQ(b, std::unexpected(std::errc::bad_message));
}

TEST(str2cmd, not_enough_characters) {
  {
    auto b{ulfcom::rx::str2cmd("P")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }
  {
    auto b{ulfcom::rx::str2cmd("DCC_")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }
  {
    auto b{ulfcom::rx::str2cmd("SUSIV")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }
}

TEST(str2cmd, complete_string) {
  {
    auto b{ulfcom::rx::str2cmd("PING\r")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(b->value(), "PING\r");
  }
  {
    auto b{ulfcom::rx::str2cmd("MDU_EIN\r")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(b->value(), "MDU_EIN\r");
  }
  {
    auto b{ulfcom::rx::str2cmd("MDU_EIN\rsomemore")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(b->value(), "MDU_EIN\r");
  }
}