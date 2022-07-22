#pragma once

#include "Defs.h"

namespace drvut {
namespace internal {

class Device final {
public:
    Device(PDEVICE_OBJECT initializedObj);
    Device() = default;
    ~Device();
    Device(Device&& other);
    Device& operator=(Device&& other) noexcept;

    NTSTATUS init(PDRIVER_OBJECT driverObject, const UNICODE_STRING& name);
    void leak();

private:
    bool m_isValid = false;
    PDEVICE_OBJECT m_obj = nullptr;
};

}
}
