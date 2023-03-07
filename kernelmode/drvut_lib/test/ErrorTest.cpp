#include <gtest/gtest.h>

#include <string>

#include "Error.h"

namespace drvut {
namespace internal {

TEST(ErrorMessageTest, FailAccessBeforeInitialized) {
    ASSERT_ANY_THROW(ErrorMessage::append(""));
}

TEST(ErrorMessageTest, Append) {
    ErrorMessageGuard guard;
    ASSERT_NO_THROW(ErrorMessage::append("AAA"));
    ASSERT_NO_THROW(ErrorMessage::append("BBB"));
    ASSERT_EQ(::std::string(ErrorMessage::view().data()),
              "AAABBB");
}

TEST(ErrorMessageTest, Reset) {
    ErrorMessageGuard guard;
    ErrorMessage::append("AAA");
    ASSERT_NO_THROW(ErrorMessage::reset());
    ASSERT_NO_THROW(ErrorMessage::append("BBB"));
    ASSERT_EQ(::std::string(ErrorMessage::view().data()), "BBB");
}

TEST(ErrorMessageTest, GuardDestroysOnDtor) {
    {
        ErrorMessageGuard guard;
        ErrorMessage::append("AAA");
    }
    ASSERT_ANY_THROW(ErrorMessage::view());
}

}
}