#include "Defs.h"

using DWORD = uint32_t;
using PDWORD = DWORD*;
using WORD = unsigned short;
using BYTE = unsigned char;

typedef struct _RUNTIME_FUNCTION {
    DWORD BeginAddress;
    DWORD EndAddress;
    DWORD UnwindData;
} RUNTIME_FUNCTION, *PRUNTIME_FUNCTION;

typedef struct _UNWIND_HISTORY_TABLE_ENTRY {
    DWORD64 ImageBase;
    PRUNTIME_FUNCTION FunctionEntry;
} UNWIND_HISTORY_TABLE_ENTRY, *PUNWIND_HISTORY_TABLE_ENTRY;

typedef struct _UNWIND_HISTORY_TABLE {
    DWORD Count;
    BYTE LocalHint;
    BYTE GlobalHint;
    BYTE Search;
    BYTE Once;
    DWORD64 LowAddress;
    DWORD64 HighAddress;
    UNWIND_HISTORY_TABLE_ENTRY Entry[1];
} UNWIND_HISTORY_TABLE, *PUNWIND_HISTORY_TABLE;

#define UNW_FLAG_NHANDLER 0

extern "C" PRUNTIME_FUNCTION __stdcall RtlLookupFunctionEntry(DWORD64 ControlPc, PDWORD64 ImageBase,
                                                              PUNWIND_HISTORY_TABLE HistoryTable);
extern "C" PEXCEPTION_ROUTINE __stdcall RtlVirtualUnwind(
    _In_ DWORD HandlerType, 
                                                       _In_ DWORD64 ImageBase, 
                                                       _In_ DWORD64 ControlPc,
                                                       _In_ PRUNTIME_FUNCTION FunctionEntry, 
                                                       _Inout_ PCONTEXT ContextRecord,
                                                       _Out_ PVOID* HandlerData, 
                                                       _Out_ PDWORD64 EstablisherFrame,
                                                       _Inout_opt_ PVOID ContextPointers);

//#include <winnt.h>


EXCEPTION_DISPOSITION __CxxFrameHandler3([[maybe_unused]] PEXCEPTION_RECORD ExceptionRecord, [[maybe_unused]] PVOID EstablisherFrame,
                                         PCONTEXT ContextRecord, PVOID DispatcherContext) {
    UNWIND_HISTORY_TABLE HistoryTable;
    PUNWIND_HISTORY_TABLE_ENTRY pHistoryTableEntry;
    PRUNTIME_FUNCTION pRuntimeFunction;
    DWORD64 ImageBase;
    DWORD64 ControlPc;
    DWORD64 FunctionStart;
    DWORD64 TargetPc;
    PVOID HandlerData = nullptr;
    DWORD64 EstablisherFramePointer = 0;
    DWORD64 TempStackPointer = 0;
    BOOLEAN HandlerFound = FALSE;
    EXCEPTION_DISPOSITION Disposition = ExceptionContinueSearch;

    // Retrieve the ImageBase and ControlPc from the DispatcherContext
    ImageBase = (DWORD64)DispatcherContext;
    ControlPc = (DWORD64)ContextRecord->Rip;

    // Initialize the history table
    HistoryTable.Count = 0;
    HistoryTable.LocalHint = 0;
    HistoryTable.GlobalHint = 0;
    HistoryTable.Search = 0;
    HistoryTable.Once = 0;
    HistoryTable.LowAddress = 0;
    HistoryTable.HighAddress = 0;

    // Loop through each function in the call chain
    while (ControlPc) {
        // Get the runtime function for the current control PC
        pRuntimeFunction = RtlLookupFunctionEntry(ControlPc, &ImageBase, &HistoryTable);

        // Make sure a runtime function was found
        if (!pRuntimeFunction) {
            break;
        }

        // Check if the function has an exception handler
        if (*(PDWORD)HandlerData != UNW_FLAG_NHANDLER) {
            // Check if the exception handler is a C++ exception handler
            if ((*(PDWORD)HandlerData & 1) == 0) {
                // Exception handler found, unwind the stack
                RtlVirtualUnwind(0x1 /* UNW_FLAG_EHANDLER */, 
                                 ImageBase, 
                                 ControlPc, 
                                 pRuntimeFunction,
                                 ContextRecord, 
                                 &HandlerData, 
                                 &EstablisherFramePointer,
                                 &TempStackPointer);

                // Set the disposition to continue executing the exception handler
                Disposition = ExceptionContinueExecution;
                HandlerFound = TRUE;
                break;
            }
        }

        // Move to the next function in the call chain
        ControlPc = EstablisherFramePointer + 8;
    }


    // Return the disposition
    if (!HandlerFound) {
        Disposition = ExceptionContinueSearch;
    }
    return Disposition;
}
