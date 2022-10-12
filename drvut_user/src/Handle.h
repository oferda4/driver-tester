#pragma once

#include "Defs.h"

struct InvalidHandle : std::exception {
    // left blank intentionally
};

template <typename T>
concept HandleTraits = requires(T& controller, 
                                    typename T::Type handle) {
    std::integral<typename T::Type>;
    { controller.close(handle) } -> std::same_as<void>;
};

template <HandleTraits HandleTraitsType>
class HandleGuard {
public:
    HandleGuard(HandleTraitsType traits, HandleTraitsType::Type handle);
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
