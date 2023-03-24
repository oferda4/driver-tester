#include "drvut/internal/StringUtils.h"

#include <string>

#include <gtest/gtest.h>

namespace drvut {

TEST(StringTest, Concat) {
    String result = internal::StringUtils::concat("ABC", "1234");
    ASSERT_EQ(result.size(), 7);
    ASSERT_EQ(::std::string(result.data()), "ABC1234");
}

TEST(StringTest, Concat_BothEmpty) {
    String result = internal::StringUtils::concat("", "");
    ASSERT_EQ(result.size(), 0);
    ASSERT_EQ(::std::string(result.data()), "");
}

TEST(StringTest, Concat_ToEmpty) {
    String result = internal::StringUtils::concat("", "1234");
    ASSERT_EQ(result.size(), 4);
    ASSERT_EQ(::std::string(result.data()), "1234");
}

TEST(StringTest, Concat_FromEmpty) {
    String result = internal::StringUtils::concat("ABC", "");
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(::std::string(result.data()), "ABC");
}

}
