#include "Error.h"

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
    assertInitialized();
    *sm_msg = "";
}

const String& ErrorMessage::view() {
    assertInitialized();
    return *sm_msg;
}

void ErrorMessage::assertInitialized() {
    if (!sm_msg) {
        ExRaiseStatus(STATUS_ACCESS_VIOLATION);
    }
}

ErrorMessageGuard::ErrorMessageGuard() {
    ErrorMessage::initialize();
}

ErrorMessageGuard::~ErrorMessageGuard() {
    ErrorMessage::destroy();
}

}
}