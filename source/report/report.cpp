//
// Created by Michel Kremer on 04.06.2020.
//

#include "report.h"

using namespace acacia;

TestResult::TestResult(std::string testName, std::string suiteName, bool success, std::string assertion, unsigned int errorLine, std::string output, std::string errorOutput)
    : testName(std::move(testName))
    , suiteName(std::move(suiteName))
    , success(success)
    , assertion(std::move(assertion))
    , errorLine(errorLine)
    , output(std::move(output))
    , errorOutput(std::move(errorOutput))
{
}

const std::string &TestResult::getTestName() const {
    return testName;
}

const std::string &TestResult::getSuiteName() const {
    return suiteName;
}

const std::string & TestResult::getAssertion() const {
    return assertion;
}

unsigned int TestResult::getErrorLine() const {
    return errorLine;
}

const std::string& TestResult::getOutput() const {
    return output;
}

const std::string & TestResult::getErrorOutput() const {
    return errorOutput;
}

bool TestResult::isSuccess() const {
    return success;
}

Report::Report()
    : testCount(0)
    , successCount(0)
    , errorCount(0)
{
}

Report & Report::operator+=(const Report &other) {
    results.insert(other.results.begin(), other.results.end());
    testCount += other.testCount;
    successCount += other.successCount;
    errorCount += other.errorCount;
    return *this;
}

void Report::addResult(const std::string &fileName, std::string testName, std::string suiteName, bool success, std::string assertion, unsigned int errorLine, std::string output, std::string errorOutput) {
    if (results.find(fileName) == results.end()) {
        results.insert(std::pair(fileName, std::vector<TestResult>()));
    }
    std::vector<TestResult> &v = results[fileName];
    v.emplace_back(std::move(testName), std::move(suiteName), success, std::move(assertion), errorLine, std::move(output), std::move(errorOutput));
}

void Report::setCounts(size_t all, size_t success, size_t error) {
    testCount = all;
    successCount = success;
    errorCount = error;
}

std::map<std::string, std::vector<TestResult> >::const_iterator Report::results_begin() {
    return results.begin();
}

std::map<std::string, std::vector<TestResult> >::const_iterator Report::results_begin() const {
    return results.begin();
}

std::map<std::string, std::vector<TestResult> >::const_iterator Report::results_end() {
    return results.end();
}

std::map<std::string, std::vector<TestResult> >::const_iterator Report::results_end() const {
    return results.end();
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
