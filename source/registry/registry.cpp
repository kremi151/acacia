//
// Created by Michel on 03.06.2020.
//

#include "registry.h"

#include <iostream>
#include <exception>
#include <exceptions/assertion_exception.h>
#include <chrono>
#include <iomanip>

using namespace acacia;

Entry __Acacia__nullTest = {nullptr, "", ""};

Registry::Registry()
    : currentEntryFromList(nullptr)
{
}

Registry & Registry::instance() {
    static Registry registry;
    return registry;
}

void Registry::registerTest(const char *fileName, const char *testName, void (*testPtr)()) {
    auto &fileEntry = fileEntries[fileName];
    fileEntry.tests.push_back({
        testPtr,
        testName,
        fileName
    });
}

Report Registry::runTests() {
    std::vector<FileEntry> tests;
    for (auto & fileEntry : fileEntries) {
        tests.push_back(fileEntry.second);
    }
    std::cout << "Start executing tests all tests" << std::endl;
    return runSpecificTests(tests);
}

Report Registry::runTestsOfFile(const std::string &fileName) {
    std::cout << "Start executing tests of " << fileName << std::endl;
    std::vector<FileEntry> tests;
    tests.push_back(fileEntries[fileName]);
    return runSpecificTests(tests);
}

bool Registry::runTest(const std::string &fileName, const std::string &testName, void (*funcPtr)(), Report &outReport) {
    StreamCapture capStdout(std::cout);
    StreamCapture capStderr(std::cerr);
    currentStdOut = &capStdout;
    currentStdErr = &capStderr;
    bool result;
    try {
        funcPtr();
        outReport.addResult(fileName, testName, true, "", 0, capStdout.str(), capStderr.str());
        result = true;
    } catch (const AssertionException &ex) {
        std::string assertionMessage = std::string("Assertion error: ") + ex.what();
        std::cerr << "Test " << testName << " failed:" << std::endl;
        std::cerr << "   Assertion error: " << ex.what() << std::endl;
        std::cerr << "   Error happened in " << ex.getFileName() << ":" << ex.getLine() << std::endl;
        outReport.addResult(fileName, testName, false, std::string("Assertion error: ") + ex.what(), ex.getLine(), capStdout.str(), capStderr.str());
        result = false;
    } catch (const std::exception &ex) {
        std::cerr << "Test " << testName << " failed:" << std::endl;
        std::cerr << "   Unexpected exception: " << ex.what() << std::endl;
        std::cerr << "   Error happened in " << fileName << ", unknown line" << std::endl;
        outReport.addResult(fileName, testName, false, std::string("Unexpected exception: ") + ex.what(), 0, capStdout.str(), capStderr.str());
        result = false;
    } catch (...) {
        std::cerr << "Test " << testName << " failed:" << std::endl;
        std::cerr << "   Unexpected exception, no further information available" << std::endl;
        std::cerr << "   Error happened in " << fileName << ", unknown line" << std::endl;
        outReport.addResult(fileName, testName, false, "Unexpected exception, no further information available", 0, capStdout.str(), capStderr.str());
        result = false;
    }
    currentEntryFromList = nullptr;
    currentStdOut = nullptr;
    currentStdErr = nullptr;
    return result;
}

Report Registry::runSpecificTests(std::vector<FileEntry> &files) {
    std::chrono::steady_clock::time_point chronoBegin = std::chrono::steady_clock::now();

    // TODO: Use a map test->state where state = SUCCESS|FAILURE|PENDING
    size_t testCount = 0;
    size_t successCount = 0;
    size_t errorCount = 0;

    Report report;

    auto end = files.end();
    for (auto i = files.begin() ; i != end ; i++) {
        auto &fileEntry = *i;

        for (const auto &test : fileEntry.beforeFile) {
            currentEntryFromList = &test;
            if (!runTest(test.fileName, "Before file", test.funcPtr, report)) {
                errorCount++;
                continue;
            }
        }

        for (const auto &test : fileEntry.tests) {
            bool canContinue = true;
            for (const auto &before : fileEntry.before) {
                currentEntryFromList = &test;
                if (!runTest(test.fileName, test.testName, before.funcPtr, report)) {
                    errorCount++;
                    canContinue = false;
                    break;
                }
            }
            if (!canContinue) {
                break;
            }
            testCount++;
            currentEntryFromList = &test;
            if (runTest(test.fileName, test.testName, test.funcPtr, report)) {
                successCount++;
            } else {
                errorCount++;
            }
            for (const auto &after : fileEntry.after) {
                currentEntryFromList = &test;
                if (!runTest(test.fileName, test.testName, after.funcPtr, report)) {
                    errorCount++;
                    break;
                }
            }
        }

        for (const auto &test : fileEntry.afterFile) {
            currentEntryFromList = &test;
            if (!runTest(test.fileName, "After file", test.funcPtr, report)) {
                errorCount++;
                continue;
            }
        }

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

const Entry & Registry::currentTest() {
    if (currentEntryFromList == nullptr) {
        return __Acacia__nullTest;
    } else {
        return *currentEntryFromList;
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

TestRegistration::TestRegistration(const char *fileName, const char *testName, void (*testPtr)()) noexcept {
    Registry::instance().registerTest(fileName, testName, testPtr);
}

BeforeRegistration::BeforeRegistration(const char *fileName, void (*testPtr)()) noexcept {

}
