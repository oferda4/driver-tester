#include "WinIoctlApi.h"

#include "WinExceptions.h"
#include "CastUtils.h"

#include <iostream>

void WinIoctlApi::send(FileHandleGuard<WinFileApi>& device, uint32_t code, const Buffer& input,
                       Buffer& output) {
    std::cout << "Sending Ioctl: " << code << std::endl;
    if (!DeviceIoControl(*device, code,
                         const_cast<byte*>(input.data()), // this api should not change the input
                         CastUtils::cast<uint32_t>(input.size()), output.data(),
                         CastUtils::cast<uint32_t>(output.size()), nullptr, nullptr)) {
        std::cout << "Ioctl failed with: " << GetLastError() << std::endl;
        throw Win32Exception();
    }
}