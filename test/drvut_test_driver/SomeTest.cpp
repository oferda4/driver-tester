#include "drvut.h"

#include "Test.h"

EXTERN_C void initializeTests() {
    drvut::test("Failing Test") = []() { return STATUS_INVALID_PARAMETER; };
    drvut::test("Successful Test") = []() { return STATUS_SUCCESS; };
}
