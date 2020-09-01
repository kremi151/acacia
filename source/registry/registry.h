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

    typedef struct {
        void (*funcPtr)();
        test_name testName;
        file_name fileName;
    } Entry;

    typedef struct {
        std::vector<Entry> beforeFile;
        std::vector<Entry> before;
        std::vector<Entry> tests;
        std::vector<Entry> after;
        std::vector<Entry> afterFile;
    } FileEntry;

    class Registry{
    private:
        Registry();

        std::map<file_name, FileEntry> fileEntries;
        const Entry *currentEntryFromList;
        StreamCapture *currentStdOut, *currentStdErr;

        Report runSpecificTests(std::vector<FileEntry> &files);
        bool runTest(const std::string &fileName, const std::string &testName, void (*funcPtr)(), Report &outReport);
    public:
        void registerTest(const char *fileName, const char *testName, void (*testPtr)());
        void registerAfter(const char *fileName, void (*funcPtr)());
        Report runTests();
        Report runTestsOfFile(const std::string &fileName);
        const Entry &currentTest();
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
        BeforeRegistration(const char *fileName, void (*testPtr)()) noexcept;
    };

    class AfterRegistration{
    public:
        AfterRegistration(const char *fileName, void (*testPtr)()) noexcept;
    };

}

#endif //ACACIA_REGISTRY_H
