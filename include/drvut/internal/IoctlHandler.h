#pragma once

#include "drvut/Defs.h"

#include "drvut/Test.h"
#include "drvut/internal/Buffer.h"

namespace drvut::internal {

class IoctlHandler final {
public:
    IoctlHandler() = delete;
    static NTSTATUS handle(TestsManager& manager, uint32_t code, BufferView input,
                           BufferView output);
};

}
