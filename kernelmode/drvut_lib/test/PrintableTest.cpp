#include <gtest/gtest.h>

#include "Printable.h"

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

}
