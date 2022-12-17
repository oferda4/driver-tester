#include "IoctlHandler.h"

#include "Ioctl.h"

namespace drvut::internal {

namespace {
NTSTATUS handleGetNumberOfTests(TestsManager& manager, BufferView input, BufferView output);
NTSTATUS handleListTests(TestsManager& manager, BufferView input, BufferView output);
NTSTATUS handleRunTest(TestsManager& manager, BufferView input, BufferView output);

template <typename ParameterType, NTSTATUS INVALID_PARAMETER_ERROR_CODE>
NTSTATUS validateParameterBuffer(BufferView buffer);
template <NTSTATUS INVALID_PARAMETER_ERROR_CODE>
NTSTATUS validateParameterBuffer(BufferView buffer, uint64_t parameterSize);

template <typename InputType>
auto validateInputBuffer(BufferView buffer) { return validateParameterBuffer<InputType, STATUS_INVALID_PARAMETER_3>(buffer); }
template <typename OutputType>
auto validateOutputBuffer(BufferView buffer) { return validateParameterBuffer<OutputType, STATUS_INVALID_PARAMETER_4>(buffer); }

auto validateListTestsInput(BufferView buffer) { return validateInputBuffer<Ioctl::ListTestsInput>(buffer); }
NTSTATUS validateListTestsOutput(BufferView buffer, uint64_t numberOfTests) { return validateParameterBuffer<STATUS_INVALID_PARAMETER_4>(buffer, numberOfTests * sizeof(TestInfo)); }
auto validateGetNumberOfTestsInput(BufferView buffer) { return validateInputBuffer<Ioctl::GetNumberOfTestsInput>(buffer); }
auto validateGetNumberOfTestsOutput(BufferView buffer) { return validateOutputBuffer<Ioctl::GetNumberOfTestsOutput>(buffer); }
auto validateRunTestInput(BufferView buffer) { return validateInputBuffer<Ioctl::RunTestInput>(buffer); }
auto validateRunTestOutput(BufferView buffer) { return validateOutputBuffer<Ioctl::RunTestOutput>(buffer); }
}

NTSTATUS IoctlHandler::handle(TestsManager& manager, uint32_t code, BufferView input, BufferView output) {
    switch (code) {
    case Ioctl::GET_NUMBER_OF_TESTS:
        return handleGetNumberOfTests(manager, input, output);
    case Ioctl::LIST_TESTS:
        return handleListTests(manager, input, output);
    case Ioctl::RUN_TEST:
        return handleRunTest(manager, input, output);
    default:
        return STATUS_INVALID_PARAMETER_2;
    }
}

namespace {

NTSTATUS handleGetNumberOfTests(TestsManager& manager, BufferView input, BufferView output) {
    CHECK_AND_RETHROW(validateGetNumberOfTestsInput(input));
    CHECK_AND_RETHROW(validateGetNumberOfTestsOutput(output));

    auto* getNumberOfTestsOutput = static_cast<Ioctl::GetNumberOfTestsOutput*>(output.data);
    getNumberOfTestsOutput->numberOfTests = manager.getNumberOfTests();

    return STATUS_SUCCESS;
}

NTSTATUS handleListTests(TestsManager& manager, BufferView input, BufferView output) {
    CHECK_AND_RETHROW(validateListTestsInput(input));

    const auto tests = manager.list();
    CHECK_AND_RETHROW(validateListTestsOutput(output, tests.size()));

    auto* listTestsOutput = static_cast<Ioctl::ListTestsOutput*>(output.data);
    for (uint32_t i = 0; i < tests.size(); i++) {
        memcpy(&listTestsOutput[i], &tests.at(i), sizeof(TestInfo));
    }

    return STATUS_SUCCESS;
}

NTSTATUS handleRunTest(TestsManager& manager, BufferView input, BufferView output) {
    CHECK_AND_RETHROW(validateRunTestInput(input));
    CHECK_AND_RETHROW(validateRunTestOutput(output));

    auto* runTestInput = static_cast<Ioctl::RunTestInput*>(input.data);
    auto* runTestsOutput = static_cast<Ioctl::RunTestOutput*>(output.data);

    runTestsOutput->result = manager.run(runTestInput->testId).status;

    return STATUS_SUCCESS;
}

template <typename ParameterType, NTSTATUS INVALID_PARAMETER_ERROR_CODE>
NTSTATUS validateParameterBuffer(BufferView buffer) {
    return validateParameterBuffer<INVALID_PARAMETER_ERROR_CODE>(buffer, sizeof(ParameterType));
}

template <NTSTATUS INVALID_PARAMETER_ERROR_CODE>
NTSTATUS validateParameterBuffer(BufferView buffer, uint64_t parameterSize) {
    return buffer.size == parameterSize ? STATUS_SUCCESS : INVALID_PARAMETER_ERROR_CODE;
}

}
}
