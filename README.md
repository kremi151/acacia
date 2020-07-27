# acacia
![acacia CI](https://github.com/kremi151/acacia/workflows/acacia%20CI/badge.svg)

A small and lightweight C++ testing framework

## Setup

Download this repository manually or using `Git submodules` into a sub folder of your project.
Assuming you put acacia in a sub folder called `acacia`, add the following lines to your `CMakeLists.txt` file:

```
project(your_project_name)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/acacia")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/acacia/source")

target_link_libraries(your_project_name acacia)
```

## Usage

Everything you need can be imported with the following `include` directive:

```
#include <acacia.h>
```

### How to write a test

Tests can be defined as follows:
```
TEST(yourTestNameHere) {
    int answerToEverything = 42;
    assertEquals(42, answerToEverything);
}
```

By writing this piece of code, you will create test which will automatically be registered within the `acacia` runtime.
This examples uses the `assertEquals` assertion. Other available assertions will be listed below.

### How to launch tests

While tests are registered dynamically, they have to be launched manually (preferably in your `main` function):
```
int main() {
    auto report = runAcaciaTests();
    if (report) {
        return 0; // In case of no failing tests, return successful exit code
    } else {
        return 1; // In case of some failing tests, return unsuccessful exit code
    }
}
```

### Available assertions

#### Equality

* assertEquals(expected, actual) \
Compares `expected` with `actual`. \
If both do not match, the test will fail.

* assertNotEquals(expected, actual) \
Compares `expected` with `actual`. \
If both do match, the test will fail.

* assertBiggerThan(biggest, smallest) \
Compares `biggest` with `smallest`. \
If `smallest` is bigger than or equal to `biggest`, the test will fail.

* assertSmallerThan(smallest, biggest) \
Compares `smallest` with `biggest`. \
If `biggest` is smaller than or equal to `smallest`, the test will fail.

* assertBiggerOrEqualTo(biggest, smallest) \
Compares `biggest` with `smallest`. \
If `smallest` is bigger than `biggest`, the test will fail.

* assertSmallerOrEqualTo(smallest, biggest) \
Compares `smallest` with `biggest`. \
If `biggest` is smaller than `smallest`, the test will fail.

* assertStandardOutputHas(text) \
Looks up the current standard output for the current test. \
If it does not contain the given `text` so far, the test will fail.

* assertStandardOutputHasNot(text) \
Looks up the current standard output for the current test. \
If it does contain the given `text`, the test will fail.

* assertErrorOutputHas(text) \
Looks up the current error output for the current test. \
If it does not contain the given `text` so far, the test will fail.

* assertErrorOutputHasNot(text) \
Looks up the current error output for the current test. \
If it does contain the given `text`, the test will fail.

* testFailure(message) \
Lets the current test fail immediately with a given `message`.

### Generate test report

Acacia provides the following APIs for generating test reports in specific formats:

#### Acacia format (JSON)

```
auto report = runAcaciaTests();
std::ofstream reportFile(std::filesystem::path("test-report.txt"));
acacia::generateAcaciaReport(result, reportFile);
```

#### JUnit format (XML)

```
auto report = runAcaciaTests();
std::ofstream reportFile(std::filesystem::path("test-report.xml"));
acacia::generateJUnitReport(result, reportFile);
```