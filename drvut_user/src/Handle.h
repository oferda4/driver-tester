#pragma once

#include "Defs.h"

struct InvalidHandle : std::exception {
    // left blank intentionally
};

template <typename T>
concept HandleTraits = requires(T& traits, 
                                typename T::Type handle) {
    sizeof(typename T::Type) == sizeof(size_t);
    { traits.close(handle) } -> std::same_as<void>;
};

template <HandleTraits HandleTraitsType>
class HandleGuard {
public:
    HandleGuard(HandleTraitsType traits, HandleTraitsType::Type handle);
    template <typename = std::enable_if_t<std::is_default_constructible_v<HandleTraitsType>>>
    HandleGuard(HandleTraitsType::Type handle);
    ~HandleGuard();

    NO_COPY(HandleGuard);
    HandleGuard(HandleGuard&& other) noexcept;
    HandleGuard& operator=(HandleGuard&& other) noexcept;

    typename HandleTraitsType::Type operator*();
    const typename HandleTraitsType::Type operator*() const;

private:
    void validate() const;

    HandleTraitsType m_traits;
    typename HandleTraitsType::Type m_handle;
    bool m_isValid;
};

#include "Handle.inl"
