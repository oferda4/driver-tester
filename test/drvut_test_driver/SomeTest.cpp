#include "drvut.h"

#include "Test.h"

struct DtorTest {
    uint32_t num;

    ~DtorTest() {
        __debugbreak();
    }
};

void testHelper() {
    __debugbreak();
    DtorTest d0{ 0 };
    DtorTest d1{ 1 };
    volatile int a = 1;
    uint32_t b = 1 / (a-1);
    b++;
}

void dtorTest() {
    __try {
        testHelper();
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        __debugbreak();
    }
}

EXTERN_C void initializeTests() {
    drvut::test("Failing Test") = []() { return STATUS_INVALID_PARAMETER; };
    drvut::test("Successful Test") = []() { return STATUS_SUCCESS; };
    
    drvut::test("Dtors called") = []() { 
        dtorTest();
        return STATUS_SUCCESS; 
    };
}
