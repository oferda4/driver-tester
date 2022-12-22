#pragma once

#include "RequestsHandler.h"
#include "Ioctl.h"

template <FileApi FileApiType, IoctlApi<FileApiType> IoctlApiType>
template <FileCreationApi FileCreationApiType>
RequestsHandlerImpl<FileApiType, IoctlApiType>::RequestsHandlerImpl(const std::wstring& deviceName, 
                                                                    FileCreationApiType& creationApi,
                                                                    IoctlApiType ioctlApi)
    : m_device(creationApi.open(deviceName)), m_ioctlApi(std::move(ioctlApi)) {
    // intentionally left blank
}

template <FileApi FileApiType, IoctlApi<FileApiType> IoctlApiType>
ListTestsOutput RequestsHandlerImpl<FileApiType, IoctlApiType>::listTests(const ListTestsInput& input) {
    const auto numberOfTests = getNumberOfTests();

    Buffer ioctlInputBuffer(sizeof(Ioctl::ListTestsInput), 0);
    auto* ioctlInput = reinterpret_cast<Ioctl::ListTestsInput*>(ioctlInputBuffer.data());
    Buffer ioctlOutputBuffer(sizeof(TestInfo) * numberOfTests, 0);
    auto* ioctlOutput = reinterpret_cast<Ioctl::ListTestsOutput*>(ioctlOutputBuffer.data());

    *ioctlInput = Ioctl::ListTestsInput{};
    m_ioctlApi.send(m_device, ioctlInputBuffer, ioctlOutputBuffer);

    return { std::vector<TestInfo>(ioctlOutput->info, ioctlOutput->info + numberOfTests) };
}

template <FileApi FileApiType, IoctlApi<FileApiType> IoctlApiType>
RunTestOutput RequestsHandlerImpl<FileApiType, IoctlApiType>::runTest(const RunTestInput& input) {

}

template <FileApi FileApiType, IoctlApi<FileApiType> IoctlApiType>
uint64_t RequestsHandlerImpl<FileApiType, IoctlApiType>::getNumberOfTests() {
    Buffer ioctlInputBuffer(sizeof(Ioctl::GetNumberOfTestsInput), 0);
    auto* ioctlInput = reinterpret_cast<Ioctl::GetNumberOfTestsInput*>(ioctlInputBuffer.data());
    Buffer ioctlOutputBuffer(sizeof(Ioctl::GetNumberOfTestsOutput), 0);
    auto* ioctlOutput = reinterpret_cast<Ioctl::GetNumberOfTestsOutput*>(ioctlOutputBuffer.data());
    
    *ioctlInput = Ioctl::GetNumberOfTestsInput{};
    m_ioctlApi.send(m_device, ioctlInputBuffer, ioctlOutputBuffer);
    
    return ioctlOutput->numberOfTests;

}