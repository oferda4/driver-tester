#pragma once

#include "traits.h"

namespace std {

namespace internal {
template <class T, class U>
concept SameHelper = std::is_same_v<T, U>;
}

template <class T, class U>
concept same_as = internal::SameHelper<T, U> && internal::SameHelper<U, T>;
}
