#include <gtest/gtest.h>

#include "FunctionUtils.h"

namespace drvut {
namespace internal {

uint32_t func(double, uint64_t) {
    return 0;
}

TEST(FunctionUtilsTest, FunctionTraits) {
    using Traits = FunctionTraits<decltype(&func)>;
    static_assert(std::is_same_v<typename Traits::ReturnType, uint32_t>);
    static_assert(std::is_same_v<typename Traits::ArgumentsTypes, Tuple<double, uint64_t>>);
}

TEST(FunctionUtilsTest, LambdaTraits) {
    auto lambda = [](bool, uint16_t) -> double { return 0; };
    using Traits = LambdaTraits<decltype(lambda)>;
    static_assert(std::is_same_v<typename Traits::ReturnType, double>);
    static_assert(std::is_same_v<typename Traits::ArgumentsTypes, Tuple<bool, uint16_t>>);
}

}
}