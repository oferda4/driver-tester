using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Runner {
    public static class InternalMessages {
        public struct TestInfo {
            public TestInfo(uint id, string name) {
                this.id = id;
                this.name = name;
            }

            public uint id;
            public string name;
        };

        public struct TestResult {
            public TestResult(long status) {
                this.status = status;
            }

            public long status;
        };

        public struct ListTestsInput {
            // intentionally left blank
        };

        public struct ListTestsOutput {
            public ListTestsOutput(List<TestInfo> tests) {
                this.tests = tests;
            }

            public List<TestInfo> tests;
        };

        public struct RunTestInput {
            public RunTestInput(uint testId) {
                this.testId = testId;
            }

            public uint testId;
        };

        public struct RunTestOutput {
            public RunTestOutput(TestResult result) {
                this.result = result;
            }

            public TestResult result;
        };
    }
}
