#include "Defs.h"

typedef const struct _s_FuncInfo {
    unsigned int magicNumber : 29;
    unsigned int bbtFlags : 3;
    int maxState;

    int dispUnwindMap;
    unsigned int nTryBlocks;
    int dispTryBlockMap;
    unsigned int nIPMapEntries;
    int dispIPtoStateMap;
    int dispUwindHelp;
    int dispESTypeList;

    int EHFlags;
} FuncInfo;

typedef struct IptoStateMapEntry {
    unsigned int Ip;
    int State;
} IptoStateMapEntry;

typedef const struct _s_UnwindMapEntry {
    int toState;
    void(__cdecl* action)(void);
} UnwindMapEntry;

static int stateFromIp(FuncInfo& funcInfo, DISPATCHER_CONTEXT& dispatcherContext) {
    uint32_t index = 0;
    auto* ipToStateMap = reinterpret_cast<IptoStateMapEntry*>(dispatcherContext.ImageBase + funcInfo.dispIPtoStateMap);

    for (; index < funcInfo.nIPMapEntries; index++) {
        const IptoStateMapEntry& pIPtoStateMap = ipToStateMap[index];
        if (dispatcherContext.ControlPc < (dispatcherContext.ImageBase + pIPtoStateMap.Ip)) {
            break;
        }
    }

    if (index == 0) {
        return -1;
    }

    return ipToStateMap[index-1].State;
}

EXCEPTION_DISPOSITION __CxxFrameHandler4([[maybe_unused]] EXCEPTION_RECORD* pExcept,
                                         [[maybe_unused]] EXCEPTION_REGISTRATION_RECORD* pRegistration,
                                         [[maybe_unused]] CONTEXT* pContext, 
                                         PDISPATCHER_CONTEXT pDispContext) {
    __debugbreak();

    auto* funcInfo = reinterpret_cast<FuncInfo*>(pDispContext->ImageBase + *reinterpret_cast<PULONG>(pDispContext->HandlerData));
    if (!funcInfo) {
        // TODO: Handle
        return ExceptionContinueSearch;
    }

    auto* unwindMap = reinterpret_cast<UnwindMapEntry*>(pDispContext->ImageBase + funcInfo->dispUnwindMap);

    auto state = stateFromIp(*funcInfo, *pDispContext);
    
    while (state != -1) {
        if (state < 0 || state >= funcInfo->maxState) {
            // TODO: Handle
            return ExceptionContinueSearch;
        }

        // calling the dtor
        unwindMap[state].action();

        state = unwindMap[state].toState;
    }

    return ExceptionContinueSearch;
}
