#pragma once

#include "Defs.h"
#include "Driver.h"

template <typename T>
concept Tester = requires(T& t) {
    { t.runAllTests() } -> std::same_as<void>;
};

template <ServiceAPI API, ExceptionTracer Tracer>
class WinTester {
public:
    WinTester(const std::wstring& name, const std::wstring& pePath);

private:
    DriverInstallationGuard<API, Tracer> m_installationGuard;
    DriverRunningGuard<API, Tracer> m_runningGuard;
};

#include "Tester.inl"
