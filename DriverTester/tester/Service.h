#pragma once

#include "Defs.h"

#include <optional>

#include "Handle.h"

class Service final {
public:
	~Service();

	MOVEABLE(Service);

	void start();
	
private:
	/// You should create services using SCManager class 
	Service(const ServiceHandle& managerHandle, const std::wstring& name, const std::wstring& pePath);

	std::optional<ServiceHandle> m_handle;
	bool isStarted;

	friend class SCManager;
};
