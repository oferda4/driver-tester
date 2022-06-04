#pragma once

#include <gmock/gmock.h>

#include "tester/Exceptions.h"

class FakeException final : public Exception {
public:
    FakeException(std::wstring msg) : Exception(std::move(msg), 0){};
    FakeException() : Exception(L"", 0){};
};
