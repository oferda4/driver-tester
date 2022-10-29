#pragma once

#include "Defs.h"

namespace drvut {
namespace internal {

template<typename T>
class Array final {
public:
    Array(size_t size);
    ~Array();

    NOCOPY(Array);
    NOMOVE(Array);

    size_t size() const;
    T& at(size_t index);
    const T& at(size_t index) const;

private:
    T* m_data;
    size_t m_size;
};

}
}

#include "Array.inl"
