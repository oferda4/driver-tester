#include <gtest/gtest.h>

#include "drvut/internal/Array.h"

namespace drvut {
namespace internal {

static uint32_t indexToArrayValue(uint32_t index);

TEST(ArrayTest, Functionality) {
    const size_t arbitrarySize = 10;
    Array<uint32_t> array(arbitrarySize);
    ASSERT_EQ(array.size(), arbitrarySize);

    for (uint32_t i = 0; i < arbitrarySize; i++) {
        array.at(i) = indexToArrayValue(i);
    }
    for (uint32_t i = 0; i < arbitrarySize; i++) {
        const auto expected = indexToArrayValue(i);
        ASSERT_EQ(array.at(i), expected);
        ASSERT_EQ(static_cast<const Array<uint32_t>&>(array).at(i), expected);
    }

    ASSERT_EQ(array.size(), arbitrarySize);
}

TEST(ArrayTest, OutOfBound) {
    const size_t arbitrarySize = 5;
    Array<uint32_t> array(arbitrarySize);

    ASSERT_ANY_THROW(array.at(arbitrarySize));
    ASSERT_ANY_THROW(array.at(arbitrarySize + 1));
    ASSERT_ANY_THROW(static_cast<const Array<uint32_t>&>(array).at(arbitrarySize));
    ASSERT_ANY_THROW(static_cast<const Array<uint32_t>&>(array).at(arbitrarySize + 1));
}

uint32_t indexToArrayValue(uint32_t index) {
    return index * 2;
}

}
}
