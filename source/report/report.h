//
// Created by Michel Kremer on 04.06.2020.
//

#ifndef ACACIA_REPORT_H
#define ACACIA_REPORT_H

#include <string>
#include <vector>
#include <map>

namespace acacia {

    class Registry;

    class TestResult {
    private:
        const std::string testName;
        const bool success;
        const std::string assertion;
        const unsigned int errorLine;
        const std::string output;
        const std::string errorOutput;
    public:
        TestResult(std::string testName, bool success, std::string assertion, unsigned int errorLine, std::string output, std::string errorOutput);

        const std::string &getTestName() const;
        const std::string &getAssertion() const;
        unsigned int getErrorLine() const;
        const std::string &getOutput() const;
        const std::string &getErrorOutput() const;
        bool isSuccess() const;
    };

    class Report {
    private:
        std::map<std::string, std::vector<TestResult>> results;
        size_t testCount;
        size_t successCount;
        size_t errorCount;

        void setCounts(size_t all, size_t success, size_t error);

        friend class Registry;
    public:
        Report();

        size_t getTestCount();
        size_t getSuccessCount();
        size_t getErrorCount();

        std::map<std::string, std::vector<TestResult>>::const_iterator results_begin();
        std::map<std::string, std::vector<TestResult>>::const_iterator results_end();

        explicit operator bool();

        void addResult(const std::string &fileName, std::string testName, bool success, std::string assertion, unsigned int errorLine, std::string output, std::string errorOutput);
    };

}

#endif //ACACIA_REPORT_H
