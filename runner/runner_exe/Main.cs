using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using System.Management.Automation;
using System.Management.Automation.Runspaces;

namespace Runner {
    internal class RunnerMain {
        private const int SERVER_PORT = 33333;
        private const string VM_NAME_ENVIRONMENT_VARIABLE_NAME = "TEST_MACHINE_NAME";

        static int Main(string[] args) {
            var ip = getVirtualMachineIP();
            TcpClient client = new TcpClient(getVirtualMachineIP(), 
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

        static string getVirtualMachineIP() {
            string vmName = Environment.GetEnvironmentVariable(VM_NAME_ENVIRONMENT_VARIABLE_NAME);
            string script = string.Format("Get-VMNetworkAdapter -VMName {0} | Select-Object -ExpandProperty IPAddresses", vmName);
            return runPowerShellScript(script);
        }

        static string runPowerShellScript(string script) {
            Runspace runspace = RunspaceFactory.CreateRunspace();
            runspace.Open();

            Pipeline pipeline = runspace.CreatePipeline();
            pipeline.Commands.AddScript(script);

            Collection<PSObject> results = pipeline.Invoke();
            runspace.Close();

            if (results == null || results.Count == 0) {
                throw new Exception("no ip found");
            }

            // TODO: find the proper ip that is connected to the host if multiple ips found.
            return results[0].ToString();
        }
    }
}
