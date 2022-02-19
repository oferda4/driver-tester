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
	/// You should create and open services using SCManager class 
	Service(ServiceHandle serviceHandle);

	std::optional<ServiceHandle> m_handle;
	bool isStarted;

	friend class SCManager;
};
