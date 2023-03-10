using Microsoft.VisualStudio.TestTools.UnitTesting;
using Runner;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Google.Protobuf;

namespace Runner.Tests {
    [TestClass()]
    public class ProtobufParserTest {
        [TestMethod()]
        public void parseListTestsOutputTest() {
            var fakeTests = new List<InternalMessages.TestInfo> {
                new InternalMessages.TestInfo(0, "Frst Test"),
                new InternalMessages.TestInfo(4, "Some Test"),
                new InternalMessages.TestInfo(5, "ASDASD"),
                new InternalMessages.TestInfo(12, "!!!@@@####")
            };

            var fakeResponse = new ListTestsResponse();
            foreach (var test in fakeTests) {
                fakeResponse.Tests.Add(new ListTestsResponse.Types.TestInfo() { Id = test.id, Name = test.name });
            }

            var result = (new ProtobufParser()).parseListTestsOutput(fakeResponse.ToByteArray());
            Assert.AreEqual(result.tests.Count, fakeTests.Count);
            for (int i = 0; i < result.tests.Count; i++) {
                Assert.AreEqual(result.tests[i].id, fakeTests[i].id);
                Assert.AreEqual(result.tests[i].name, fakeTests[i].name);
            }
        }

        [TestMethod()]
        public void parseRunTestOutputTest() {
            String fakeErrorMessage = "some error";
            var fakeTestResult = new InternalMessages.TestResult(false, fakeErrorMessage);
            var fakeResponse = new RunTestResponse() { Passed = false, Msg = fakeErrorMessage };

            var result = (new ProtobufParser()).parseRunTestOutput(fakeResponse.ToByteArray());
            Assert.AreEqual(result.result.passed, fakeTestResult.passed);
            Assert.AreEqual(result.result.msg, fakeTestResult.msg);
        }

        [TestMethod()]
        public void serializeListTestsInputTest() {
            var fakeInput = new InternalMessages.ListTestsInput();
            var serializedFakeInput = (new ProtobufParser()).serializeListTestsInput(fakeInput);

            // Nothing to check on the result as this is currently empty
            var parsedRequest = Request.Parser.ParseFrom(serializedFakeInput);
            Assert.IsTrue(parsedRequest.ListTests.IsInitialized());
        }

        [TestMethod()]
        public void serializeRunTestInputTest() {
            var fakeInput = new InternalMessages.RunTestInput(105);
            var serializedFakeInput = (new ProtobufParser()).serializeRunTestInput(fakeInput);

            var parsedRequest = Request.Parser.ParseFrom(serializedFakeInput);
            Assert.IsTrue(parsedRequest.RunTest.IsInitialized());
            Assert.AreEqual(fakeInput.testId, parsedRequest.RunTest.TestId);
        }
    }
}