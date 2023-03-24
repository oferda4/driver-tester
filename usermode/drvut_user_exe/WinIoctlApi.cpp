#include "WinIoctlApi.h"

#include "CastUtils.h"
#include "WinExceptions.h"

void WinIoctlApi::send(FileHandleGuard<WinFileApi>& device, uint32_t code, const Buffer& input,
                       Buffer& output) {
    if (!DeviceIoControl(*device, code,
                         const_cast<byte*>(input.data()), // this api should not change the input
                         CastUtils::cast<uint32_t>(input.size()), output.data(),
                         CastUtils::cast<uint32_t>(output.size()), nullptr, nullptr)) {
        throw Win32Exception();
    }
}