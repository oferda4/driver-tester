#include "drvut/internal/Error.h"

namespace drvut {
namespace internal {

String* ErrorMessage::sm_msg = nullptr;

void ErrorMessage::initialize() {
    sm_msg = new String("");
}

void ErrorMessage::destroy() {
    sm_msg = nullptr;
}

void ErrorMessage::append(const String& msg) {
    assertInitialized();
    *sm_msg = StringUtils::concat(*sm_msg, msg);
}

void ErrorMessage::reset() {
    if (isInitialized()) {
        *sm_msg = "";
    }
}

const String& ErrorMessage::view() {
    assertInitialized();
    return *sm_msg;
}

void ErrorMessage::assertInitialized() {
    if (!isInitialized()) {
        ExRaiseStatus(STATUS_ACCESS_VIOLATION);
    }
}

bool ErrorMessage::isInitialized() {
    return sm_msg != nullptr;
}

ErrorMessageGuard::ErrorMessageGuard() {
    ErrorMessage::initialize();
}

ErrorMessageGuard::~ErrorMessageGuard() {
    ErrorMessage::destroy();
}

}
}