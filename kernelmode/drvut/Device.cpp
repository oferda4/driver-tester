#include "Device.h"

#include "drvut/internal/Utility.h"

namespace drvut {
namespace internal {

Device::Device(PDEVICE_OBJECT initializedObj) : m_obj(initializedObj) {
    // Left blank intentionally
}

Device::Device(PDRIVER_OBJECT driver, PCUNICODE_STRING name)
    : m_obj(nullptr), m_driver(driver), m_name(name) {
    // Left blank intentionally
}

NTSTATUS Device::initialize() {
    const NTSTATUS status =
        IoCreateDevice(m_driver, 0, const_cast<PUNICODE_STRING>(m_name), FILE_DEVICE_UNKNOWN,
                       FILE_DEVICE_SECURE_OPEN, FALSE, &m_obj);
    CHECK_AND_RETHROW(status);
    return STATUS_SUCCESS;
}

NTSTATUS Device::destroy() {
    IoDeleteDevice(m_obj);
    return STATUS_SUCCESS;
}

}
}