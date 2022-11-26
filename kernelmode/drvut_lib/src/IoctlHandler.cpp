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
    // we are currently not using the input. However we still want 
    // to make sure the proper struct was passed for validation.
    UNREFERENCED_PARAMETER(input);
    if (input.size != sizeof(Ioctl::ListTestsInput)) {
        return STATUS_INVALID_PARAMETER_3;
    }

    auto* listTestsOutput = static_cast<Ioctl::ListTestsOutput*>(output.data);
    const auto tests = manager.list();

    if (output.size < sizeof(Ioctl::ListTestsOutput::numberOfTests)) {
        // you must have at least enough size for the number of tests
        return STATUS_INVALID_PARAMETER_4;
    }
    listTestsOutput->numberOfTests = tests.size();
     
    const uint64_t testsThatFitsInOutput = min(tests.size(), 
                                               (output.size - sizeof(Ioctl::ListTestsOutput::numberOfTests)) / sizeof(TestInfo));
    TestInfo* testsOutput = &listTestsOutput->info[0];
    for (uint32_t i = 0; i < testsThatFitsInOutput; i++) {
        memcpy(testsOutput + i, &tests.at(i), sizeof(TestInfo));
    }

    if (testsThatFitsInOutput < tests.size()) {
        return STATUS_BUFFER_TOO_SMALL;
    }

    return STATUS_SUCCESS;
}
}

}
