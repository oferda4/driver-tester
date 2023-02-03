#include "WinFile.h"

#include "WinExceptions.h"

void WinFileApi::close(HANDLE handle) {
    if (!CloseHandle(handle)) {
        throw Win32Exception();
    }
}

HANDLE WinFileCreationApi::open(const std::wstring& path) {
    const HANDLE fileHandle =
        CreateFile(path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                   nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        throw Win32Exception();
    }
    return fileHandle;
}
