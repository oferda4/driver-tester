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
                var tests = runner.listTests();
                var res1 = runner.runTest(tests[0].id);
                var res2 = runner.runTest(tests[1].id);
            } finally {
                client.GetStream().Close();
                client.Close();
            }

            pause();
            return 0;
        }

        static void printUsages() {
            Console.WriteLine("Usages: runner.exe <ip> <port>");
        }

        static void pause() {
            Console.ReadKey();
        }
    }
}
