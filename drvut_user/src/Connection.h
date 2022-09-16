#pragma once

#include "Defs.h"
#include "Buffer.h"

template<typename T>
concept Connection = requires(T& t, const Buffer& data) {
    { t.recv() } -> std::same_as<Buffer>;
    { t.send(data) } -> std::same_as<void>;
};
