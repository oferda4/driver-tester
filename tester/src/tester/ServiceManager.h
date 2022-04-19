#pragma once

#include "Defs.h"

#include "Service.h"
#include "Handle.h"

class SCManager final {
public:
    SCManager();

    MOVEABLE(SCManager);

    WinService create(const std::wstring& name, const std::wstring& pePath);
    WinService open(const std::wstring& name);

private:
    static WinService createServiceObject(ServiceHandle serviceHandle);

    ServiceHandle m_handle;
};
