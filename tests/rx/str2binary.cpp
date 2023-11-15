#include <gtest/gtest.h>
#include <ulfcom/ulfcom.hpp>

TEST(str2binary, empty_string) { EXPECT_TRUE(ulfcom::rx::str2binary("")); }

TEST(str2binary, wrong_string) {
  auto b{ulfcom::rx::str2binary("123")};
  EXPECT_FALSE(b);
  EXPECT_EQ(b, std::unexpected(std::errc::bad_message));
}

TEST(str2binary, not_enough_characters) {
  auto b{ulfcom::rx::str2binary("\x01")};
  EXPECT_TRUE(b);
  EXPECT_FALSE(*b);

  b = ulfcom::rx::str2binary("\x01\x01");
  EXPECT_TRUE(b);
  EXPECT_FALSE(*b);

  b = ulfcom::rx::str2binary("\x01\x01somethingelse");
  EXPECT_TRUE(b);
  EXPECT_FALSE(*b);
}

TEST(str2binary, complete_string) {
  auto b{ulfcom::rx::str2binary("\x01\x01"
                                "data\x17")};
  EXPECT_TRUE(b);
  EXPECT_TRUE(*b);
  EXPECT_EQ(size(b->value()), 7uz);

  b = ulfcom::rx::str2binary("\x01\x01"
                             "data\x17"
                             "someextradata");
  EXPECT_TRUE(b);
  EXPECT_TRUE(*b);
  EXPECT_EQ(size(b->value()), 7uz);
}

TEST(str2binary, complete_string_with_escaped_characters) {
  auto b{ulfcom::rx::str2binary("\x01\x01"
                                "\x10\x17"
                                "data\x17")};
  EXPECT_TRUE(b);
  EXPECT_TRUE(*b);
  EXPECT_EQ(size(b->value()), 9uz);

  b = ulfcom::rx::str2binary("\x01\x01"
                             "\x10\x17"
                             "data\x17"
                             "someextradata");
  EXPECT_TRUE(b);
  EXPECT_TRUE(*b);
  EXPECT_EQ(size(b->value()), 9uz);
}