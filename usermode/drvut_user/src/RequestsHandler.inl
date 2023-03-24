#pragma once

#include "Ioctl.h"
#include "RequestsHandler.h"

template <FileApi FileApiType, IoctlApi<FileApiType> IoctlApiType>
template <FileCreationApi FileCreationApiType>
RequestsHandlerImpl<FileApiType, IoctlApiType>::RequestsHandlerImpl(
    const std::wstring& deviceName, FileCreationApiType& creationApi, IoctlApiType ioctlApi)
    : m_device(creationApi.open(deviceName)), m_ioctlApi(std::move(ioctlApi)) {
    // intentionally left blank
}

template <FileApi FileApiType, IoctlApi<FileApiType> IoctlApiType>
InternalMessages::ListTestsOutput RequestsHandlerImpl<FileApiType, IoctlApiType>::listTests(
    const InternalMessages::ListTestsInput& input) {
    const auto numberOfTests = getNumberOfTests();

    Buffer ioctlInputBuffer(sizeof(Ioctl::ListTestsInput), 0);
    auto* ioctlInput = reinterpret_cast<Ioctl::ListTestsInput*>(ioctlInputBuffer.data());
    Buffer ioctlOutputBuffer(sizeof(Ioctl::TestInfo) * numberOfTests, 0);
    auto* ioctlOutput = reinterpret_cast<Ioctl::ListTestsOutput*>(ioctlOutputBuffer.data());

    *ioctlInput = Ioctl::ListTestsInput{};
    m_ioctlApi.send(m_device, Ioctl::LIST_TESTS, ioctlInputBuffer, ioctlOutputBuffer);

    std::vector<InternalMessages::TestInfo> itnernalTestInfoFormat;
    for (uint32_t i = 0; i < numberOfTests; i++) {
        itnernalTestInfoFormat.push_back({ ioctlOutput->info[i].id, ioctlOutput->info[i].name });
    }

    return { std::move(itnernalTestInfoFormat) };
}

template <FileApi FileApiType, IoctlApi<FileApiType> IoctlApiType>
InternalMessages::RunTestOutput RequestsHandlerImpl<FileApiType, IoctlApiType>::runTest(
    const InternalMessages::RunTestInput& input) {
    Buffer ioctlInputBuffer(sizeof(Ioctl::RunTestInput), 0);
    auto* ioctlInput = reinterpret_cast<Ioctl::RunTestInput*>(ioctlInputBuffer.data());
    Buffer ioctlOutputBuffer(sizeof(Ioctl::RunTestOutput), 0);
    auto* ioctlOutput = reinterpret_cast<Ioctl::RunTestOutput*>(ioctlOutputBuffer.data());

    ioctlInput->testId = input.testId;
    m_ioctlApi.send(m_device, Ioctl::RUN_TEST, ioctlInputBuffer, ioctlOutputBuffer);

    return { { ioctlOutput->result.passed, ioctlOutput->result.msg } };
}

template <FileApi FileApiType, IoctlApi<FileApiType> IoctlApiType>
uint64_t RequestsHandlerImpl<FileApiType, IoctlApiType>::getNumberOfTests() {
    Buffer ioctlInputBuffer(sizeof(Ioctl::GetNumberOfTestsInput), 0);
    auto* ioctlInput = reinterpret_cast<Ioctl::GetNumberOfTestsInput*>(ioctlInputBuffer.data());
    Buffer ioctlOutputBuffer(sizeof(Ioctl::GetNumberOfTestsOutput), 0);
    auto* ioctlOutput = reinterpret_cast<Ioctl::GetNumberOfTestsOutput*>(ioctlOutputBuffer.data());

    *ioctlInput = Ioctl::GetNumberOfTestsInput{};
    m_ioctlApi.send(m_device, Ioctl::GET_NUMBER_OF_TESTS, ioctlInputBuffer, ioctlOutputBuffer);

    return ioctlOutput->numberOfTests;
}
