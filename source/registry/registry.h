//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_REGISTRY_H
#define ACACIA_REGISTRY_H

#include <vector>
#include <string>

namespace acacia {

    typedef struct {
        void (*testPtr)();
        std::string testName;
        std::string fileName;
    } Test;

    class Registry{
    private:
        std::vector<Test> tests;
        Test *currentTestFromList;
    public:
        Registry();

        void registerTest(const char *fileName, const char *testName, void (*testPtr)());
        int runTests();
        const Test &currentTest();
    };

}

#endif //ACACIA_REGISTRY_H
