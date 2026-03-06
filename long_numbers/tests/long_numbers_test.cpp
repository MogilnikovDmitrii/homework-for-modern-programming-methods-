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



TEST(LongNumberTest, AdditionSimple) {
    LongNumber a("2");
    LongNumber b("3");
    EXPECT_EQ(a + b, LongNumber("5"));
}

TEST(LongNumberTest, AdditionWithCarry) {
    LongNumber a("9");
    LongNumber b("1");
    EXPECT_EQ(a + b, LongNumber("10"));
}

TEST(LongNumberTest, AdditionDifferentLengths) {
    LongNumber a("123");
    LongNumber b("7");
    EXPECT_EQ(a + b, LongNumber("130"));
}

TEST(LongNumberTest, AdditionLargeNumbers) {
    LongNumber a("999999999");
    LongNumber b("1");
    EXPECT_EQ(a + b, LongNumber("1000000000"));
}

TEST(LongNumberTest, AdditionWithZero) {
    LongNumber a("12345");
    LongNumber b("0");
    EXPECT_EQ(a + b, LongNumber("12345"));
}

TEST(LongNumberTest, AdditionNegativeNumbers) {
    LongNumber a("-5");
    LongNumber b("-7");
    EXPECT_EQ(a + b, LongNumber("-12"));
}

TEST(LongNumberTest, AdditionPositiveAndNegative) {
    LongNumber a("10");
    LongNumber b("-3");
    EXPECT_EQ(a + b, LongNumber("7"));
}

TEST(LongNumberTest, AdditionNegativeAndPositive) {
    LongNumber a("-10");
    LongNumber b("3");
    EXPECT_EQ(a + b, LongNumber("-7"));
}


/* ---------------- ВЫЧИТАНИЕ ---------------- */

TEST(LongNumberTest, SubtractionSimple) {
    LongNumber a("5");
    LongNumber b("3");
    EXPECT_EQ(a - b, LongNumber("2"));
}

TEST(LongNumberTest, SubtractionNegativeResult) {
    LongNumber a("3");
    LongNumber b("5");
    EXPECT_EQ(a - b, LongNumber("-2"));
}

TEST(LongNumberTest, SubtractionWithBorrow) {
    LongNumber a("10");
    LongNumber b("1");
    EXPECT_EQ(a - b, LongNumber("9"));
}

TEST(LongNumberTest, SubtractionLargeBorrow) {
    LongNumber a("1000");
    LongNumber b("1");
    EXPECT_EQ(a - b, LongNumber("999"));
}

TEST(LongNumberTest, SubtractionDifferentLengths) {
    LongNumber a("1234");
    LongNumber b("34");
    EXPECT_EQ(a - b, LongNumber("1200"));
}

TEST(LongNumberTest, SubtractionWithZero) {
    LongNumber a("123");
    LongNumber b("0");
    EXPECT_EQ(a - b, LongNumber("123"));
}

TEST(LongNumberTest, SubtractionToZero) {
    LongNumber a("456");
    LongNumber b("456");
    EXPECT_EQ(a - b, LongNumber("0"));
}

TEST(LongNumberTest, SubtractionNegativeNumbers) {
    LongNumber a("-10");
    LongNumber b("-3");
    EXPECT_EQ(a - b, LongNumber("-7"));
}

TEST(LongNumberTest, SubtractionNegativeFromPositive) {
    LongNumber a("10");
    LongNumber b("-5");
    EXPECT_EQ(a - b, LongNumber("15"));
}

TEST(LongNumberTest, SubtractionPositiveFromNegative) {
    LongNumber a("-10");
    LongNumber b("5");
    EXPECT_EQ(a - b, LongNumber("-15"));
}


TEST(LongNumberTest, MultiplicationByZero) {
    LongNumber a("12345");
    LongNumber b("0");
    EXPECT_EQ(a * b, LongNumber("0"));
}

TEST(LongNumberTest, ZeroByNumber) {
    LongNumber a("0");
    LongNumber b("6789");
    EXPECT_EQ(a * b, LongNumber("0"));
}

TEST(LongNumberTest, MultiplicationPositiveNumbers) {
    LongNumber a("12");
    LongNumber b("34");
    EXPECT_EQ(a * b, LongNumber("408"));
}

TEST(LongNumberTest, MultiplicationPositiveAndNegative) {
    LongNumber a("-12");
    LongNumber b("34");
    EXPECT_EQ(a * b, LongNumber("-408"));
}

TEST(LongNumberTest, MultiplicationNegativeAndPositive) {
    LongNumber a("12");
    LongNumber b("-34");
    EXPECT_EQ(a * b, LongNumber("-408"));
}

TEST(LongNumberTest, MultiplicationNegativeNumbers) {
    LongNumber a("-12");
    LongNumber b("-34");
    EXPECT_EQ(a * b, LongNumber("408"));
}

