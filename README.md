# acacia
![acacia CI](https://github.com/kremi151/acacia/workflows/acacia%20CI/badge.svg)

A small and lightweight C++ testing framework

## Setup

Download this repository manually or using `Git submodules` into a sub folder of your project.
Assuming you've put acacia in a sub folder called `acacia`, add the following lines to your `CMakeLists.txt` file:

```cmake
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

```c++
#include <acacia.h>
```

### How to write a test

Tests need to belong to a test suite, they can be defined as follows:
```c++
TEST_SUITE(yourTestSuiteNameHere) {

    name("Optional custom suite name comes here");

    auto sharedValue = createState<std::string>("This value is shared between tests");

    before([sharedValue] {
        sharedValue->set("This shared value is updated before each test");
    });

    it("test assumption comes here", [] {
        int answerToEverything = 42;
        assertEquals(42, answerToEverything);
    });

    it("another test assumption comes here", [sharedValue] {
        assertEquals("This shared value is updated before each test", sharedValue->get());
    });

}
```

By writing this piece of code, you will create tests which will automatically be registered within the `acacia` runtime.
This examples uses the `assertEquals` assertion. Other available assertions will be listed below.

Test suites can maintain values that are shared between test cases by using `createState` in the `TEST_SUITE` block.\
This will effectively create a `shared_ptr` for a holder object that wraps the passed value. This holder object provides
a getter and a setter.\
*IMPORTANT*: Pass those shared values as a value to the lambda expressions! If you pass them by reference, the runtime
behavior of the test code may be undefined.

The following hooks exist for preparation of teardown of a test suite:

* `before`\
Executed before each single test case
* `beforeAll`\
Executed once before any test case or `before` hook (acts like an initializer of the test suite)
* `after`\
Executed after each single test case
* `afterAll`\
Executed once after every test case and `after` hook (acts like a destructor of the test suite)

### How to execute tests

If you use the `set_acacia_use_default_main()` macro in your `CMakeLists.txt`, you're all set and there's nothing more to do for you.
The built binary can be executed out of the box.

If you wish to implement a custom `main` function, you need to follow these steps:

1. Do *not* use the `set_acacia_use_default_main()` macro in your `CMakeLists.txt`
2. Call `acacia::runTests` like for example as follows:
```c++
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

```c++
acacia::Report report;
int status = acacia::runTests(argc, argv, &report);
std::ofstream reportFile("test-report.txt");
acacia::generateAcaciaReport(report, reportFile);
```

#### JUnit format (XML)

```c++
acacia::Report report;
int status = acacia::runTests(argc, argv, &report);
std::ofstream reportFile("test-report.xml");
acacia::generateJUnitReport(report, reportFile);
```

### Migration from acacia v1.X

Acacia v1 made partial use of generated code to register test suites by statically analyzing test code.\
Acacia v2 makes use of static registration at runtime. Also, it makes use of functional syntax to define tests.

Here is how a test suite with a basic tests looks like in v1:

```c++
TEST_SUITE(simpleTestSuite) {

    TEST(answerToEverythingShouldBe42) {
        int answerToEverything = 42;
        assertEquals(42, answerToEverything);
    }

}
```

In v2, it will look as follows:

```c++
TEST_SUITE(simpleTestSuite) {

    it("answerToEverythingShouldBe42", [] {
        int answerToEverything = 42;
        assertEquals(42, answerToEverything);
    });

}
```

The syntax for defining a test suite remains unchanged (`TEST_SUITE`).\
Test cases now no longer use the `TEST` keyword, but instead they use `it` in combination with an assumption string and
a lambda function.\
Assertions remain unchanged.
