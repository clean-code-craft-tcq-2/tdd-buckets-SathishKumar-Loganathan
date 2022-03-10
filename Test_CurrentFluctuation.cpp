#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "DetectCurrentFluctuation.h"

TEST_CASE("Checks No Of Range in given array") {
  int arr[] = {3, 3, 5, 4, 10, 11, 12};
  REQUIRE(Capture_and_Print_Current_values(arr,sizeof(arr)/sizeof(arr[0])) == 2);
}
