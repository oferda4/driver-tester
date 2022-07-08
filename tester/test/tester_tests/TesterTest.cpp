#include "TesterTest.h"

#include <gtest/gtest.h>

#include "tester/Tester.h"

#include "MockTracer.h"

static constexpr uint32_t ARBITRARY_FIXTURES_INDEX_START = 0;
static constexpr uint32_t ARBITRARY_NUMBER_OF_FIXTURES = 10;
static constexpr uint32_t ARBITRARY_TESTS_INDEX_START = 12;
static constexpr uint32_t ARBITRARY_NUMBER_OF_TESTS = 12;

// To simplify use the same name for all fixtures and tests
static constexpr char ARBITARARY_FIXTURE_NAME[] = "FixtureTest";
static_assert(sizeof(ARBITARARY_FIXTURE_NAME) < MAX_NAME_SIZE);
static constexpr char ARBITRARY_TEST_NAME[] = "SomeTest";
static_assert(sizeof(ARBITRARY_TEST_NAME) < MAX_NAME_SIZE);

static std::vector<FixtureInfo> getTestFixturesList();
static std::vector<TestInfo> getFixturesTestsList();

TEST(TestTest, RunAllTests) {
    auto comm = std::make_unique<testing::StrictMock<MockClientCommunicator>>();
    EXPECT_CALL(*comm, getFixtures()).WillOnce(testing::Return(getTestFixturesList()));
    EXPECT_CALL(*comm, 
                getTests(testing::AllOf(
                    testing::Ge(ARBITRARY_FIXTURES_INDEX_START), testing::Lt(ARBITRARY_FIXTURES_INDEX_START + ARBITRARY_NUMBER_OF_FIXTURES))))
        .WillRepeatedly(testing::Return(getFixturesTestsList()));

    ASSERT_NO_THROW((Tester<MockClientCommunicator, MockTracer>(std::move(comm)).runAllTests()));
}

std::vector<FixtureInfo> getTestFixturesList() {
    std::vector<FixtureInfo> fixtures;
    for (uint32_t i = 0; i < ARBITRARY_NUMBER_OF_FIXTURES; i++) {
        FixtureInfo info = { i + ARBITRARY_FIXTURES_INDEX_START, { 0 } };
        memcpy(info.name, ARBITARARY_FIXTURE_NAME, sizeof(ARBITARARY_FIXTURE_NAME));
        fixtures.push_back(std::move(info));
    }
    return fixtures;
}

std::vector<TestInfo> getFixturesTestsList() {
    std::vector<TestInfo> tests;
    for (uint32_t i = 0; i < ARBITRARY_NUMBER_OF_TESTS; i++) {
        TestInfo info = { i + ARBITRARY_TESTS_INDEX_START, { 0 } };
        memcpy(info.name, ARBITRARY_TEST_NAME, sizeof(ARBITRARY_TEST_NAME));
        tests.push_back(std::move(info));
    }
    return tests;
}
