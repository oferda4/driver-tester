using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Google.Protobuf;

namespace Runner {
    public class ProtobufParser : Parser {
        public InternalMessages.ListTestsOutput parseListTestsOutput(byte[] output) {
            var response = ListTestsResponse.Parser.ParseFrom(output);
            var testsInfo = response.Tests
                .Select(info => new InternalMessages.TestInfo(info.Id, info.Name))
                .ToList();
            return new InternalMessages.ListTestsOutput(testsInfo);
        }

        public InternalMessages.RunTestOutput parseRunTestOutput(byte[] output) {
            var response = RunTestResponse.Parser.ParseFrom(output);
            return new InternalMessages.RunTestOutput(new InternalMessages.TestResult(response.Passed, response.Msg));
        }

        public byte[] serializeListTestsInput(InternalMessages.ListTestsInput input) {
            // currently there is no input
            var listTestsRequest = new Request() { ListTests = new ListTestsRequest() };
            return listTestsRequest.ToByteArray();
        }

        public byte[] serializeRunTestInput(InternalMessages.RunTestInput input) {
            var runTestRequest = new Request() { 
                RunTest = new RunTestRequest() { TestId = input.testId } 
            };
            return runTestRequest.ToByteArray();
        }
    }
}
