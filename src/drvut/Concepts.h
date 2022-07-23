#pragma once

#include "Traits.h"

namespace drvut {
namespace internal {
namespace std {

namespace detail {
template <class T, class U>
concept SameHelper = std::is_same_v<T, U>;
}

template <class T, class U>
concept same_as = detail::SameHelper<T, U> && detail::SameHelper<U, T>;
}

}
}