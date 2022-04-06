#pragma once

#include "Defs.h"

template <typename T>
    requires HandleTraits<T>
class Handle final {
public:
    Handle(typename T::HandleType handle);
    ~Handle();

    NOCOPY(Handle);
    Handle(Handle&& other) noexcept;
    Handle& operator=(Handle&& other) noexcept;

    operator typename T::HandleType() const;

private:
    typename T::HandleType m_handle;
};

template <typename T>
concept HandleTraits = requires(T) {
    { T::HandleType };
    requires std::derived_from<typename T::ExceptionType, Exception>;
    { T::INVALID_VALUE } -> std::convertible_to<typename T::HandleType>;
    { T::close(T::INVALID_VALUE) } -> std::same_as<bool>;
};

#include "Handle.inl"
