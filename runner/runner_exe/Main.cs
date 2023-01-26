using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Runner {
    internal class RunnerMain {
        static int Main(string[] args) {
            // if (args.Length != 3) {
            //     printUsages();
            //    return 1;
            // }

            Console.WriteLine("Connecting to server");
            // TcpClient client = new TcpClient(args[1], int.Parse(args[2]));
            TcpClient client = new TcpClient("169.254.97.64", 33333);

            try {
                var parser = new ProtobufParser();
                var runner = new RunnerImpl(new ProtobufParser(), 
                                        new MessagesConnectionImpl(client.GetStream()));
                var tests = runner.listTests();
                var res1 = runner.runTest(tests[0].id);
                var res2 = runner.runTest(tests[1].id);
                pause();
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
