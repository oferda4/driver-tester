#include <gtest/gtest.h>

#include "CastUtils.h"

TEST(CastUtilsTest, validCast) {
    const uint32_t num = 1;
    ASSERT_EQ(num, CastUtils::cast<uint16_t>(num));
}

TEST(CastUtilsTest, invalidCast) {
    const uint32_t num = UINT16_MAX + 1UL;
    ASSERT_THROW(CastUtils::cast<uint16_t>(num), InvalidCast);
}
