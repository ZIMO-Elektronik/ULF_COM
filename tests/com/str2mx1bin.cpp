#include <gtest/gtest.h>
#include <ulf/com.hpp>

TEST(str2mx1bin, string_empty) { EXPECT_TRUE(ulf::com::str2mx1bin("")); }

TEST(str2mx1bin, string_invalid) {
  auto b{ulf::com::str2mx1bin("123")};
  EXPECT_FALSE(b);
  EXPECT_EQ(b, std::unexpected(std::errc::invalid_argument));
}

TEST(str2mx1bin, string_too_short) {
  // Missing second SOH and ETB
  {
    auto b{ulf::com::str2mx1bin("\x01")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }

  // Missing ETB
  {
    auto b{ulf::com::str2mx1bin("\x01\x01")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }

  // Missing ETB
  {
    auto b{ulf::com::str2mx1bin("\x01\x01somethingelse")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }
}

TEST(str2mx1bin, string_valid) {
  // SOH SOH data ETB
  {
    auto b{ulf::com::str2mx1bin("\x01\x01"
                                "data\x17")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(size(b->value()), 7uz);
  }

  // SOH SOH data ETB and additional unused characters
  {
    auto b{ulf::com::str2mx1bin("\x01\x01"
                                "data\x17"
                                "someextradata")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(size(b->value()), 7uz);
  }
}

TEST(str2mx1bin, string_valid_with_escaped_characters) {
  // SOH SOH escaped ETB data ETB
  {
    auto b{ulf::com::str2mx1bin("\x01\x01"
                                "\x10\x17"
                                "data\x17")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(size(b->value()), 9uz);
  }

  // SOH SOH escaped ETB data ETB and additional unused characters
  {
    auto b{ulf::com::str2mx1bin("\x01\x01"
                                "\x10\x17"
                                "data\x17"
                                "someextradata")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(size(b->value()), 9uz);
  }
}