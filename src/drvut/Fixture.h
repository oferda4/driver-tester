#pragma once

#include <vector>
#include <string>

#include "Test.h"

namespace drvtest {
    namespace ut {

        enum class RunTestResultType {
            SUCCESS,
            FAILED,
            END
        };

        struct RunTestResult {
            std::string name;
            RunTestResultType type;
        };

        class Fixture {
        public:
            virtual ~Fixture() = default;

            virtual void setup() = 0;
            virtual void teardown() = 0;
        };

        class FixtureHandler {
        public:
            virtual ~FixtureHandler() = default;

            virtual RunTestResult runNextTest() = 0;
        };

        template <typename FixtureType>
        class FixtureHandlerImpl final : public FixtureHandler {
        public:
            FixtureHandlerImpl();

            static void add(Test test);
            RunTestResult runNextTest() override;

        private:
            bool didFinish();
            Test& advance();
            static void runTest(Test& test);

            static std::vector<Test> sm_tests;
            uint32_t m_index;
        };

    }
}

#include "Fixture.inl"
