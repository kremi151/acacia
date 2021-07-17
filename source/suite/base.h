//
// Created by Michel on 13.07.2021.
//

#ifndef ACACIA_SUITE_BASE_H
#define ACACIA_SUITE_BASE_H

#include <functional>
#include <string>
#include <vector>

namespace acacia {

    typedef struct {
        std::string description;
        std::function<void()> func;
    } TestSuiteStateTest;

    typedef struct {
        std::string suiteName;
        std::string fileName;
        std::vector<TestSuiteStateTest> tests;
        std::vector<std::function<void()>> beforeAll;
        std::vector<std::function<void()>> before;
        std::vector<std::function<void()>> after;
        std::vector<std::function<void()>> afterAll;
    } TestSuiteState;

    class BaseTestSuite {
    private:
        TestSuiteState state;

    public:
        virtual const char *suiteName() = 0;
        virtual const char *fileName() = 0;

        TestSuiteState describe();

    protected:
        virtual void doDescribe() = 0;

        void before(const std::function<void()> &func);
        void beforeAll(const std::function<void()> &func);

        void after(const std::function<void()> &func);
        void afterAll(const std::function<void()> &func);

        void name(const std::string &name);

        void it(const std::string &description, const std::function<void()> &func);
    };

}

#endif //ACACIA_SUITE_BASE_H
