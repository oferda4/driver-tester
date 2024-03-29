#pragma once

#include "Defs.h"

#include "Buffer.h"

template <typename T>
concept Connection = requires(T& t, const Buffer& data, size_t size) {
                         { t.recv(size) } -> std::same_as<Buffer>;
                         { t.send(data) } -> std::same_as<size_t>;
                     };
