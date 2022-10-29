#pragma once

#include "Defs.h"

namespace drvut {
namespace internal {
namespace std {

template<typename T>
class unique_ptr final {
public:
    unique_ptr(T* ptr);
    unique_ptr(unique_ptr<T>&& other);
    unique_ptr& operator=(unique_ptr<T>&& other);

    NOCOPY(unique_ptr);
    ~unique_ptr();

    T* operator->();
    const T* operator->() const;
    T& operator*();
    const T& operator*() const;

    bool operator==(decltype(nullptr)) const;

private:
    T* m_ptr;
};

}
}
}

#include "Memory.inl"
