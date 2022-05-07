#pragma once

#include "Tester.h"

template <ServiceAPI API, ExceptionTracer Tracer>
WinTester<API, Tracer>::WinTester(const std::wstring& name, const std::wstring& pePath) : 
    m_installationGuard(name, pePath),
    m_runningGuard(m_installationGuard) {
    // Left blank intentionally
}
