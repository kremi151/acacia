//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_REGISTRY_H
#define ACACIA_REGISTRY_H

#include <vector>
#include <set>
#include <map>
#include <string>
#include <report/report.h>
#include <io/stream_capture.h>
#include <suite/base.h>
#include <functional>

namespace acacia {

    typedef std::string file_name;
    typedef std::string suite_name;
    typedef std::string test_name;

    typedef struct {
        std::function<void()> func;
        test_name testName;
        file_name fileName;
    } TestEntry;

    typedef struct {
        std::string fileName;
        std::string suiteName;
        std::vector<std::function<void()>> beforeFile;
        std::vector<std::function<void()>> before;
        std::vector<TestEntry> tests;
        std::vector<std::function<void()>> after;
        std::vector<std::function<void()>> afterFile;
    } SuiteEntry;

    class Registry{
    private:
        Registry();

        std::map<suite_name, SuiteEntry> suiteEntries;
        std::string _currentTestName;
        StreamCapture *currentStdOut, *currentStdErr;

        Report runSpecificTests(std::vector<SuiteEntry> &suites);
        bool runTest(const std::string &fileName, const std::string &testName, const std::string &suiteName, const std::vector<std::function<void()>> &steps, Report &outReport);
    public:
        void registerTest(const char *fileName, const char *suiteName, const char *testName, const std::function<void()> &func);
        void registerBefore(bool file, const char *fileName, const char *suiteName, const std::function<void()> &func);
        void registerAfter(bool file, const char *fileName, const char *suiteName, const std::function<void()> &func);
        Report runTests();
        [[deprecated]]
        Report runTestsOfFile(const std::string &fileName);

        Report runTestsOfSuite(const std::string &suiteName);

        void collectSuiteNames(std::set<std::string> &outList);

        const std::string &currentTestName();

        std::string getCurrentStdOut();
        std::string getCurrentStdErr();

        static Registry &instance();
    };

    template <class T>
    class SuiteRegistration {
    private:
        T suite;
    public:
        SuiteRegistration() noexcept {
            fprintf(stdout, "REGISTER SUITE %s\n", suite.suiteName());
            suite.describe();
        }
    };

}

#endif //ACACIA_REGISTRY_H
