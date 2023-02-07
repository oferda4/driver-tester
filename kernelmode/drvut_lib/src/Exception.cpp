#include "Defs.h"

EXCEPTION_DISPOSITION __CxxFrameHandler4(PVOID pExcept,
                                         PVOID pRegistration, 
                                         PVOID pContext, 
                                         PVOID pDispContext) {
    UNREFERENCED_PARAMETER(pExcept);
    UNREFERENCED_PARAMETER(pRegistration);
    UNREFERENCED_PARAMETER(pContext);
    UNREFERENCED_PARAMETER(pDispContext);
    return ExceptionContinueSearch;
}
