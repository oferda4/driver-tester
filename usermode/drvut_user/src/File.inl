#pragma once

#include "File.h"

template <FileApi Api>
void FileTraits<Api>::close(HANDLE handle) {
    m_api.close(handle);
}
