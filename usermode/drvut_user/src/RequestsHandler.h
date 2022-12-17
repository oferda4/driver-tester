#pragma once

#include "Defs.h"
#include "Messages.h"
#include "RequestsHandler.h"
#include "File.h"
#include "IoctlApi.h"

template<typename T>
concept RequestsHandler = requires(T& t, 
                                   const ListTestsInput& listTestsInput,
                                   const RunTestInput& runTestInput) {
    { t.listTests(listTestsInput) } -> std::same_as<ListTestsOutput>;
    { t.runTest(runTestInput) } -> std::same_as<RunTestOutput>;
};

template <FileApi FileApiType, IoctlApi<FileApiType> IoctlApiType>
class RequestsHandlerImpl final {
public:
    RequestsHandlerImpl(const std::wstring& deviceName, FileApiType& creationApi);

    ListTestsOutput listTests(const ListTestsInput& input);
    RunTestOutput runTest(const RunTestInput& input);

private:
    uint32_t getNumberOfTests();

    FileHandleGuard<FileApiType> m_device;
    IoctlApiType m_ioctlApi;
};

#include "RequestsHandler.inl"
