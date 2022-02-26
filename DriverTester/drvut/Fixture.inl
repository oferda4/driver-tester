#pragma once

#include "Fixture.h"

namespace drvtest {
namespace ut {

template<typename FixtureType>
std::vector<Test> FixtureHandlerImpl<FixtureType>::sm_tests{};

template<typename FixtureType>
FixtureHandlerImpl<FixtureType>::FixtureHandlerImpl() : m_index(0) {}

template<typename FixtureType>
void FixtureHandlerImpl<FixtureType>::add(Test test) {
	sm_tests.add(std::move(test));
}

template<typename FixtureType>
bool FixtureHandlerImpl<FixtureType>::didFinish() {
	return m_index >= sm_tests.size();
}

template<typename FixtureType>
RunTestResult FixtureHandlerImpl<FixtureType>::runNextTest() {
	if (didFinish) {
		return { "", TestResult.END };
	}

	Test& curr = advance();
	__try {
		runTest(curr);
		return { curr.name, RunResult::SUCCESS };
	} __except (...) {
		return { curr.name, RunResult::FAILED };
	}
}

template<typename FixtureType>
Test& FixtureHandlerImpl<FixtureType>::advance() {
	return sm_tests[index++];
}

template<typename FixtureType>
void FixtureHandlerImpl<FixtureType>::runTest(Test& test) {
	FixtureTraits::setup();
	curr[m_index].run();
	FixtureTraits::teardown();
}

}
}
