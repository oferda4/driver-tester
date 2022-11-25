#include "IoctlHandler.h"

#include "Ioctl.h"

namespace drvut::internal {

namespace {
NTSTATUS handleListTests(TestsManager& manager, BufferView input, BufferView output);
}

NTSTATUS IoctlHandler::handle(TestsManager& manager, uint32_t code, BufferView input, BufferView output) {
    switch (code) {
    case Ioctl::LIST_TESTS:
        return handleListTests(manager, input, output);
    case Ioctl::RUN_TEST:
        return STATUS_SUCCESS;
    default:
        return STATUS_INVALID_PARAMETER_2;
    }
}

namespace {
NTSTATUS handleListTests(TestsManager& manager, BufferView input, BufferView output) {
    if (input.size != sizeof(Ioctl::ListTestsInput)) {
        return STATUS_INVALID_PARAMETER_3;
    }

    return STATUS_SUCCESS;
}
}

}
