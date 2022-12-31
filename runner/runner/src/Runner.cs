using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Runner {
    public interface Runner {
        List<InternalMessages.TestInfo> listTests();
        InternalMessages.TestResult runTest(uint testId);
    }

    public class RunnerImpl : Runner {
        private Parser parser;
        private MessagesConnection connection;

        public RunnerImpl(Parser parser, MessagesConnection connection) { 
            this.parser = parser;
            this.connection = connection;
        }

        public List<InternalMessages.TestInfo> listTests() {
            connection.send(
                parser.serializeListTestsInput(new InternalMessages.ListTestsInput())
            );
            var result = parser.parseListTestsOutput(
                connection.recv()
            );
            return result.tests;
        }

        public InternalMessages.TestResult runTest(uint testId) {
            connection.send(
                parser.serializeRunTestInput(new InternalMessages.RunTestInput(testId))
            );
            var result = parser.parseRunTestOutput(
                connection.recv()
            );
            return result.result;
        }
    }
}
