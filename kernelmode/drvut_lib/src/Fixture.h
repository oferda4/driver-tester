#pragma once

#include "Defs.h"
#include "Concepts.h"

namespace drvut {

template <typename T>
concept Fixture = requires(T& fixture) {
    { fixture.setup() } -> internal::std::same_as<NTSTATUS>;
    { fixture.teardown() } -> internal::std::same_as<void>;
    { T() };
};

}
