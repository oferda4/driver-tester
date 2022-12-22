#pragma once

#include "File.h"

class WinFileApi final {
public:
    void close(HANDLE handle);
};

class WinFileCreationApi final {
public:
    HANDLE open(const std::wstring& path);
};
