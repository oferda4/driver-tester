# Driver Tester #
## Overview ##
These days it's hard to find a way to unit test kernel drivers. The goal of this project is to improve the developing process and maintenance of kernel drivers by providing a framework with modern syntax. The test driver you'll create will actually run in kernel, which can significally help testing all of those complex kernel API, offsets and weird compilation edge cases.

We are currently supporting only *C++ Windows Kernel Drivers*, but the framework is written in a way that extending it to more operating systems and languages in the futer.

**Note:** This is not a complete version yet and doesn't include all of the basic features. Feel free to vote for new features and contribute to this project and help it evolve. Contact me at - *oferda4@gmail.com*. 


## Requirements ##
* Visual Studio 17.4.1 or newer.
* WDK 10.0.22621.382 or newer.
* Hyper-V (for automatic deployment scripts).


## Setup ##
### Host ###
* Clone this repository - `git clone git@github.com:oferda4/driver-tester.git`
* Setup the following environment variables:
    * `DRVUT_PATH` - path the cloned repository.
    * `TEST_MACHINE_NAME` - The name of the Hyper-V virtual machine.

### Guest ###
* Allow running the test driver - You may do it by connecting a debugger, signing the driver or any other way you would run your "in developed" driver.
* Enable guest services - `VM Settings -> Integration Services -> Guest Services`.


## drvut 101 ##
### Tests Initialization ###
You must implement in your project the following function and create all tests in there (or in functions called from there):
```
EXTERN_C void initializeTests() {
    // all tests creations...
}
```

### Test Creation ###
You can create a test with the following syntax:
```
drvut::test("Test Name") = []() { 
    // do some testing...
};
```

### Assertion ###
Inside your test you may assert a boolean expression:
```
drvut::assert(/* some boolean expression */)
```
The assertion will raise a SEH exception that will be handled in the testing framework. 

**Note:** Because there is no stack unwinding in Windows kernel drivers, you must do initialization of RAII objects as fixtures (see relevant section bellow).

### Printables ###
To have a better output from the test, it's recommended to use the printables wrappers:
* `I` - Integral value.
* `B` - Boolean value.
* `AreEqual` - Compare two values.
* `AreNotEqua` - Checks that two values aren't equal.

You may add more printables by implementing the `drvut::Printable` concept.
