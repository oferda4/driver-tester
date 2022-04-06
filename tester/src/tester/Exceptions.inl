#pragma once

#include "Exceptions.h"

template <LastErrorAPIImpl T>
WinAPIException<T>::WinAPIException(std::wstring msg, const T& t) : 
    Exception(std::move(msg), t.getLastError()) {
    // Left blank intentionally
}
