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

template <typename T>
concept LastErrorAPIImpl = requires(T) {
    { T::getLastError() } -> std::same_as<uint32_t>;
};

struct StandardLastErrorAPIImpl {
    static uint32_t getLastError();
};

template <LastErrorAPIImpl T = StandardLastErrorAPIImpl>
class WinAPIException : public Exception {
public:
    WinAPIException(std::wstring msg);
};

#include "Exceptions.inl"
