#include "drvut/Printable.h"

namespace drvut {

B::B(bool boolean) : m_boolean(boolean) {
    // intentionally left blank
}

B::operator bool() const {
    return m_boolean;
}

String B::toString() const {
    return m_boolean ? String("true") : String("false");
}

}