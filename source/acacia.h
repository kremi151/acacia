//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_ACACIA_H
#define ACACIA_ACACIA_H

#include <registry/registry.h>
#include <assertions/assertions.h>
#include <report/report.h>
#include <report/junit.h>
#include <report/acacia_report.h>
#include <suite/base.h>

#define runAcaciaTests() \
acacia::Registry::instance().runTests()

#define __deprecated_runAcaciaFileTests() \
acacia::Registry::instance().runTestsOfFile(__FILE__)

#define TEST_SUITE(name) \
namespace __Acacia__TestSuite_##name##_ { \
    class Suite: public acacia::BaseTestSuite { \
    public: \
        const char *suiteName() final; \
        const char *fileName() final; \
        void describe() override; \
    }; \
    acacia::SuiteRegistration<Suite> __Acacia__suiteRegistration; \
} \
const char *__Acacia__TestSuite_ ## name ## _::Suite::suiteName() { \
    const char *sname = BaseTestSuite::suiteName(); \
    if (sname != nullptr) { \
        return sname; \
    } \
    return #name; \
} \
const char *__Acacia__TestSuite_ ## name ## _::Suite::fileName() { \
    return __FILE__; \
} \
void __Acacia__TestSuite_ ## name ## _::Suite::describe()

namespace acacia {
    int runTests(int argc, char **argv, Report *outReport);
}

#endif //ACACIA_ACACIA_H
