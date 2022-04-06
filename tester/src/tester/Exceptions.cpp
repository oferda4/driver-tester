#include "Exceptions.h"

#include "Defs.h"

using std::wstring;
using std::exception;

Exception::Exception(wstring msg, uint32_t num) : m_msg(std::move(msg)), m_num(num) {
    // Left blank intentionally
}

const wstring& Exception::viewMsg() const {
    return m_msg;
}

uint32_t Exception::getNum() const {
    return m_num;
}

uint32_t StandardLastErrorAPIImpl::getLastError() const {
    return GetLastError();
}
