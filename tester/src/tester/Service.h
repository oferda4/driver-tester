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

template <typename ControllerType>
    requires ServiceController<ControllerType>
class Service final {
public:
    Service(ControllerType controller);
    MOVEABLE(Service);

    void start();
    void stop();
    void remove();

private:
    ControllerType m_controller;
};

template <typename T>
concept ServiceController = requires(T t) {
    { t.start() } -> std::same_as<bool>;
    { t.stop() } -> std::same_as<bool>;
    { t.remove() } -> std::same_as<bool>;
    requires std::derived_from<typename T::ExceptionType, Exception>;
};

class WinServiceController final {
public:
    using ExceptionType = WinAPIException<>;

    WinServiceController(ServiceHandle handle);

    bool start();
    bool stop();
    bool remove();
    
private:
    ServiceHandle m_handle;
};

using WinService = Service<WinServiceController>;

#include "Service.inl"
