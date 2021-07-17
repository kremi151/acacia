//
// Created by Michel on 03.06.2020.
//

#include "registry.h"

#include <iostream>
#include <exception>
#include <exceptions/assertion_exception.h>
#include <chrono>
#include <iomanip>
#include <utility>

using namespace acacia;

Registry::Registry() = default;

Registry & Registry::instance() {
    static Registry registry;
    return registry;
}

void Registry::registerTest(const char *fileName, const char *suiteName, const char *testName, const std::function<void()> &func) {
    auto &suiteEntry = suiteEntries[suiteName];
    if (suiteEntry.fileName.empty()) {
        suiteEntry.fileName = fileName;
    }
    if (suiteEntry.suiteName.empty()) {
        suiteEntry.suiteName = suiteName;
    }
    suiteEntry.tests.push_back({
        func,
        testName,
        fileName
    });
}

void Registry::registerBefore(bool file, const char *fileName, const char *suiteName, const std::function<void()> &func) {
    auto &suiteEntry = suiteEntries[suiteName];
    if (suiteEntry.fileName.empty()) {
        suiteEntry.fileName = fileName;
    }
    if (suiteEntry.suiteName.empty()) {
        suiteEntry.suiteName = suiteName;
    }
    if (file) {
        suiteEntry.beforeFile.push_back(func);
    } else {
        suiteEntry.before.push_back(func);
    }
}

void Registry::registerAfter(bool file, const char *fileName, const char *suiteName, const std::function<void()> &func) {
    auto &suiteEntry = suiteEntries[suiteName];
    if (suiteEntry.fileName.empty()) {
        suiteEntry.fileName = fileName;
    }
    if (suiteEntry.suiteName.empty()) {
        suiteEntry.suiteName = suiteName;
    }
    if (file) {
        suiteEntry.afterFile.push_back(func);
    } else {
        suiteEntry.after.push_back(func);
    }
}

Report Registry::runTests() {
    std::vector<SuiteEntry> tests;
    for (auto & suiteEntry : suiteEntries) {
        tests.push_back(suiteEntry.second);
    }
    std::cout << "Start executing tests all tests" << std::endl;
    return runSpecificTests(tests);
}

Report Registry::runTestsOfFile(const std::string &fileName) {
    std::cout << "Start executing tests of " << fileName << std::endl;
    std::vector<SuiteEntry> tests;
    for (const auto &pair : suiteEntries) {
        if (pair.second.fileName == fileName) {
            tests.push_back(pair.second);
        }
    }
    return runSpecificTests(tests);
}

bool Registry::runTest(
        const std::string &fileName, const std::string &testName, const std::string &suiteName,
        const std::vector<std::function<void()>> &steps, Report &outReport
) {
    StreamCapture capStdout(std::cout);
    StreamCapture capStderr(std::cerr);
    currentStdOut = &capStdout;
    currentStdErr = &capStderr;
    bool result;
    try {
        for (const std::function<void()> &step : steps) {
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
    std::vector<SuiteEntry> tests;
    if (suiteEntries.find(suiteName) != suiteEntries.end()) {
        tests.emplace_back(suiteEntries[suiteName]);
    }
    return runSpecificTests(tests);
}

Report Registry::runSpecificTests(std::vector<SuiteEntry> &suites) {
    std::chrono::steady_clock::time_point chronoBegin = std::chrono::steady_clock::now();

    // TODO: Use a map test->state where state = SUCCESS|FAILURE|PENDING
    size_t testCount = 0;
    size_t successCount = 0;
    size_t errorCount = 0;

    Report report;

    auto end = suites.end();
    for (auto i = suites.begin() ; i != end ; i++) {
        auto &suiteEntry = *i;

        std::vector<std::function<void()>> testSteps;

        if (!suiteEntry.beforeFile.empty()) {
            for (const auto &func : suiteEntry.beforeFile) {
                testSteps.push_back(func);
            }
            _currentTestName = "<before file>";
            if (!runTest(suiteEntry.fileName, _currentTestName, suiteEntry.suiteName, testSteps, report)) {
                errorCount++;
                for (const auto &test : suiteEntry.tests) {
                    report.addResult(suiteEntry.fileName, test.testName, suiteEntry.suiteName, false, "Previous error", 0, "", "");
                    errorCount++;
                }
                continue;
            }
        }

        testSteps.clear();
        for (const auto &func : suiteEntry.before) {
            testSteps.push_back(func);
        }
        testSteps.push_back(nullptr);
        for (const auto &func : suiteEntry.after) {
            testSteps.push_back(func);
        }

        for (const auto &test : suiteEntry.tests) {
            testCount++;
            _currentTestName = test.testName;
            testSteps[suiteEntry.before.size()] = test.func;
            if (runTest(test.fileName, test.testName, suiteEntry.suiteName, testSteps, report)) {
                successCount++;
            } else {
                errorCount++;
            }
        }

        testSteps.clear();
        if (!suiteEntry.afterFile.empty()) {
            for (const auto &func : suiteEntry.afterFile) {
                testSteps.push_back(func);
            }
            _currentTestName = "<after file>";
            if (!runTest(suiteEntry.fileName, _currentTestName, suiteEntry.suiteName, testSteps, report)) {
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

void Registry::collectSuiteNames(std::set<std::string> &outList) {
    for (const auto &pair : suiteEntries) {
        outList.insert(pair.second.suiteName);
    }
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

void acacia::registerSuiteState(const TestSuiteState &state) {
    for (const auto &test : state.tests) {
        Registry::instance().registerTest(state.fileName.c_str(), state.suiteName.c_str(), test.description.c_str(), test.func);
    }
    for (const auto &func : state.beforeAll) {
        Registry::instance().registerBefore(true, state.fileName.c_str(), state.suiteName.c_str(), func);
    }
    for (const auto &func : state.before) {
        Registry::instance().registerBefore(false, state.fileName.c_str(), state.suiteName.c_str(), func);
    }
    for (const auto &func : state.after) {
        Registry::instance().registerAfter(false, state.fileName.c_str(), state.suiteName.c_str(), func);
    }
    for (const auto &func : state.afterAll) {
        Registry::instance().registerAfter(true, state.fileName.c_str(), state.suiteName.c_str(), func);
    }
}