#pragma once

#include "Defs.h"

namespace drvut {
namespace internal {

class Device final {
public:
    ~Device();

    NTSTATUS init(const UNICODE_STRING& name);

private:
    bool m_isInitialized = false;
    PDEVICE_OBJECT m_obj = nullptr;
};

}
}
