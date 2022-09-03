#pragma once

namespace drvut {
namespace internal {

template<typename T>
class Array final {
public:
    Array(size_t count);
    ~Array();

    size_t count();
    T& at(size_t index);

private:
    T* m_data;
    size_t m_count;
};

}
}

#include "Array.inl"
