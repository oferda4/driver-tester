#pragma once

#include "ServiceController.h"

#include "Exceptions.h"

template <typename API, typename HandleTraitsType>
    requires ServiceAPI<API, HandleTraitsType>
ServiceController<API, HandleTraitsType>::ServiceController(Handle<HandleTraitsType> handle) : 
    m_handle(std::move(handle)) {
    // Left blank intentionally
}

template <typename API, typename HandleTraitsType>
    requires ServiceAPI<API, HandleTraitsType>
void ServiceController<API, HandleTraitsType>::start() {
    if (!API::start(m_handle)) {
        throw HandleTraitsType::ExceptionType(L"Failed starting service");
    }
}

template <typename API, typename HandleTraitsType>
    requires ServiceAPI<API, HandleTraitsType>
void ServiceController<API, HandleTraitsType>::stop() {
    if (!API::stop(m_handle)) {
        throw HandleTraitsType::ExceptionType(L"Failed stopping service");
    }
}

template <typename API, typename HandleTraitsType>
    requires ServiceAPI<API, HandleTraitsType>
void ServiceController<API, HandleTraitsType>::remove() {
    if (!API::remove(m_handle)) {
        throw HandleTraitsType::ExceptionType(L"Failed deleting service");
    }
}
