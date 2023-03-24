#pragma once

#include "drvut/internal/Tuple.h"

namespace drvut {
namespace internal {

template <typename T>
struct FunctionTraits;

template <typename R, typename... Args>
struct FunctionTraits<R(*)(Args...)> {
    using ReturnType = R;
    using ArgumentsTypes = Tuple<Args...>;
};

template <typename R, typename C, typename... Args>
struct FunctionTraits<R(C::*)(Args...)> {
    using ReturnType = R;
    using ArgumentsTypes = Tuple<Args...>;
};

template <typename R, typename C, typename... Args>
struct FunctionTraits<R(C::*)(Args...) const> {
    using ReturnType = R;
    using ArgumentsTypes = Tuple<Args...>;
};

template <typename Lambda>
struct LambdaTraits : FunctionTraits<decltype(&Lambda::operator())> {
    // left blank intentionally
};

}
}
