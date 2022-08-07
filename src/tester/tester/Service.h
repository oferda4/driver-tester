#pragma once

#include "Defs.h"

#include "Handle.h"
#include "Exceptions.h"

struct ServiceHandleTraits {
    using HandleType = SC_HANDLE;
    using ExceptionType = WinAPIException<>;
    
    static constexpr HandleType INVALID_VALUE = nullptr;
    static bool close(HandleType handle);
};

using ServiceHandle = Handle<ServiceHandleTraits>;

class Service final {
public:
    explicit Service(ServiceHandle handle);
    NOCOPY(Service);
    MOVEABLE(Service);

    void start();
    void stop();
    void remove();

private:
    ServiceHandle m_handle;
};

class SCManager final {
public:
    explicit SCManager();
    NOCOPY(SCManager);
    MOVEABLE(SCManager);

    Service create(const std::wstring& name, const std::wstring& pePath);
    Service open(const std::wstring& name);

private:
    ServiceHandle m_handle;
};
