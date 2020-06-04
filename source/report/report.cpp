//
// Created by Michel Kremer on 04.06.2020.
//

#include "report.h"

using namespace acacia;

TestResult::TestResult(std::string testName, bool success, std::string output): testName(std::move(testName)), success(success), output(std::move(output)) {
}

const std::string &TestResult::getTestName() const {
    return testName;
}

const std::string& TestResult::getOutput() const {
    return output;
}

bool TestResult::isSuccess() const {
    return success;
}

Report::Report(): testCount(0), successCount(0), errorCount(0) {
}

void Report::addResult(const std::string &fileName, std::string testName, bool success, std::string output) {
    if (results.find(fileName) == results.end()) {
        results.insert(std::pair(fileName, std::vector<TestResult>()));
    }
    std::vector<TestResult> &v = results[fileName];
    v.emplace_back(std::move(testName), success, std::move(output));
}

void Report::setCounts(size_t all, size_t success, size_t error) {
    testCount = all;
    successCount = success;
    errorCount = error;
}

size_t Report::getTestCount() {
    return testCount;
}

size_t Report::getSuccessCount() {
    return successCount;
}

size_t Report::getErrorCount() {
    return errorCount;
}

Report::operator bool() {
    return errorCount == 0;
}
