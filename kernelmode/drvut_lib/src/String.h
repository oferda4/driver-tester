#pragma once

#include "Defs.h"

namespace drvut {
namespace internal {

class String final {
public:
    String();
    template <size_t N>
    String(char data[N]);

    ~String();

    String(String&& other) noexcept;
    String& operator=(String&& other) noexcept;

    NOCOPY(String);

private:
    void destroy();

    char* m_data;
    size_t m_len;
};

}
}

#include "String.inl"
