using Runner;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Runner {
    public interface Serializer {
        byte[] serializeListTestsInput(InternalMessages.ListTestsInput input);
        byte[] serializeRunTestInput(InternalMessages.RunTestInput input);
        InternalMessages.ListTestsOutput deserializeListTestsOutput(byte[] output);
        InternalMessages.RunTestOutput deserializeRunTestOutput(byte[] output);
    }
}
