#pragma once

#include <string>

class Exception {
public:
    Exception(std::wstring msg, uint32_t num);
    virtual ~Exception() = default;

    const std::wstring& viewMsg() const;
    uint32_t getNum() const;

private:
    std::wstring m_msg;
    uint32_t m_num;
};

class WinAPIException : public Exception {
public:
    WinAPIException(std::wstring msg);
};
