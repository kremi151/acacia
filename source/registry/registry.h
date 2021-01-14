//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_REGISTRY_H
#define ACACIA_REGISTRY_H

#include <vector>
#include <string>
#include <report/report.h>
#include <io/stream_capture.h>

namespace acacia {

    typedef struct {
        void (*testPtr)();
        std::string testName;
        std::string fileName;
        std::string suiteName;
    } Test;

    class Registry{
    private:
        Registry();

        std::vector<Test> registeredTests;
        Test *currentTestFromList;
        StreamCapture *currentStdOut, *currentStdErr;

        std::string currentSuite;

        Report runSpecificTests(std::vector<Test> &tests);
    public:
        void registerTest(const char *fileName, const char *testName, void (*testPtr)());
        Report runTests();
        [[deprecated]]
        Report runTestsOfFile(const std::string &fileName);
        Report runTestsOfSuite(const std::string &suiteName);
        const Test &currentTest();
        std::string getCurrentStdOut();
        std::string getCurrentStdErr();

        void setCurrentSuite(const std::string &suiteName);
        std::string &getCurrentSuite();

        static Registry &instance();
    };

    class Registration{
    public:
        Registration(const char *fileName, const char *testName, void (*testPtr)()) noexcept;
    };

    class StartSuite {
    public:
        StartSuite(const char *suiteName) noexcept;
    };

}

#endif //ACACIA_REGISTRY_H
