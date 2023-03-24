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

### Project ###
* Add an include to your testing driver project configuration:
```
<Import Project="$(DRVUT_PATH)\props\drvut.props" />
```


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

### Fixtures ###
Fixtures are a core concept in the drvut framework, because everything that needs to do RAII must be a fixture (See note in the "Assertion" section).

A fixture is simply a class that implements the *Fixture* concept, aka implementing the functions:
```
NTSTATUS setup();
void teardown();
```
As you can see a *setup* may fail by returning an error *NTSTATUS*.
Then you simply pass a reference to the fixture in the test function args:
```
drvut::test("Test With Fixtures") = [](Fixture1& fxt1, Fixture2& fxt2) {
    // some testings that can use the fixtures...
};
```

### Putting it all together
Let's make an example that puts everything together:
```
/// a fixture to create and delete a file in test scope.
struct TempFile {
    NTSTATUS setup() {
        // creating the file
    }

    void teardown() {
        // deleting the file
    }
}

EXTERN_C void initializeTests() {
    drvut::test("Passing Test") = []() {
        drvut::assert(drvut::AreEqual(I(1+1), I(2)));
    };

    drvut::test("Passing Test") = []() {
        drvut::assert(drvut::AreNotEqual(I(2*1), I(2)));
    };

    drvut::test("Something On a File") = [](TempFile& file) {
        // some testing on the file
    };
}
```