TEST(LongNumberTest, MultiplicationLargeNumbers) {
    LongNumber a("123456");
    LongNumber b("789");
    EXPECT_EQ(a * b, LongNumber("97406784"));
}

TEST(LongNumberTest, MultiplicationSingleDigits) {
    LongNumber a("7");
    LongNumber b("8");
    EXPECT_EQ(a * b, LongNumber("56"));
}

TEST(LongNumberTest, MultiplicationByOne) {
    LongNumber a("98765");
    LongNumber b("1");
    EXPECT_EQ(a * b, LongNumber("98765"));
}

TEST(LongNumberTest, MultiplicationOneByNumber) {
    LongNumber a("1");
    LongNumber b("98765");
    EXPECT_EQ(a * b, LongNumber("98765"));
}

TEST(LongNumberTest, DivisionSimple1) {
    LongNumber a("10");
    LongNumber b("2");
    EXPECT_EQ(a / b, LongNumber("5"));
}

TEST(LongNumberTest, DivisionSimple2) {
    LongNumber a("100");
    LongNumber b("10");
    EXPECT_EQ(a / b, LongNumber("10"));
}

TEST(LongNumberTest, DivisionSimple3) {
    LongNumber a("9");
    LongNumber b("3");
    EXPECT_EQ(a / b, LongNumber("3"));
}

TEST(LongNumberTest, DivisionWithRemainder) {
    LongNumber a("7");
    LongNumber b("2");
    EXPECT_EQ(a / b, LongNumber("3"));
}

TEST(LongNumberTest, DivisionByLarger) {
    LongNumber a("5");
    LongNumber b("10");
    EXPECT_EQ(a / b, LongNumber("0"));
}

TEST(LongNumberTest, DivisionSameNumbers) {
    LongNumber a("12345");
    LongNumber b("12345");
    EXPECT_EQ(a / b, LongNumber("1"));
}

TEST(LongNumberTest, DivisionNegativeResult) {
    LongNumber a("-10");
    LongNumber b("2");
    EXPECT_EQ(a / b, LongNumber("-5"));
}

TEST(LongNumberTest, DivisionNegativeDivisor) {
    LongNumber a("10");
    LongNumber b("-2");
    EXPECT_EQ(a / b, LongNumber("-5"));
}

TEST(LongNumberTest, DivisionTwoNegatives) {
    LongNumber a("-10");
    LongNumber b("-2");
    EXPECT_EQ(a / b, LongNumber("5"));
}

TEST(LongNumberTest, DivisionLargeNumber) {
    LongNumber a("1000");
    LongNumber b("10");
    EXPECT_EQ(a / b, LongNumber("100"));
}

TEST(LongNumberTest, DivisionLargeNumber2) {
    LongNumber a("999");
    LongNumber b("9");
    EXPECT_EQ(a / b, LongNumber("111"));
}

TEST(LongNumberTest, DivisionOne) {
    LongNumber a("123456");
    LongNumber b("1");
    EXPECT_EQ(a / b, LongNumber("123456"));
}

TEST(LongNumberTest, ModuloSimple) {
    LongNumber a("17");
    LongNumber b("5");

    EXPECT_EQ(a % b, LongNumber("2"));
}

TEST(LongNumberTest, ModuloExactDivision) {
    LongNumber a("20");
    LongNumber b("5");

    EXPECT_EQ(a % b, LongNumber("0"));
}

TEST(LongNumberTest, ModuloSmallerDividend) {
    LongNumber a("3");
    LongNumber b("5");

    EXPECT_EQ(a % b, LongNumber("3"));
}

TEST(LongNumberTest, ModuloNegativeDividend) {
    LongNumber a("-17");
    LongNumber b("5");

    EXPECT_EQ(a % b, LongNumber("-2"));
}

TEST(LongNumberTest, ModuloNegativeDivisor) {
    LongNumber a("17");
    LongNumber b("-5");

    EXPECT_EQ(a % b, LongNumber("2"));
}

TEST(LongNumberTest, ModuloTwoNegatives) {
    LongNumber a("-17");
    LongNumber b("-5");

    EXPECT_EQ(a % b, LongNumber("-2"));
}

TEST(LongNumberTest, ModuloLargeNumbers) {
    LongNumber a("123456789");
    LongNumber b("1000");

    EXPECT_EQ(a % b, LongNumber("789"));
}

TEST(LongNumberTest, ModuloByOne) {
    LongNumber a("987654321");
    LongNumber b("1");

    EXPECT_EQ(a % b, LongNumber("0"));
}

TEST(LongNumberTest, ModuloZeroDividend) {
    LongNumber a("0");
    LongNumber b("7");

    EXPECT_EQ(a % b, LongNumber("0"));
}