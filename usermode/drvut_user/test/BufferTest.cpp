#include "Buffer.h"

#include <gtest/gtest.h>

namespace {
template <std::integral T>
void testNumberConversion();
}

TEST(BufferTest, NumberConversion) {
    ASSERT_NO_THROW(testNumberConversion<uint16_t>());
    ASSERT_NO_THROW(testNumberConversion<int32_t>());
    ASSERT_NO_THROW(testNumberConversion<uint64_t>());
}

TEST(BufferTest, ToNumberBadSize) {
    using ArbitraryNumType = uint32_t;
    ASSERT_THROW(BufferUtils::toNumber<ArbitraryNumType>(Buffer(sizeof(ArbitraryNumType) - 1, 0)),
                 InvalidBufferSize);
}

TEST(BufferTest, Equals) {
    Buffer buffer({ 1, 2, 3 });
    Buffer equalBuffer({ 1, 2, 3 });
    Buffer nonEqualBuffer({ 1, 2, 5 });
    Buffer nonEqualWithDifferentSize({ 1, 2 });

    EXPECT_TRUE(BufferUtils::equal(buffer, equalBuffer));
    EXPECT_FALSE(BufferUtils::equal(buffer, nonEqualBuffer));
    EXPECT_FALSE(BufferUtils::equal(buffer, nonEqualWithDifferentSize));
    EXPECT_TRUE(BufferUtils::equal(Buffer{}, Buffer{}));
}

TEST(BufferTest, Append) {
    Buffer part1({ 1, 2, 3 });
    Buffer part2({ 4, 5, 6 });
    Buffer full({ 1, 2, 3, 4, 5, 6 });
    ASSERT_NO_THROW(BufferUtils::append(part1, part2));
    ASSERT_TRUE(BufferUtils::equal(part1, full));
}

namespace {
template <std::integral T>
void testNumberConversion() {
    const T arbitraryNum = static_cast<T>(11223344);
    Buffer buffer = BufferUtils::fromNumber(arbitraryNum);
    T resultNum = BufferUtils::toNumber<T>(buffer);
    ASSERT_EQ(arbitraryNum, resultNum);
}
}
