#pragma once

#include "Exceptions.h"

template <typename T>
concept InfoTracer = requires(T, const std::wstring& msg) {
    { T::info(msg) } -> std::same_as<void>;
};

template <typename T>
concept ExceptionTracer = requires(T, const Exception& exc) {
    { T::exception(exc) } -> std::same_as<void>;
};

template <typename T>
concept Tracer = InfoTracer<T> && ExceptionTracer<T>;

struct StdOutTracer {
    static void exception(const Exception& exc);
    static void info(const std::wstring& msg);
};
