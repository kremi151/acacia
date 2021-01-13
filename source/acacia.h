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

#define TEST(name) \
void __Acacia__Test__##name(); \
acacia::Registration __Acacia__Registration_##name(__FILE__, #name, __Acacia__Test__##name); \
void __Acacia__Test__##name()

#define runAcaciaTests() \
acacia::Registry::instance().runTests()

#define __deprecated_runAcaciaFileTests() \
acacia::Registry::instance().runTestsOfFile(__FILE__)

#define TEST_SUITE(name) \
namespace __Acacia__TestSuite_##name { \
    acacia::StartSuite suite(#name); \
    acacia::Report runSuite() { \
        return acacia::Registry::instance().runTestsOfSuite(#name); \
    } \
} \
namespace __Acacia__TestSuite_##name

namespace acacia {
    int runTests(int argc, char **argv, Report *outReport);
}

#endif //ACACIA_ACACIA_H
