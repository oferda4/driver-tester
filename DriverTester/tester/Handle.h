#pragma once

#include "Defs.h"

template<typename HandleTraits>
class Handle final {
public:
	Handle(typename HandleTraits::Type handle);
	~Handle();

	NOCOPY(Handle);
	Handle(Handle&& other) noexcept;
	Handle& operator=(Handle&& other) noexcept;

	operator typename HandleTraits::Type() const;

private:
	typename HandleTraits::Type m_handle;
};

struct ServiceHandleTraits {
	using Type = SC_HANDLE;
	static constexpr Type INVALID_VALUE = nullptr;
	static void close(Type handle) {
		if (!CloseServiceHandle(handle)) {
			traceException(Win32Exception(L"Failed closing service handle"));
		}
	}
};
using ServiceHandle = Handle<ServiceHandleTraits>;

#include "Handle.inl"
