//
// Created by Michel on 03.06.2020.
//

#include "registry.h"

#include <iostream>
#include <exception>
#include <exceptions/assertion_exception.h>
#include <algorithm>
#include <chrono>
#include <iomanip>

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
    registeredTests.push_back(test);
}

Report Registry::runTests() {
    std::vector<Test> tests(registeredTests);
    std::cout << "Start executing tests all tests" << std::endl;
    return runSpecificTests(tests);
}

Report Registry::runTestsOfFile(const std::string &fileName) {
    std::cout << "Start executing tests of " << fileName << std::endl;
    std::vector<Test> tests;
    std::copy_if(registeredTests.begin(), registeredTests.end(), std::back_inserter(tests), [fileName](Test &t) {
        return t.fileName == fileName;
    });
    return runSpecificTests(tests);
}

Report Registry::runSpecificTests(std::vector<Test> &tests) {
    std::chrono::steady_clock::time_point chronoBegin = std::chrono::steady_clock::now();

    size_t testCount = 0;
    size_t successCount = 0;
    size_t errorCount = 0;

    Report report;

    auto end = tests.end();
    for (auto i = tests.begin() ; i != end ; i++) {
        testCount++;
        auto &test = *i;
        currentTestFromList = &test;
        StreamCapture capStdout(std::cout);
        StreamCapture capStderr(std::cerr);
        currentStdOut = &capStdout;
        currentStdErr = &capStderr;
        try {
            test.testPtr();
            report.addResult(test.fileName, test.testName, true, "", 0, capStdout.str(), capStderr.str());
            successCount++;
        } catch (const AssertionException &ex) {
            std::string assertionMessage = std::string("Assertion error: ") + ex.what();
            std::cerr << "Test " << test.testName << " failed:" << std::endl;
            std::cerr << "   Assertion error: " << ex.what() << std::endl;
            std::cerr << "   Error happened in " << ex.getFileName() << ":" << ex.getLine() << std::endl;
            report.addResult(test.fileName, test.testName, false, std::string("Assertion error: ") + ex.what(), ex.getLine(), capStdout.str(), capStderr.str());
            errorCount++;
        } catch (const std::exception &ex) {
            std::cerr << "Test " << test.testName << " failed:" << std::endl;
            std::cerr << "   Unexpected exception: " << ex.what() << std::endl;
            std::cerr << "   Error happened in " << test.fileName << ", unknown line" << std::endl;
            report.addResult(test.fileName, test.testName, false, std::string("Unexpected exception: ") + ex.what(), 0, capStdout.str(), capStderr.str());
            errorCount++;
        } catch (...) {
            std::cerr << "Test " << test.testName << " failed:" << std::endl;
            std::cerr << "   Unexpected exception, no further information available" << std::endl;
            std::cerr << "   Error happened in " << test.fileName << ", unknown line" << std::endl;
            report.addResult(test.fileName, test.testName, false, "Unexpected exception, no further information available", 0, capStdout.str(), capStderr.str());
            errorCount++;
        }
        currentTestFromList = nullptr;
        currentStdOut = nullptr;
        currentStdErr = nullptr;
    }

    std::chrono::steady_clock::time_point chronoEnd = std::chrono::steady_clock::now();

    report.setCounts(testCount, successCount, errorCount);

    if (errorCount > 0) {
        std::cout << errorCount << " out of " << testCount << " tests have failed" << std::endl;
    } else {
        std::cout << "All " << testCount << " tests have completed successfully!" << std::endl;
    }

    long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(chronoEnd - chronoBegin).count();
    std::cout << "Execution time: ";
    if (ms >= 3600000) {
        auto f = ((float) ms) / 60000.f;
        std::cout << std::setprecision(3) << f;
        std::cout << " hr(s)" << std::endl;
    } else if (ms >= 60000) {
        auto f = ((float) ms) / 60000.f;
        std::cout << std::setprecision(3) << f;
        std::cout << " min(s)" << std::endl;
    } else if (ms >= 1000) {
        auto f = ((float) ms) / 1000.f;
        std::cout << std::setprecision(3) << f;
        std::cout << " s" << std::endl;
    } else {
        std::cout << ms << " ms" << std::endl;
    }

    return report;
}

const Test & Registry::currentTest() {
    if (currentTestFromList == nullptr) {
        return __Acacia__nullTest;
    } else {
        return *currentTestFromList;
    }
}

std::string Registry::getCurrentStdOut() {
    if (currentStdOut == nullptr) {
        return "";
    } else {
        return currentStdOut->str();
    }
}

std::string Registry::getCurrentStdErr() {
    if (currentStdErr == nullptr) {
        return "";
    } else {
        return currentStdErr->str();
    }
}

Registration::Registration(const char *fileName, const char *testName, void (*testPtr)()) noexcept {
    Registry::instance().registerTest(fileName, testName, testPtr);
}
