#pragma once

#include "Defs.h"
#include "Resource.h"

namespace drvut {
namespace internal {

class Device final {
public:
    Device(PDEVICE_OBJECT initializedObj);
    Device(PDRIVER_OBJECT driver, PCUNICODE_STRING name);
    MOVEABLE(Device);
    NOCOPY(Device);

    NTSTATUS initialize();
    NTSTATUS destroy();

private:
    PDEVICE_OBJECT m_obj;
    PDRIVER_OBJECT m_driver;
    PCUNICODE_STRING m_name;
};

using DeviceGuard = ResourceGuard<Device>;

}
}
