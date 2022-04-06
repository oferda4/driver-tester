#pragma once

#include "Defs.h"

#include "Handle.h"
#include "Exceptions.h"

class ServiceHandleTraits {
public:
    MOVEABLE(ServiceHandleTraits);

    using HandleType = SC_HANDLE;
    using ExceptionType = WinAPIException<>;
    
    static constexpr HandleType INVALID_VALUE = nullptr;
    static bool close(HandleType handle);
};

using ServiceHandle = Handle<ServiceHandleTraits>;

class Service final {
public:
    MOVEABLE(Service);

    void start();
    void stop();
    void remove();

private:
    /// You should create and open services using SCManager class
    Service(ServiceHandle serviceHandle);

    ServiceHandle m_handle;

    friend class SCManager;
};
