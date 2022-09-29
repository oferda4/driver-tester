#pragma once

#include "Defs.h"

#include "Connection.h"

template <typename T>
concept Server = requires(T& server) {
    // TODO: improve these constrains
    { T::ConnectionType } -> Connection;
    { server.waitForConnection() } -> Connection;
};