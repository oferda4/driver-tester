#include <gtest/gtest.h>

#include <string>

#include "TupleUtils.h"

namespace drvut {
namespace internal {

using ::std::string;

namespace {
template <bool isVoid, size_t elementsToExecute>
void testForEachSanity();
}

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

TEST(TupleUtilsTest, ForEach_Sanity) {
    testForEachSanity<false, 0>();
    testForEachSanity<true, 0>();
    testForEachSanity<false, 1>();
    testForEachSanity<true, 1>();
    testForEachSanity<false, 3>();
    testForEachSanity<true, 3>();
    testForEachSanity<false, 5>();
    testForEachSanity<true, 5>();
}

TEST(TupleUtilsTest, ForEach_FailureInTheMiddle) {
    Tuple<uint32_t, uint32_t> tuple(0, 1);
    uint16_t index = 0;
    auto func = [&index](auto& num) -> NTSTATUS {
        EXPECT_EQ(index, num);
        index++;
        // only first will succeed
        return num == 0 ? STATUS_SUCCESS : STATUS_INVALID_PARAMETER;
    };

    EXPECT_EQ(1, TupleUtils::forEach(tuple, func));
    // after failure on second it should stop iterating
    EXPECT_EQ(index, 2);
}

namespace {
template <bool isVoid, size_t maxIndex>
static void testForEachSanity() {
    Tuple<uint32_t, uint32_t, uint16_t> tuple(0, 1, 2);
    uint16_t index = 0;
    auto func = [&index](auto& num) {
        EXPECT_EQ(index, num);
        index++;
        if constexpr (!isVoid) {
            return STATUS_SUCCESS;
        }
    };

    const auto actualExecuted = min(maxIndex, tuple.size);
    EXPECT_EQ(actualExecuted, TupleUtils::forEach(tuple, func, maxIndex));
    EXPECT_EQ(actualExecuted, index);
}
}

}
}