#pragma once

#include <windows.h>

#include <iostream>
#include <string>

#include "Exceptions.h"

#define NOCOPY(className) className(const className&) = delete; \
						  className& operator=(const className&) = delete
#define MOVEABLE(className) className(className&&) noexcept = default; \
						    className& operator=(className&&) noexcept = default

inline void traceError(const std::wstring& msg) {
	std::wcout << "[Error] " << msg << std::endl;
}

inline void traceException(const Exception& exc) {
	std::wcout << "[Exception] msg - " << exc.viewMsg() << " ; num - " << exc.getNum() << std::endl;
}

inline void traceInfo(const std::wstring& msg) {
	std::wcout << "[Info] " << msg << std::endl;
}

template<typename Func>
void tryExecute(Func f) {
	try {
		f();
	} catch (const Exception& exc) {
		traceException(exc);
	}
}
