#pragma once

#include "Tester.h"

template <ClientCommunicator ClientCommunicatorType, Tracer TracerType>
Tester<ClientCommunicatorType, TracerType>::Tester(std::unique_ptr<ClientCommunicatorType> communicator) : 
    m_communicator(std::move(communicator)) /*, m_converter() */ {
    // Left blank intentionally
}

template <ClientCommunicator ClientCommunicatorType, Tracer TracerType>
void Tester<ClientCommunicatorType, TracerType>::runAllTests() {
    for (const auto& fixture : m_communicator->getFixtures()) {
        // TracerType::info(m_converter.from_bytes(fixture.name));
        runAllTestsInFixture(fixture);
    }
}

template <ClientCommunicator ClientCommunicatorType, Tracer TracerType>
void Tester<ClientCommunicatorType, TracerType>::runAllTestsInFixture(const FixtureInfo& fixture) {
    for (const auto& test : m_communicator->getTests(fixture.id)) {
        auto result = m_communicator->runTest(test.id);
        // TracerType::info(m_converter.from_bytes(test.name) + std::wstring(L": ") + );
    }
}
