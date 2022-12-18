#pragma once

#include <gmock/gmock.h>

#include "Defs.h"
#include "File.h"

class FakeFileApi final {
public:
    void close(HANDLE) {}
};

class MockFileCreationApi {
public:
    virtual ~MockFileCreationApi() = default;

    MOCK_METHOD(HANDLE, open, (const std::wstring&));
};

class MoveableMockFileCreationApi {
public:
    MoveableMockFileCreationApi()
        : m_mock(std::make_unique<testing::NiceMock<MockFileCreationApi>>()) {}
    virtual ~MoveableMockFileCreationApi() = default;

    HANDLE open(const std::wstring& path) {
        return m_mock->open(path);
    }

    testing::NiceMock<MockFileCreationApi>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::NiceMock<MockFileCreationApi>> m_mock;
};
