#include <drvut/drvut.h>

using drvut::test;
using drvut::assert;
using drvut::B;
using drvut::I;
using drvut::AreEqual;

struct LeakCountFixture final {
    NTSTATUS setup() {
        leakCount++;
        return STATUS_SUCCESS;
    }

    void teardown() {
        leakCount--;
    }

    static int leakCount;
};
int LeakCountFixture::leakCount = 0;

EXTERN_C void initializeTests() {
    test("Failing Test") = []() { assert(B(false)); };
    test("Successful Test") = []() { assert(B(true)); };

    test("Failing Test With Fixture") = [](LeakCountFixture& leakCount) {
        UNREFERENCED_PARAMETER(leakCount);
        assert(AreEqual(I(1), I(2))); 
    };
    test("Did Not Leak Fixture") = []() { 
         assert(AreEqual(I(LeakCountFixture::leakCount), I(0))); 
    };
}
