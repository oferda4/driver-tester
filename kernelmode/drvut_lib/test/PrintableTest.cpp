#include <gtest/gtest.h>

#include "drvut/Printable.h"

namespace drvut {

TEST(PrintableTest, Integral_ToString) {
    EXPECT_EQ(std::string(I(1356).toString().data()), "1356");
    EXPECT_EQ(std::string(I(-8891).toString().data()), "-8891");
    EXPECT_EQ(std::string(I(0).toString().data()), "0");
}

TEST(PrintableTest, Integral_Conversion) {
    ASSERT_EQ(I(1123), 1123);
}

TEST(PrintableTest, Boolean_ToString) {
    EXPECT_EQ(std::string(B(true).toString().data()), "true");
    EXPECT_EQ(std::string(B(false).toString().data()), "false");
}

TEST(PrintableTest, Boolean_Conversion) {
    EXPECT_EQ(I(true), true);
    EXPECT_EQ(I(false), false);
}

TEST(PrintableTest, AreEqual_ToString) {
    EXPECT_EQ(std::string(AreEqual(0, 0).toString().data()), "unknown == unknown");
    EXPECT_EQ(std::string(AreEqual(I(0), 0).toString().data()), "0 == unknown");
    EXPECT_EQ(std::string(AreEqual(0, I(0)).toString().data()), "unknown == 0");
}

TEST(PrintableTest, AreEqual_Conversion) {
    EXPECT_TRUE(AreEqual(0, 0));
    EXPECT_TRUE(AreEqual(I(0), 0));
    EXPECT_FALSE(AreEqual(1, 0));
    EXPECT_FALSE(AreEqual(I(0), I(1)));
}

TEST(PrintableTest, AreNotEqual_ToString) {
    EXPECT_EQ(std::string(AreNotEqual(1, 0).toString().data()), "unknown != unknown");
    EXPECT_EQ(std::string(AreNotEqual(I(1), 0).toString().data()), "1 != unknown");
    EXPECT_EQ(std::string(AreNotEqual(1, I(0)).toString().data()), "unknown != 0");
}

TEST(PrintableTest, AreNotEqual_Conversion) {
    EXPECT_TRUE(AreNotEqual(1, 0));
    EXPECT_TRUE(AreNotEqual(I(1), 0));
    EXPECT_FALSE(AreNotEqual(1, 1));
    EXPECT_FALSE(AreNotEqual(I(1), I(1)));
}

TEST(PrintableTest, Greater_ToString) {
    EXPECT_EQ(std::string(Greater(1, 0).toString().data()), "unknown > unknown");
    EXPECT_EQ(std::string(Greater(I(1), 0).toString().data()), "1 > unknown");
    EXPECT_EQ(std::string(Greater(1, I(0)).toString().data()), "unknown > 0");
}

TEST(PrintableTest, Greater_Conversion) {
    EXPECT_TRUE(Greater(1, 0));
    EXPECT_TRUE(Greater(I(1), 0));
    EXPECT_FALSE(Greater(1, 1));
    EXPECT_FALSE(Greater(I(1), I(1)));
}

TEST(PrintableTest, GreaterOrEqual_ToString) {
    EXPECT_EQ(std::string(GreaterOrEqual(1, 0).toString().data()), "unknown >= unknown");
    EXPECT_EQ(std::string(GreaterOrEqual(I(1), 0).toString().data()), "1 >= unknown");
    EXPECT_EQ(std::string(GreaterOrEqual(0, I(0)).toString().data()), "unknown >= 0");
}

TEST(PrintableTest, GreaterOrEqual_Conversion) {
    EXPECT_TRUE(GreaterOrEqual(1, 0));
    EXPECT_TRUE(GreaterOrEqual(I(1), 1));
    EXPECT_FALSE(GreaterOrEqual(1, 2));
    EXPECT_FALSE(GreaterOrEqual(I(1), I(2)));
}

TEST(PrintableTest, Lower_ToString) {
    EXPECT_EQ(std::string(Lower(0, 1).toString().data()), "unknown < unknown");
    EXPECT_EQ(std::string(Lower(I(0), 1).toString().data()), "0 < unknown");
    EXPECT_EQ(std::string(Lower(0, I(1)).toString().data()), "unknown < 1");
}

TEST(PrintableTest, Lower_Conversion) {
    EXPECT_TRUE(Lower(0, 1));
    EXPECT_TRUE(Lower(I(0), 1));
    EXPECT_FALSE(Lower(1, 0));
    EXPECT_FALSE(Lower(I(1), I(1)));
}

TEST(PrintableTest, LowerOrEqual_ToString) {
    EXPECT_EQ(std::string(LowerOrEqual(0, 0).toString().data()), "unknown <= unknown");
    EXPECT_EQ(std::string(LowerOrEqual(I(0), 1).toString().data()), "0 <= unknown");
    EXPECT_EQ(std::string(LowerOrEqual(0, I(0)).toString().data()), "unknown <= 0");
}

TEST(PrintableTest, LowerOrEqual_Conversion) {
    EXPECT_TRUE(LowerOrEqual(0, 1));
    EXPECT_TRUE(LowerOrEqual(I(1), 1));
    EXPECT_FALSE(LowerOrEqual(1, 0));
    EXPECT_FALSE(LowerOrEqual(I(1), I(0)));
}

TEST(PrintableUtilsTest, PrintableOrUnknown) {
    EXPECT_EQ(std::string(PrintableUtils::printableOrUnknown(I(11)).data()), "11");
    EXPECT_EQ(std::string(PrintableUtils::printableOrUnknown(11).data()), "unknown");
}

}
