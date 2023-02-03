#pragma once

#include "File.h"
#include "Buffer.h"

template <typename T, typename FileApiType>
concept IoctlApi = requires(T& api, FileHandleGuard<FileApiType>& device, uint32_t code,
                            const Buffer& input, Buffer& output) {
                       FileApi<FileApiType>;
                       { api.send(device, code, input, output) } -> std::same_as<void>;
                   };
