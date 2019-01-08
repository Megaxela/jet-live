
#include <catch.hpp>
#include <iostream>
#include <thread>
#include "ClassInstanceMethod.hpp"
#include "Globals.hpp"
#include "WaitForReload.hpp"

TEST_CASE("Reload of class instance method", "[function]")
{
    int v1 = 23;
    int v2 = 45;
    int sum = v1 + v2;
    int mul = v1 * v2;
    ClassInstanceMethod ins;

    REQUIRE(ins.computeResult(v1, v2) == sum);

    std::cout << "JET_TEST: disable(3:1); enable(3:2)" << std::endl;
    waitForReload();

    REQUIRE(ins.computeResult(v1, v2) == mul);
}
