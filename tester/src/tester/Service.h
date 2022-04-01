#pragma once

#include "Defs.h"

#include "Handle.h"

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
