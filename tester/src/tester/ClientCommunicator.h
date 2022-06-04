#pragma once

#include <vector>

#include "Defs.h"
#include "Messages.h"
#include "Driver.h"

template <typename T>
concept ClientCommunicator = requires(T& t, uint32_t fixtureId, uint32_t testId) {
    { t.getFixtures() } -> std::same_as<std::vector<FixtureInfo>>;
    { t.getTests(fixtureId) } -> std::same_as<std::vector<TestInfo>>;
    { t.runTest(testId) } -> std::same_as<TestResult>;
};

template <ServiceAPI API = WinServiceAPI, ExceptionTracer Tracer = StdOutTracer>
class WinClientCommunicator {
public:
    WinClientCommunicator(const std::wstring& name, const std::wstring& pePath);

private:
    DriverInstallationGuard<API, Tracer> m_installationGuard;
    DriverRunningGuard<API, Tracer> m_runningGuard;
};

#include "ClientCommunicator.inl"
