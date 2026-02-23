#include <gtest/gtest.h>
#include "long_numbers.hpp"

using DmMog::LongNumber;

TEST(LongNumberTest, DefaultConstructorIsZero) {
    LongNumber a;
    EXPECT_EQ(a, LongNumber("0"));
    EXPECT_FALSE(a.is_negative());
}

TEST(LongNumberTest, ConstructFromStringPositive) {
    LongNumber a("12345");
    EXPECT_EQ(a, LongNumber("12345"));
    EXPECT_FALSE(a.is_negative());
}

TEST(LongNumberTest, ConstructFromStringNegative) {
    LongNumber a("-6789");
    EXPECT_EQ(a, LongNumber("-6789"));
    EXPECT_TRUE(a.is_negative());
}

TEST(LongNumberTest, CopyConstructor) {
    LongNumber a("42");
    LongNumber b(a);
    EXPECT_EQ(a, b);
}

TEST(LongNumberTest, MoveConstructor) {
    LongNumber a("999");
    LongNumber b(std::move(a));
    EXPECT_EQ(b, LongNumber("999"));
}





TEST(LongNumberTest, AssignFromString) {
    LongNumber a;
    a = "555";
    EXPECT_EQ(a, LongNumber("555"));
}

TEST(LongNumberTest, AssignFromObject) {
    LongNumber a("111");
    LongNumber b;
    b = a;
    EXPECT_EQ(a, b);
}

TEST(LongNumberTest, AssignFromMove) {
    LongNumber a("222");
    LongNumber b;
    b = std::move(a);
    EXPECT_EQ(b, LongNumber("222"));
}





TEST(LongNumberTest, EqualityOperator) {
    LongNumber a("100");
    LongNumber b("100");
    LongNumber c("101");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a != b);
}

TEST(LongNumberTest, ComparisonOperators) {
    LongNumber a("10");
    LongNumber b("20");
    LongNumber c("-5");

    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(c < a);
    EXPECT_FALSE(a < a);
    EXPECT_FALSE(a > a);
}

TEST(LongNumberTest, IsNegative) {
    LongNumber a("-123");
    LongNumber b("0");
    LongNumber c("456");

    EXPECT_TRUE(a.is_negative());
    EXPECT_FALSE(b.is_negative());
    EXPECT_FALSE(c.is_negative());
}


TEST(LongNumberTest, OutputOperator) {
    LongNumber a("123");
    LongNumber b("-456");
    LongNumber c("0");

    std::ostringstream oss1, oss2, oss3;
    oss1 << a;
    oss2 << b;
    oss3 << c;

    EXPECT_EQ(oss1.str(), "123");
    EXPECT_EQ(oss2.str(), "-456");
    EXPECT_EQ(oss3.str(), "0");
}