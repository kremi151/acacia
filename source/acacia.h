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
    protected: \
        void doDescribe() override; \
    public: \
        const char *suiteName() final; \
        const char *fileName() final; \
    }; \
    acacia::SuiteRegistration<Suite> __Acacia__suiteRegistration; \
} \
const char *__Acacia__TestSuite_ ## name ## _::Suite::suiteName() { \
    return #name; \
} \
const char *__Acacia__TestSuite_ ## name ## _::Suite::fileName() { \
    return __FILE__; \
} \
void __Acacia__TestSuite_ ## name ## _::Suite::doDescribe()

namespace acacia {
    int runTests(int argc, char **argv, Report *outReport);
}

#endif //ACACIA_ACACIA_H
