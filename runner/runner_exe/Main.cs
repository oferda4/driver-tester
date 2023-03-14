using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Runner {
    internal class RunnerMain {
        private const int SERVER_PORT = 33333;
        private const string SERVER_IP_ENVIRONMENT_VARABLE_NAME = "TEST_MACHINE_IP";

        static int Main(string[] args) {
            TcpClient client = new TcpClient(Environment.GetEnvironmentVariable(SERVER_IP_ENVIRONMENT_VARABLE_NAME), 
                                             SERVER_PORT);

            try {
                var parser = new ProtobufParser();
                var runner = new RunnerImpl(new ProtobufParser(), 
                                        new MessagesConnectionImpl(client.GetStream()));
                runAll(runner);
            } finally {
                client.GetStream().Close();
                client.Close();
            }

            pause();
            return 0;
        }

        static void runAll(Runner runner) {
            var tests = runner.listTests();
            foreach (var test in tests) {
                var res = runner.runTest(test.id);
                if (res.passed) {
                    Console.WriteLine("[PASSED] {0}", test.name);
                } else {
                    Console.WriteLine("[FAILED] {0}\n" +
                                        "\t{1}", test.name, res.msg);
                }
            }
        }

        static void printUsages() {
            Console.WriteLine("Usages: runner.exe <ip> <port>");
        }

        static void pause() {
            Console.ReadKey();
        }
    }
}
