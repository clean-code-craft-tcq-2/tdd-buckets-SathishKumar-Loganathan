#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "DetectCurrentFluctuation.h"

TEST_CASE("Checks No Of Range in given array") {
  int arr[] = {0, 10, 50, 100, 200, 2123, 2743, 3521, 4095, 4095, 4094, 4000, 0, 1010};
  REQUIRE(Capture_and_Print_Current_values(arr,sizeof(arr)/sizeof(arr[0])) == 4);
}
