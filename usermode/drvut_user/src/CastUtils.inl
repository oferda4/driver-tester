#pragma once

#include "CastUtils.h"

template <std::integral ToType, std::integral FromType>
ToType CastUtils::cast(FromType num) {
    const auto result = static_cast<ToType>(num);
    if (result != num) {
        throw InvalidCast();
    }
    return result;
}