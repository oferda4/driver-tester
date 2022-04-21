#pragma once

#include "Defs.h"

#include "Handle.h"
#include "Exceptions.h"
#include "Passkey.h"

struct ServiceHandleTraits {
    MOVEABLE(ServiceHandleTraits);

    using HandleType = SC_HANDLE;
    using ExceptionType = WinAPIException<>;
    
    static constexpr HandleType INVALID_VALUE = nullptr;
    static bool close(HandleType handle);
};

using ServiceHandle = Handle<ServiceHandleTraits>;

template <typename T>
concept ServiceAPI = requires(T, typename T::HandleType& handle) {
    { T::start(handle) } -> std::same_as<void>;
    { T::stop(handle) } -> std::same_as<void>;
    { T::remove(handle) } -> std::same_as<void>;
};

struct WinServiceAPI {
    using HandleType = ServiceHandle;

    void start(HandleType& handle);
    void stop(HandleType& handle);
    void remove(HandleType& handle);
};
