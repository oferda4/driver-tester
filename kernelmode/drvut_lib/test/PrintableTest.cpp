#include <gtest/gtest.h>

#include "Printable.h"

namespace drvut {

TEST(PrintableTest, Integral) {
    EXPECT_EQ(std::string(I(1356).toString().data()), "1356");
    EXPECT_EQ(std::string(I(-8891).toString().data()), "-8891");
    EXPECT_EQ(std::string(I(0).toString().data()), "0");
}

TEST(PrintableTest, Boolean) {
    EXPECT_EQ(std::string(B(true).toString().data()), "true");
    EXPECT_EQ(std::string(B(false).toString().data()), "false");
}

}
