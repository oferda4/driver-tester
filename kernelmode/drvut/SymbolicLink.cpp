#include "SymbolicLink.h"

namespace drvut {
namespace internal {

SymbolicLink::SymbolicLink(PCUNICODE_STRING dosDeviceName, PCUNICODE_STRING ntDeviceName)
    : m_dosDeviceName(dosDeviceName), m_ntDeviceName(ntDeviceName) {
    // Left blank intentionally
}

SymbolicLink::SymbolicLink(PCUNICODE_STRING alreadyInitializedDosDeviceName)
    : m_dosDeviceName(alreadyInitializedDosDeviceName), m_ntDeviceName(nullptr) {
    // Left blank intentionally
}

NTSTATUS SymbolicLink::initialize() {
    // we can const cast as this function shouldn't change the value
    return IoCreateSymbolicLink(const_cast<PUNICODE_STRING>(m_dosDeviceName),
                                const_cast<PUNICODE_STRING>(m_ntDeviceName));
}

NTSTATUS SymbolicLink::destroy() {
    return IoDeleteSymbolicLink(const_cast<PUNICODE_STRING>(m_dosDeviceName));
}

}
}
