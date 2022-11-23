#include "IoctlHandler.h"

#include "Ioctl.h"

namespace drvut::internal {

NTSTATUS IoctlHandler::handle(TestsManager& manager, uint32_t code, BufferView input, BufferView output) {
    switch (code) {
    case Ioctl::LIST_TESTS:
        break;
    case Ioctl::RUN_TEST:
        break;
    default:
        return STATUS_INVALID_PARAMETER_1;
    }

    return STATUS_SUCCESS;
}

}
