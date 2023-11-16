#include <gtest/gtest.h>
#include <ulfcom/ulfcom.hpp>

TEST(str2cmd, empty_string) { EXPECT_TRUE(ulfcom::str2cmd("")); }

TEST(str2cmd, wrong_string) {
  auto b{ulfcom::str2cmd("123")};
  EXPECT_FALSE(b);
  EXPECT_EQ(b, std::unexpected(std::errc::bad_message));
}

TEST(str2cmd, not_enough_characters) {
  // Missing "ING\r"
  {
    auto b{ulfcom::str2cmd("P")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }

  // Missing "EIN\r"
  {
    auto b{ulfcom::str2cmd("DCC_")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }

  // Missing "2\r"
  {
    auto b{ulfcom::str2cmd("SUSIV")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }
}

TEST(str2cmd, complete_string) {
  // Complete "PING\r"
  {
    auto b{ulfcom::str2cmd("PING\r")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(b->value(), "PING\r");
  }

  // Complete "MDU_EIN\r"
  {
    auto b{ulfcom::str2cmd("MDU_EIN\r")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(b->value(), "MDU_EIN\r");
  }

  // Complete "MDU_EIN\r" and additional unused characters
  {
    auto b{ulfcom::str2cmd("MDU_EIN\rsomemore")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(b->value(), "MDU_EIN\r");
  }
}