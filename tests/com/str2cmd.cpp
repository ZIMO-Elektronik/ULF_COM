#include <gtest/gtest.h>
#include <ulf/com.hpp>

TEST(str2cmd, string_empty) { EXPECT_TRUE(ulf::com::str2cmd("")); }

TEST(str2cmd, string_invalid) {
  auto b{ulf::com::str2cmd("123")};
  EXPECT_FALSE(b);
  EXPECT_EQ(b, std::unexpected(std::errc::invalid_argument));
}

TEST(str2cmd, string_too_short) {
  // Missing "ING\r"
  {
    auto b{ulf::com::str2cmd("P")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }

  // Missing "EIN\r"
  {
    auto b{ulf::com::str2cmd("DCC_")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }

  // Missing "2\r"
  {
    auto b{ulf::com::str2cmd("SUSIV")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }
}

TEST(str2cmd, string_valid) {
  // Complete "PING\r"
  {
    auto b{ulf::com::str2cmd("PING\r")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(b->value(), "PING\r");
  }

  // Complete "MDU_EIN\r"
  {
    auto b{ulf::com::str2cmd("MDU_EIN\r")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(b->value(), "MDU_EIN\r");
  }

  // Complete "MDU_EIN\r" and additional unused characters
  {
    auto b{ulf::com::str2cmd("MDU_EIN\rsomemore")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(b->value(), "MDU_EIN\r");
  }
}