#pragma once

#include <memory>
// #include <locale>
// #include <codecvt>

#include "Defs.h"
#include "ClientCommunicator.h"
#include "Tracer.h"

template <ClientCommunicator ClientCommunicatorType, Tracer TracerType>
class Tester {
public:
    Tester(std::unique_ptr<ClientCommunicatorType> communicator);

    void runAllTests();

private:
    void runAllTestsInFixture(const FixtureInfo& fixture);

    std::unique_ptr<ClientCommunicatorType> m_communicator;
    // TODO: Find non deprecated replacement
    // std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> m_converter;
};

#include "Tester.inl"
