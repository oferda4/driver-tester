using Runner;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Runner {
    public interface Parser {
        byte[] serializeListTestsInput(InternalMessages.ListTestsInput input);
        byte[] serializeRunTestInput(InternalMessages.RunTestInput input);
        InternalMessages.ListTestsOutput parseListTestsOutput(byte[] output);
        InternalMessages.RunTestOutput parseRunTestOutput(byte[] output);
    }
}
