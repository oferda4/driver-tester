#pragma once

#include "Defs.h"

#include "File.h"
#include "InternalMessages.h"
#include "IoctlApi.h"
#include "RequestsHandler.h"

template <typename T>
concept RequestsHandler = requires(T& t, const InternalMessages::ListTestsInput& listTestsInput,
                                   const InternalMessages::RunTestInput& runTestInput) {
                              {
                                  t.listTests(listTestsInput)
                                  } -> std::same_as<InternalMessages::ListTestsOutput>;
                              {
                                  t.runTest(runTestInput)
                                  } -> std::same_as<InternalMessages::RunTestOutput>;
                          };

template <FileApi FileApiType, IoctlApi<FileApiType> IoctlApiType>
class RequestsHandlerImpl final {
public:
    template <FileCreationApi FileCreationApiType>
    RequestsHandlerImpl(const std::wstring& deviceName, FileCreationApiType& creationApi,
                        IoctlApiType ioctlApi = IoctlApiType());

    InternalMessages::ListTestsOutput listTests(const InternalMessages::ListTestsInput& input);
    InternalMessages::RunTestOutput runTest(const InternalMessages::RunTestInput& input);

private:
    uint64_t getNumberOfTests();

    FileHandleGuard<FileApiType> m_device;
    IoctlApiType m_ioctlApi;
};

#include "RequestsHandler.inl"
