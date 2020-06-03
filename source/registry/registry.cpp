//
// Created by Michel on 03.06.2020.
//

#include "registry.h"

#include <iostream>
#include <exception>
#include <exceptions/assertion_exception.h>

using namespace acacia;

Test __Acacia__nullTest = {nullptr, "", "" };

Registry::Registry(): currentTestFromList(nullptr) {
}

Registry & Registry::instance() {
    static Registry registry;
    return registry;
}

void Registry::registerTest(const char *fileName, const char *testName, void (*testPtr)()) {
    Test test;
    test.testPtr = testPtr;
    test.testName = testName;
    test.fileName = fileName;
    tests.push_back(test);
}

int Registry::runTests() {
    size_t testCount = 0;
    size_t successCount = 0;
    size_t errorCount = 0;
    auto end = tests.end();
    for (auto i = tests.begin() ; i != end ; i++) {
        testCount++;
        auto &test = *i;
        currentTestFromList = &test;
        try {
            test.testPtr();
            successCount++;
        } catch (const AssertionException &ex) {
            std::cerr << "Test " << test.testName << " failed:" << std::endl;
            std::cerr << "   Assertion error: " << ex.what() << std::endl;
            std::cerr << "   Error happened in " << ex.getFileName() << ":" << ex.getLine();
            errorCount++;
        } catch (const std::exception &ex) {
            std::cerr << "Test " << test.testName << " failed:" << std::endl;
            std::cerr << "   Unexpected exception: " << ex.what() << std::endl;
            std::cerr << "   Error happened in " << test.fileName << ", unknown line" << std::endl;
            errorCount++;
        } catch (...) {
            std::cerr << "Test " << test.testName << " failed:" << std::endl;
            std::cerr << "   Unexpected exception, no further information available" << std::endl;
            std::cerr << "   Error happened in " << test.fileName << ", unknown line" << std::endl;
            errorCount++;
        }
        currentTestFromList = nullptr;
    }

    if (errorCount > 0) {
        std::cout << errorCount << " out of " << testCount << " tests have failed" << std::endl;
    } else {
        std::cout << "All " << testCount << " tests have completed successfully!" << std::endl;
    }

    return errorCount;
}

const Test & Registry::currentTest() {
    if (currentTestFromList == nullptr) {
        return __Acacia__nullTest;
    } else {
        return *currentTestFromList;
    }
}

Registration::Registration(const char *fileName, const char *testName, void (*testPtr)()) noexcept {
    Registry::instance().registerTest(fileName, testName, testPtr);
}
