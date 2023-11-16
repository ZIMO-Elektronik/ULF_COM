#include <gtest/gtest.h>
#include <ulfcom/ulfcom.hpp>

TEST(str2mx1bin, empty_string) { EXPECT_TRUE(ulfcom::str2mx1bin("")); }

TEST(str2mx1bin, wrong_string) {
  auto b{ulfcom::str2mx1bin("123")};
  EXPECT_FALSE(b);
  EXPECT_EQ(b, std::unexpected(std::errc::bad_message));
}

TEST(str2mx1bin, not_enough_characters) {
  // Missing second SOH and ETB
  {
    auto b{ulfcom::str2mx1bin("\x01")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }

  // Missing ETB
  {
    auto b{ulfcom::str2mx1bin("\x01\x01")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }

  // Missing ETB
  {
    auto b{ulfcom::str2mx1bin("\x01\x01somethingelse")};
    EXPECT_TRUE(b);
    EXPECT_FALSE(*b);
  }
}

TEST(str2mx1bin, complete_string) {
  // SOH SOH data ETB
  {
    auto b{ulfcom::str2mx1bin("\x01\x01"
                                  "data\x17")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(size(b->value()), 7uz);
  }

  // SOH SOH data ETB and additional unused characters
  {
    auto b{ulfcom::str2mx1bin("\x01\x01"
                                  "data\x17"
                                  "someextradata")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(size(b->value()), 7uz);
  }
}

TEST(str2mx1bin, complete_string_with_escaped_characters) {
  // SOH SOH escaped ETB data ETB
  {
    auto b{ulfcom::str2mx1bin("\x01\x01"
                                  "\x10\x17"
                                  "data\x17")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(size(b->value()), 9uz);
  }

  // SOH SOH escaped ETB data ETB and additional unused characters
  {
    auto b{ulfcom::str2mx1bin("\x01\x01"
                                  "\x10\x17"
                                  "data\x17"
                                  "someextradata")};
    EXPECT_TRUE(b);
    EXPECT_TRUE(*b);
    EXPECT_EQ(size(b->value()), 9uz);
  }
}