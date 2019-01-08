
#include <catch.hpp>
#include <iostream>
#include <thread>
#include "LambdaFunctionWithCapturesBadCase.hpp"
#include "Globals.hpp"
#include "WaitForReload.hpp"

TEST_CASE("Reload of lambda function with captured data and another lambda in the file", "[function]")
{
    int v1 = 23;
    int v2 = 45;
    int sum = v1 + v2;
    int mul = v1 * v2;
    auto lambda = createLambdaFunctionWithCapturesBadCase();

    REQUIRE(lambda(v1, v2) == sum);

    std::cout << "JET_TEST: disable(8:1); enable(8:2)" << std::endl;
    waitForReload();

    REQUIRE_FALSE(lambda(v1, v2) == mul); // note REQUIRE_FALSE
}
