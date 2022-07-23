#include "Tracer.h"

#include <iostream>

void StdOutTracer::exception(const Exception& exc) {
    std::wcout << "[Exception] msg - " << exc.viewMsg() << " ; num - " << exc.getNum() << std::endl;
}

void StdOutTracer::info(const std::wstring& msg) {
    std::wcout << "[Info] " << msg << std::endl;
}
