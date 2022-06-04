#pragma once

#include <memory>

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
};

#include "Tester.inl"
