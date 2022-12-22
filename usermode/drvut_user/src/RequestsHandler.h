#pragma once

#include "Defs.h"
#include "InternalMessages.h"
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
    template <FileCreationApi FileCreationApiType>
    RequestsHandlerImpl(const std::wstring& deviceName, FileCreationApiType& creationApi, IoctlApiType ioctlApi = IoctlApiType());

    ListTestsOutput listTests(const ListTestsInput& input);
    RunTestOutput runTest(const RunTestInput& input);

private:
    uint64_t getNumberOfTests();

    FileHandleGuard<FileApiType> m_device;
    IoctlApiType m_ioctlApi;
};

#include "RequestsHandler.inl"
