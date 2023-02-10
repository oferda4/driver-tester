#include <gtest/gtest.h>

#include <string>

#include "Tuple.h"

namespace drvut {
namespace internal {

using std::string;

TEST(TupleUtilsTest, Get) {
    uint32_t intValue = 10;
    float floatValue = 24.6f;
    string stringValue = "qwerr";

    Tuple<uint32_t, float, string> tuple(intValue, floatValue, stringValue);

    EXPECT_EQ(intValue, TupleUtils::get<0>(tuple));
    EXPECT_EQ(floatValue, TupleUtils::get<1>(tuple));
    EXPECT_EQ(stringValue, TupleUtils::get<2>(tuple));
}

}
}