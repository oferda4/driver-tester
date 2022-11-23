#pragma once

#include "Defs.h"

#include "Test.h"
#include "Buffer.h"

namespace drvut::internal {

class IoctlHandler final {
public:
    IoctlHandler() = delete;
    static NTSTATUS handle(TestsManager& manager, uint32_t code, BufferView input, BufferView output);
};

}
