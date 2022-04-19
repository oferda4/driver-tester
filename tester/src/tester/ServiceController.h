#pragma once

#include "Defs.h"

#include "Handle.h"
#include "Exceptions.h"
#include "Handle.h"

struct ServiceHandleTraits {
    using HandleType = SC_HANDLE;
    using ExceptionType = WinAPIException<>;
    
    static constexpr HandleType INVALID_VALUE = nullptr;
    static bool close(HandleType handle);
};

using ServiceHandle = Handle<ServiceHandleTraits>;

template <typename API, typename HandleTraitsType>
    requires ServiceAPI<API, HandleTraitsType>
class ServiceController final {
public:
    ServiceController(Handle<HandleTraitsType> handle);
    NOCOPY(ServiceController);
    MOVEABLE(ServiceController);

    void start();
    void stop();
    void remove();

private:
    Handle<HandleTraitsType> m_handle;
};

template <typename API, typename HandleTraitsType>
concept ServiceAPI = requires(API, HandleTraitsType) {
    requires HandleTraits<HandleTraitsType>;
    // { API::start(Handle<HandleTraitsType>(HandleTraitsType::INVALID_HANDLE)) } -> std::same_as<bool>;
    // { API::stop(Handle<HandleTraitsType>(HandleTraitsType::INVALID_HANDLE)) } -> std::same_as<bool>;
    // { API::remove(Handle<HandleTraitsType>(HandleTraitsType::INVALID_HANDLE)) } -> std::same_as<bool>;
};

class WinServiceAPI final {
public:
    static bool start(ServiceHandle handle);
    static bool stop(ServiceHandle handle);
    static bool remove(ServiceHandle handle);
};

using WinServiceController = ServiceController<WinServiceAPI, ServiceHandle>;

#include "ServiceController.inl"
