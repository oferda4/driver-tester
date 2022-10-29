#pragma once

#include "Defs.h"
#include "Resource.h"

namespace drvut {
namespace internal {

class SymbolicLink final {
public:
    SymbolicLink(PCUNICODE_STRING dosDeviceName, PCUNICODE_STRING ntDeviceName);
    SymbolicLink(PCUNICODE_STRING alreadyInitializedDosDeviceName);
    MOVEABLE(SymbolicLink);
    NOCOPY(SymbolicLink);

    NTSTATUS initialize();
    NTSTATUS destroy();

private:
    PCUNICODE_STRING m_dosDeviceName;
    PCUNICODE_STRING m_ntDeviceName;
};

using SymbolicLinkGuard = ResourceGuard<SymbolicLink>;

}
}
