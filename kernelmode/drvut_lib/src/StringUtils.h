#pragma once

#include "Defs.h"

namespace drvut {

class String final {
public:
    String(size_t len);
    template <size_t N>
    String(char const(&data)[N]);

    ~String();

    String(String&& other) noexcept;
    String& operator=(String&& other) noexcept;

    NOCOPY(String);

    char* data();
    const char* data() const;
    size_t size() const;

private:
    void destroy();

    char* m_data;
    size_t m_len;
};

namespace internal {

class StringUtils final {
public:
    StringUtils() = delete;

    static String concat(const String& str1, const String& str2);
};

}
}

#include "StringUtils.inl"
