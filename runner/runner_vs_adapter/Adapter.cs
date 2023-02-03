using Microsoft.VisualStudio.TestPlatform.ObjectModel;
using Microsoft.VisualStudio.TestPlatform.ObjectModel.Adapter;
using Microsoft.VisualStudio.TestPlatform.ObjectModel.Logging;

namespace RunnerAdapter {

[ExtensionUri("executor://RunnerExecutor/v1")]
public class RunnerExecutor : ITestExecutor {
    public void Cancel() {
        throw new NotImplementedException();
    }

    public void RunTests(IEnumerable<TestCase>? tests, IRunContext? runContext, IFrameworkHandle? frameworkHandle) {
        throw new NotImplementedException();
    }

    public void RunTests(IEnumerable<string>? sources, IRunContext? runContext, IFrameworkHandle? frameworkHandle) {
        throw new NotImplementedException();
    }
}

[ExtensionUri("discovery://RunnerDiscoverer/v1")]
public class RunnerDiscoverer : ITestDiscoverer {
    public void DiscoverTests(IEnumerable<string> sources, IDiscoveryContext discoveryContext, IMessageLogger logger, ITestCaseDiscoverySink discoverySink) {
        throw new NotImplementedException();
    }
}

}