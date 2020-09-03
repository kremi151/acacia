//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_REGISTRY_H
#define ACACIA_REGISTRY_H

#include <vector>
#include <map>
#include <string>
#include <report/report.h>
#include <io/stream_capture.h>

namespace acacia {

    typedef std::string file_name;
    typedef std::string test_name;

    typedef void (*func_ptr)();

    typedef struct {
        void (*funcPtr)();
        test_name testName;
        file_name fileName;
    } Entry;

    typedef struct {
        std::string fileName;
        std::vector<func_ptr> beforeFile;
        std::vector<func_ptr> before;
        std::vector<Entry> tests;
        std::vector<func_ptr> after;
        std::vector<func_ptr> afterFile;
    } FileEntry;

    class Registry{
    private:
        Registry();

        std::map<file_name, FileEntry> fileEntries;
        std::string _currentTestName;
        StreamCapture *currentStdOut, *currentStdErr;

        Report runSpecificTests(std::vector<FileEntry> &files);
        bool runTest(const std::string &fileName, const std::string &testName, const std::vector<func_ptr> &steps, Report &outReport);
    public:
        void registerTest(const char *fileName, const char *testName, void (*testPtr)());
        void registerBefore(bool file, const char *fileName, void (*funcPtr)());
        void registerAfter(bool file, const char *fileName, void (*funcPtr)());
        Report runTests();
        Report runTestsOfFile(const std::string &fileName);
        const std::string &currentTestName();
        std::string getCurrentStdOut();
        std::string getCurrentStdErr();

        static Registry &instance();
    };

    class TestRegistration{
    public:
        TestRegistration(const char *fileName, const char *testName, void (*testPtr)()) noexcept;
    };

    class BeforeRegistration{
    public:
        BeforeRegistration(bool file, const char *fileName, void (*testPtr)()) noexcept;
    };

    class AfterRegistration{
    public:
        AfterRegistration(bool file, const char *fileName, void (*testPtr)()) noexcept;
    };

}

#endif //ACACIA_REGISTRY_H
