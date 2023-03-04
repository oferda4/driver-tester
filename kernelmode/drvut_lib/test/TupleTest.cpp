#include <gtest/gtest.h>

#include <string>

#include "TupleUtils.h"

namespace drvut {
namespace internal {

using ::std::string;

TEST(TupleUtilsTest, Get) {
    uint32_t intValue = 10;
    float floatValue = 24.6f;
    string stringValue = "qwerr";

    Tuple<uint32_t, float, string> tuple(intValue, floatValue, stringValue);

    EXPECT_EQ(intValue, TupleUtils::get<0>(tuple));
    EXPECT_EQ(floatValue, TupleUtils::get<1>(tuple));
    EXPECT_EQ(stringValue, TupleUtils::get<2>(tuple));
}

TEST(TupleUtilsTest, Apply) {
    uint32_t intInput = 100;
    float floatInput = 10.1f;
    uint32_t callCount = 0;
    const double arbitraryReturnValue = 11.11;

    Tuple<uint32_t, float> tuple(intInput, floatInput);
    auto func = [&intInput, &floatInput, &callCount, &arbitraryReturnValue](uint32_t i, float f) -> double { 
        EXPECT_EQ(intInput, i);
        EXPECT_EQ(floatInput, f);
        callCount++;

        return arbitraryReturnValue;
    };

    TupleUtils::apply(func, tuple);
    EXPECT_EQ(1, callCount);
}

}
}