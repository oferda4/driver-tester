#pragma once

#include "Defs.h"

struct InvalidCast : std::exception {
    // intentionally left blank
};

class CastUtils final {
public:
    CastUtils() = delete;

    template <std::integral ToType, std::integral FromType>
    static ToType cast(FromType num);
};

#include "CastUtils.inl"
