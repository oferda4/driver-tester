#pragma once

#include "ClientCommunicator.h"

template <ServiceAPI API, ExceptionTracer Tracer>
WinClientCommunicator<API, Tracer>::WinClientCommunicator(const std::wstring& name, const std::wstring& pePath) : 
    m_installationGuard(name, pePath),
    m_runningGuard(m_installationGuard) {
    // Left blank intentionally
}
