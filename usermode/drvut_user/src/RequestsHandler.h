#pragma once

#include "Defs.h"
#include "Messages.h"

template<typename T>
concept RequestsHandler = requires(T& t, 
                                   const ListFixturesInput& listFixturesInput,
                                   const ListTestsInput& listTestsInput,
                                   const RunTestInput& runTestInput) {
    { t.listFixtures(listFixturesInput) } -> std::same_as<ListFixturesOutput>;
    { t.listTests(listTestsInput) } -> std::same_as<ListTestsOutput>;
    { t.runTest(runTestInput) } -> std::same_as<RunTestOutput>;
};
