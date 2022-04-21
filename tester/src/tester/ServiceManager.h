#pragma once

#include "Defs.h"

#include "Service.h"
#include "Handle.h"

class SCManager final {
public:
    SCManager();

    MOVEABLE(SCManager);

    ServiceHandle create(const std::wstring& name, const std::wstring& pePath);
    ServiceHandle open(const std::wstring& name);

private:
    ServiceHandle m_handle;
};
