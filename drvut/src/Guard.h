#pragma once

#include "Defs.h"
#include "concepts.h"

template<typename T>
concept Guardable = requires(T& obj) {
    { obj.init() } -> std::same_as<NTSTATUS>;
    { obj.destroy() } -> std::same_as<NTSTATUS>;
};

template<Guardable T>
class Guard final {
public:
    Guard(T obj);
    ~Guard();

private:
    T m_obj;
};
