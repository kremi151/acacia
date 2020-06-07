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
    } Test;

    class Registry{
    private:
        Registry();

        std::vector<Test> tests;
        Test *currentTestFromList;
        StreamCapture *currentStdOut, *currentStdErr;
    public:
        void registerTest(const char *fileName, const char *testName, void (*testPtr)());
        Report runTests();
        const Test &currentTest();
        std::string getCurrentStdOut();
        std::string getCurrentStdErr();

        static Registry &instance();
    };

    class Registration{
    public:
        Registration(const char *fileName, const char *testName, void (*testPtr)()) noexcept;
    };

}

#endif //ACACIA_REGISTRY_H
