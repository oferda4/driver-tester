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

class SCManager;

class Service final {
public:
    Service(ServiceHandle serviceHandle, Passkey<SCManager>);
    MOVEABLE(Service);

    void start();
    void stop();
    void remove();

private:
    ServiceHandle m_handle;
};
