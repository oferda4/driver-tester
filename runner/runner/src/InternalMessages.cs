using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Runner {
    public static class InternalMessages {
        public struct TestInfo {
            uint id;
            string name;
        };

        public struct TestResult {
            int status;
        };

        public struct ListTestsInput {
            // intentionally left blank
        };

        public struct ListTestsOutput {
            List<TestInfo> tests;
        };

        public struct RunTestInput {
            uint testId;
        };

        public struct RunTestOutput {
            TestResult result;
        };
    }
}
