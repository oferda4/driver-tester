#pragma once

#include "Defs.h"

#include "Connection.h"

template <typename T>
concept Server = requires(T& server) {
    { T::ConnectionType };
    Connection<typename T::ConnectionType>;
    { server.waitForConnection() } -> std::same_as<typename T::ConnectionType>;
};