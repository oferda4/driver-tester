#pragma once

#include "Defs.h"

#include "Service.h"
#include "Handle.h"

class SCManager final {
public:
	SCManager();
	
	MOVEABLE(SCManager);
	
	Service createService(const std::wstring& name, const std::wstring& pePath);
	Service openService(const std::wstring& name);

private:
	ServiceHandle m_handle;
};
