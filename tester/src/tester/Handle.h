#pragma once

#include "Defs.h"
#include "Tracer.h"

template <typename HandleTraitsType, typename TracerType = StdOutTracer>
    requires HandleTraits<HandleTraitsType> && ExceptionTracer<TracerType>
class Handle final {
public:
    Handle(typename HandleTraitsType::HandleType handle);
    ~Handle();

    NOCOPY(Handle);
    Handle(Handle&& other) noexcept;
    Handle& operator=(Handle&& other) noexcept;

    operator typename HandleTraitsType::HandleType() const;

private:
    typename HandleTraitsType::HandleType m_handle;
};

template <typename T>
concept HandleTraits = requires(T, typename T::HandleType handle) {
    { T::HandleType };
    requires std::derived_from<typename T::ExceptionType, Exception>;
    { T::INVALID_VALUE } -> std::convertible_to<typename T::HandleType>;
    { T::close(handle) } -> std::same_as<bool>;
};

#include "Handle.inl"
