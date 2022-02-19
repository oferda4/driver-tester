#pragma once

#include <exception>
#include <string>

class Win32Exception : public std::exception {
public:
	Win32Exception(const std::string& message);
};
