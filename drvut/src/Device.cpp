#include "Device.h"

namespace drvut {
namespace internal {

Device::~Device() {
    if (m_isInitialized) {

    }

}

NTSTATUS Device::init(const UNICODE_STRING& name) {
    IoCreateDevice(DriverObject, 0, const_cast<PUNICODE_STRING>(&NT_DEVICE_NAME), FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &deviceObject)
    m_isInitialized = true;
    return STATUS_SUCCESS;
}

}
}