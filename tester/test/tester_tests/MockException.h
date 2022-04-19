#pragma once

class MockException final : public Exception {
public:
    MockException(std::wstring msg);
};
