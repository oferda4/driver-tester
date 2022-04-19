#pragma once

#include "Service.h"

#include "Exceptions.h"

template <typename ControllerType>
    requires ServiceController<ControllerType>
Service<ControllerType>::Service(ControllerType controller) : 
    m_controller(std::move(controller)) {
    // Left blank intentionally
}

template <typename ControllerType>
    requires ServiceController<ControllerType>
void Service<ControllerType>::start() {
    if (!m_controller.start()) {
        throw ControllerType::ExceptionType(L"Failed starting service");
    }
}
template <typename ControllerType>
    requires ServiceController<ControllerType>
void Service<ControllerType>::stop() {
    if (!m_controller.stop()) {
        throw ControllerType::ExceptionType(L"Failed stopping service");
    }
}

template <typename ControllerType>
    requires ServiceController<ControllerType>
void Service<ControllerType>::remove() {
    if (!m_controller.remove()) {
        throw ControllerType::ExceptionType(L"Failed deleting service");
    }
}
