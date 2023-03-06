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

EXTERN_C void initializeTests() {
    drvut::test("Failing Test") = []() {};
    drvut::test("Successful Test") = []() {};
}
