#include "../src/constexprMapArduino.cpp"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, C_assertions) {
EXPECT_EQ( C(1,2.f,3.d) == C(1,2.f,3.d), true);
EXPECT_EQ( C(1,2,3) != C(1,2,3), false);
EXPECT_EQ( C(1,2,4) == C(1,2,3), false);
EXPECT_EQ( C(1,2,3) == C(1,2,3), false);
}
