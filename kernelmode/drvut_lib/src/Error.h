#pragma once

#include "StringUtils.h"

namespace drvut {
namespace internal {

class ErrorMessage final {
public:
    static void initialize();
    static void destroy();

    static void append(const String& msg);
    static void reset();
    static const String& view();

private:
    static void assertInitialized();
    static bool isInitialized();

    static String* sm_msg;
};

class ErrorMessageGuard final {
public:
    ErrorMessageGuard();
    ~ErrorMessageGuard();
};

}
}
