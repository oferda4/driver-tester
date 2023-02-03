#pragma once

#include "IoctlApi.h"
#include "WinFile.h"

class WinIoctlApi final {
public:
    void send(FileHandleGuard<WinFileApi>& device, uint32_t code, const Buffer& input,
              Buffer& output);
};
