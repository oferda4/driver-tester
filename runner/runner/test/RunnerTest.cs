using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using Runner;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Runner.Tests {
    [TestClass()]
    public class RunnerTest {
        [TestMethod()]
        public void ListTestsTest() {
            var parser = new Mock<Parser>();
            var connection = new Mock<MessagesConnection>();

            byte[] fakeSerializedListTestsInput = { 1, 2, 3, 4 };
            byte[] fakeSerializedListTestsOutput = { 11, 22, 33, 44};
            var fakeTests = new List<InternalMessages.TestInfo>();

            parser.Setup(p => p.serializeListTestsInput(new InternalMessages.ListTestsInput()))
                .Returns(fakeSerializedListTestsInput);
            parser.Setup(p => p.parseListTestsOutput(fakeSerializedListTestsOutput))
                .Returns(new InternalMessages.ListTestsOutput(fakeTests));
            connection.Setup(c => c.send(fakeSerializedListTestsInput));
            connection.Setup(c => c.recv())
                .Returns(fakeSerializedListTestsOutput);

            var runner = new RunnerImpl(parser.Object, connection.Object);
            var result = runner.listTests();
            Assert.AreEqual(fakeTests, result);
        }

        [TestMethod()]
        public void RunTestTest() {
            var parser = new Mock<Parser>();
            var connection = new Mock<MessagesConnection>();

            const uint fakeTestId = 11;
            byte[] fakeSerializedRunTestInput = { 9, 8, 7, 6 };
            byte[] fakeSerializedRunTestOutput = { 100, 200, 100, 200 };
            var fakeTestResult = new InternalMessages.TestResult(false, "An Error");
            
            parser.Setup(p => p.serializeRunTestInput(It.IsAny<InternalMessages.RunTestInput>()))
                .Returns((InternalMessages.RunTestInput input) => {
                    Assert.AreEqual(fakeTestId, input.testId);
                    return fakeSerializedRunTestInput;
                });
            parser.Setup(p => p.parseRunTestOutput(fakeSerializedRunTestOutput))
                .Returns(new InternalMessages.RunTestOutput(fakeTestResult));
            connection.Setup(c => c.send(fakeSerializedRunTestInput));
            connection.Setup(c => c.recv())
                .Returns(fakeSerializedRunTestOutput);

            var runner = new RunnerImpl(parser.Object, connection.Object);
            var result = runner.runTest(fakeTestId);
            Assert.AreEqual(fakeTestResult.passed, result.passed);
            Assert.AreEqual(fakeTestResult.msg, result.msg);
        }
    }
}