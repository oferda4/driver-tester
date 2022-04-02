#pragma once

#include "Exceptions.h"

template <LastErrorAPIImpl T>
WinAPIException<T>::WinAPIException(std::wstring msg) : 
    Exception(std::move(msg), T::getLastError()) {
    // Left blank intentionally
}
