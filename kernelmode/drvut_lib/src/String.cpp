#include "String.h"


namespace drvut {
namespace internal {

String::String() : m_data(nullptr), m_len(0) {
    // Left blank intentionally
}

String::~String() {
    destroy();
}

String::String(String&& other) noexcept
    : m_data(std::exchange(other.m_data, nullptr)), 
      m_len(std::exchange(other.m_len, 0)) {
    // left blank intentionally
}

String& String::operator=(String&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    destroy();

    m_data = std::exchange(other.m_data, nullptr);
    m_len = std::exchange(other.m_len, 0);

    return *this;
}

void String::destroy() {
    if (m_data) {
        delete[] m_data;
    }
}

}
}