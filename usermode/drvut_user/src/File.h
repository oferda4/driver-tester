#pragma once

#include "Defs.h"
#include "Handle.h"

template <typename T>
concept FileApi = requires(T& api, 
                           HANDLE handle) {
    { api.close(handle) } -> std::same_as<void>;
};

template <typename T>
concept FileCreationApi = requires(T& api, 
                                   const std::wstring& path) {
    { api.open(path) } -> std::same_as<HANDLE>;
};

template <FileApi Api>
class FileTraits final {
public:
    using Type = HANDLE;
    void close(HANDLE socket);

private:
    Api m_api;
};

template <typename FileApi>
using FileHandleGuard = HandleGuard<FileTraits<FileApi>>;

#include "File.inl"
