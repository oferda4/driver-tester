#pragma once

#include "drvut/Defs.h"
#include "drvut/internal/Traits.h"

namespace drvut {
namespace internal {
namespace std {

template <typename T>
class unique_ptr final {
public:
    template <typename U, typename = std::enable_if_t<
                              std::disjunction_v<std::is_same<U, T>, std::is_base_of<T, U>>>>
    unique_ptr(U* ptr);
    unique_ptr(unique_ptr<T>&& other) noexcept;
    unique_ptr& operator=(unique_ptr<T>&& other) noexcept;

    NOCOPY(unique_ptr);
    ~unique_ptr();

    T* operator->();
    const T* operator->() const;
    T& operator*();
    const T& operator*() const;

    bool operator==(decltype(nullptr)) const;

    T* release();
    T* get();

private:
    T* m_ptr;
};

}
}
}

#include "drvut/internal/Memory.inl"
