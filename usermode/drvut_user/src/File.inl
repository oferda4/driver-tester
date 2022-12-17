#pragma once

#include "File.h"

template <FileApi Api>
void FileTraits<Api>::close(HANDLE socket) {
    m_api.close();
}
