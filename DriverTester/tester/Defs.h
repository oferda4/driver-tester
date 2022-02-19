#pragma once

#include <windows.h>

#include <iostream>
#include <string>

#define NOCOPY(className) className(const className&) = delete; \
						  className& operator=(const className&) = delete
#define MOVEABLE(className) className(className&&) noexcept = default; \
						    className& operator=(className&&) noexcept = default

inline void traceException(const std::wstring& msg) {
	std::wcout << "[Exception] " << msg << std::endl;
}

inline void traceException(const std::exception& exc) {
	std::wcout << "[Exception] " << exc.what() << std::endl;
}

inline void traceInfo(const std::wstring& msg) {
	std::wcout << "[Info] " << msg << std::endl;
}

template<typename Func>
void tryExecute(Func f) {
	try {
		f();
	} catch (const std::exception& exc) {
		traceException(exc);
	}
}
