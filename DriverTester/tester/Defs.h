#pragma once

#include <windows.h>

#include <iostream>
#include <string>

#define NOCOPY(className) className(const className&) = delete; \
						  className& operator=(const className&) = delete
#define MOVEABLE(className) className(className&&) noexcept = default; \
						    className& operator=(className&&) noexcept = default

inline void traceException(const std::string& msg) {
	std::cout << "[Exception] " << msg << std::endl;
}

inline void traceException(const std::exception& exc) {
	std::cout << "[Exception] " << exc.what() << std::endl;
}

inline void traceInfo(const std::string& msg) {
	std::cout << "[Info] " << msg << std::endl;
}
