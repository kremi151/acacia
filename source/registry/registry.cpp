//
// Created by Michel on 03.06.2020.
//

#include "registry.h"

#include <iostream>
#include <exception>
#include <exceptions/assertion_exception.h>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace acacia;

Registry::Registry()
    : currentSuite("default")
{
}

Registry & Registry::instance() {
    static Registry registry;
    return registry;
}

void Registry::registerTest(const char *fileName, const char *testName, void (*testPtr)()) {
    auto &fileEntry = fileEntries[fileName];
    if (fileEntry.fileName.empty()) {
        fileEntry.fileName = fileName;
    }
    fileEntry.tests.push_back({
        testPtr,
        testName,
        fileName
    });
}

void Registry::registerBefore(bool file, const char *fileName, void (*funcPtr)()) {
    auto &fileEntry = fileEntries[fileName];
    if (fileEntry.fileName.empty()) {
        fileEntry.fileName = fileName;
    }
    if (file) {
        fileEntry.beforeFile.push_back(funcPtr);
    } else {
        fileEntry.before.push_back(funcPtr);
    }
}

void Registry::registerAfter(bool file, const char *fileName, void (*funcPtr)()) {
    auto &fileEntry = fileEntries[fileName];
    if (fileEntry.fileName.empty()) {
        fileEntry.fileName = fileName;
    }
    if (file) {
        fileEntry.afterFile.push_back(funcPtr);
    } else {
        fileEntry.after.push_back(funcPtr);
    }
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

bool Registry::runTest(const std::string &fileName, const std::string &testName, const std::string &suiteName, const std::vector<func_ptr> &steps, Report &outReport) {
    StreamCapture capStdout(std::cout);
    StreamCapture capStderr(std::cerr);
    currentStdOut = &capStdout;
    currentStdErr = &capStderr;
    bool result;
    try {
        for (const func_ptr &step : steps) {
            step();
        }
        outReport.addResult(fileName, testName, suiteName, true, "", 0, capStdout.str(), capStderr.str());
        result = true;
    } catch (const AssertionException &ex) {
        std::string assertionMessage = std::string("Assertion error: ") + ex.what();
        std::cerr << "Test " << testName << " failed:" << std::endl;
        std::cerr << "   Assertion error: " << ex.what() << std::endl;
        std::cerr << "   Error happened in " << ex.getFileName() << ":" << ex.getLine() << std::endl;
        outReport.addResult(fileName, testName, suiteName, false, std::string("Assertion error: ") + ex.what(), ex.getLine(), capStdout.str(), capStderr.str());
        result = false;
    } catch (const std::exception &ex) {
        std::cerr << "Test " << testName << " failed:" << std::endl;
        std::cerr << "   Unexpected exception: " << ex.what() << std::endl;
        std::cerr << "   Error happened in " << fileName << ", unknown line" << std::endl;
        outReport.addResult(fileName, testName, suiteName, false, std::string("Unexpected exception: ") + ex.what(), 0, capStdout.str(), capStderr.str());
        result = false;
    } catch (...) {
        std::cerr << "Test " << testName << " failed:" << std::endl;
        std::cerr << "   Unexpected exception, no further information available" << std::endl;
        std::cerr << "   Error happened in " << fileName << ", unknown line" << std::endl;
        outReport.addResult(fileName, testName, suiteName, false, "Unexpected exception, no further information available", 0, capStdout.str(), capStderr.str());
        result = false;
    }
    _currentTestName = "MISSINGNO";
    currentStdOut = nullptr;
    currentStdErr = nullptr;
    return result;
}

Report Registry::runTestsOfSuite(const std::string &suiteName) {
    std::cout << "Start executing test suite " << suiteName << std::endl;
    std::vector<FileEntry> tests;
    std::copy_if(fileEntries.begin(), fileEntries.end(), std::back_inserter(tests), [suiteName](FileEntry &t) {
        return t.suiteName == suiteName;
    });
    return runSpecificTests(tests);
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

        std::vector<func_ptr> testSteps;

        if (!fileEntry.beforeFile.empty()) {
            for (const auto &func : fileEntry.beforeFile) {
                testSteps.push_back(func);
            }
            _currentTestName = "<before file>";
            if (!runTest(fileEntry.fileName, _currentTestName, fileEntry.suiteName, testSteps, report)) {
                errorCount++;
                for (const auto &test : fileEntry.tests) {
                    report.addResult(fileEntry.fileName, test.testName, fileEntry.suiteName, false, "Previous error", 0, "", "");
                    errorCount++;
                }
                continue;
            }
        }

        testSteps.clear();
        for (const auto &func : fileEntry.before) {
            testSteps.push_back(func);
        }
        testSteps.push_back(nullptr);
        for (const auto &func : fileEntry.after) {
            testSteps.push_back(func);
        }

        for (const auto &test : fileEntry.tests) {
            testCount++;
            _currentTestName = test.testName;
            testSteps[fileEntry.before.size()] = test.funcPtr;
            if (runTest(test.fileName, test.testName, fileEntry.suiteName, testSteps, report)) {
                successCount++;
            } else {
                errorCount++;
            }
        }

        testSteps.clear();
        if (!fileEntry.afterFile.empty()) {
            for (const auto &func : fileEntry.afterFile) {
                testSteps.push_back(func);
            }
            _currentTestName = "<after file>";
            if (!runTest(fileEntry.fileName, _currentTestName, fileEntry.suiteName, testSteps, report)) {
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

const std::string &Registry::currentTestName() {
    return _currentTestName;
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

BeforeRegistration::BeforeRegistration(bool file, const char *fileName, void (*testPtr)()) noexcept {
    Registry::instance().registerBefore(file, fileName, testPtr);
}

AfterRegistration::AfterRegistration(bool file, const char *fileName, void (*testPtr)()) noexcept {
    Registry::instance().registerAfter(file, fileName, testPtr);
}

void Registry::setCurrentSuite(const std::string &suiteName) {
    this->currentSuite = suiteName;
}

std::string & Registry::getCurrentSuite() {
    return currentSuite;
}

StartSuite::StartSuite(const char *suiteName) noexcept {
    Registry::instance().setCurrentSuite(suiteName);
}
