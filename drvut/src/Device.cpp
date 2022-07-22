#include "Device.h"

#include "Utility.h"

namespace drvut {
namespace internal {

Device::Device(PDEVICE_OBJECT initializedObj) : m_obj(initializedObj), m_isValid(true) {
    // Left blank intentionally
}

Device::~Device() {
    if (m_isValid) {
        IoDeleteDevice(m_obj);
    }

}

Device::Device(Device&& other) : 
    m_obj(std::exchange(other.m_obj, nullptr)),
    m_isValid(std::exchange(other.m_isValid, false)) {
    // Left blank intentionally
}

Device& Device::operator=(Device&& other) noexcept {
    m_obj = std::exchange(other.m_obj, nullptr);
    m_isValid = std::exchange(other.m_isValid, false);
    return *this;
}

NTSTATUS Device::init(PDRIVER_OBJECT driverObject, const UNICODE_STRING& name) {
    const NTSTATUS status = IoCreateDevice(driverObject, 0, const_cast<PUNICODE_STRING>(&name), FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &m_obj);
    if (!status) {
        return status;
    }
    m_isValid = true;
    return STATUS_SUCCESS;
}

void Device::leak() {
    m_obj = nullptr;
    m_isValid = false;
}

}
}