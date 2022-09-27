#pragma once

#include "Stream.h"

template <Connection ConnectionType>
StreamImpl<ConnectionType>::StreamImpl(ConnectionType connection) 
    : m_connection(std::move(connection)) {
    // Left blank intentionally
}

template <Connection ConnectionType>
Buffer StreamImpl<ConnectionType>::recv() {
    return Buffer();
}

template <Connection ConnectionType>
void StreamImpl<ConnectionType>::send(const Buffer& data) {

}
