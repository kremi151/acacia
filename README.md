# acacia
![acacia CI](https://github.com/kremi151/acacia/workflows/acacia%20CI/badge.svg)

A small and lightweight C++ testing framework

## Setup

Download this repository manually or using `Git submodules` into a sub folder of your project.
Assuming you've put acacia in a sub folder called `acacia`, add the following lines to your `CMakeLists.txt` file:

```
project(your_project_name)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/acacia")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/acacia/source")

set_acacia_use_default_main()

set_acacia_test_sources(
    test_source1.cpp
    test_source2.cpp
)

include_directories(${ACACIA_TEST_INCLUDE_DIRS})

add_executable(your_project_name ${ACACIA_TEST_SOURCES} ${ACACIA_TEST_HEADERS})

target_link_libraries(your_project_name acacia)
```

## Usage

Everything you need can be imported with the following `include` directive:

```
#include <acacia.h>
```

### How to write a test

Tests need to belong to a test suite, they can be defined as follows:
```
TEST_SUITE(yourTestSuiteNameHere) {

    TEST(yourTestNameHere) {
        int answerToEverything = 42;
        assertEquals(42, answerToEverything);
    }

    TEST(anotherTest) {
        ...
    }

}
```

By writing this piece of code, you will create tests which will automatically be registered within the `acacia` runtime.
This examples uses the `assertEquals` assertion. Other available assertions will be listed below.

### How to execute tests

If you use the `set_acacia_use_default_main()` macro in your `CMakeLists.txt`, you're all set and there's nothing more to do for you.
The built binary can be executed out of the box.

If you wish to implement a custom `main` function, you need to follow these steps:

1. Do *not* use the `set_acacia_use_default_main()` macro in your `CMakeLists.txt`
2. Call `acacia::runTests` like for example as follows:
```
#include <acacia.h>

int main(int argc, char **argv) {
    return acacia::runTests(argc, argv, nullptr);
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

* assertTrue(bool) \
Asserts whether the given boolean value is `true`. \
If it is `false`, the test will fail.

* assertFalse(bool) \
Asserts whether the given boolean value is `false`. \
If it is `true`, the test will fail.

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
acacia::Report report;
int status = acacia::runTests(argc, argv, &report);
std::ofstream reportFile("test-report.txt");
acacia::generateAcaciaReport(report, reportFile);
```

#### JUnit format (XML)

```
acacia::Report report;
int status = acacia::runTests(argc, argv, &report);
std::ofstream reportFile("test-report.xml");
acacia::generateJUnitReport(report, reportFile);
```

### Current limitations

Acacia makes use of automatically generated code for wiring the different test suites together. \
For this, it currently makes use of regular expressions to search for test suites in a file.

What this means is that:
- Defining a test suite using a custom macro will break things

Please note that conditional enabling/disabling of tests and test suites with `#if`, `#ifdef`, `#ifndef`, `#else` and `#elif` macros is supported, but any referenced value in the condition needs to publicly visible.

Tests defined using the `TEST(xyz)` macro are currently evaluated at runtime, but this may be subject to change in the future (in favor of code generation ahead of time).
