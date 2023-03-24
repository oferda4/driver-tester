#include "drvut/internal/StringUtils.h"


namespace drvut {

String::String(size_t len) : m_data(new char[len + 1]), m_len(len) {
    // left blank intentioanlly
}

String::~String() {
    destroy();
}

String::String(String&& other) noexcept
    : m_data(internal::std::exchange(other.m_data, nullptr)), 
      m_len(internal::std::exchange(other.m_len, 0)) {
    // intentionally left blank
}

String& String::operator=(String&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    destroy();

    m_data = internal::std::exchange(other.m_data, nullptr);
    m_len = internal::std::exchange(other.m_len, 0);

    return *this;
}

void String::destroy() {
    if (m_data) {
        delete[] m_data;
    }
}

char* String::data() {
    return m_data;
}

const char* String::data() const {
    return m_data;
}

size_t String::size() const {
    return m_len;
}

namespace internal {

String StringUtils::concat(const String& str1, const String& str2) {
    String newStr(str1.size() + str2.size());
    memcpy(newStr.data(), str1.data(), str1.size());
    memcpy(newStr.data() + str1.size(), str2.data(), str2.size());
    newStr.data()[str1.size() + str2.size()] = '\x00';
    return newStr;
}

}
}