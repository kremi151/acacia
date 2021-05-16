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
acacia::TestRegistration __Acacia__Registration_##name(__FILE__, #name, __Acacia__Test__##name); \
void __Acacia__Test__##name()

#define BEFORE(name) \
void __Acacia__BeforeFunc__##name(); \
acacia::BeforeRegistration __Acacia__BeforeRegistration_##name(false, __FILE__, __Acacia__BeforeFunc__##name); \
void __Acacia__BeforeFunc__##name()

#define AFTER(name) \
void __Acacia__AfterFunc__##name(); \
acacia::AfterRegistration __Acacia__AfterRegistration_##name(false, __FILE__, __Acacia__AfterFunc__##name); \
void __Acacia__AfterFunc__##name()

#define BEFORE_FILE(name) \
void __Acacia__BeforeFileFunc__##name(); \
acacia::BeforeRegistration __Acacia__BeforeFileRegistration_##name(true, __FILE__, __Acacia__BeforeFileFunc__##name); \
void __Acacia__BeforeFileFunc__##name()

#define AFTER_FILE(name) \
void __Acacia__AfterFileFunc__##name(); \
acacia::AfterRegistration __Acacia__AfterFileRegistration_##name(true, __FILE__, __Acacia__AfterFileFunc__##name); \
void __Acacia__AfterFileFunc__##name()

#define runAcaciaTests() \
acacia::Registry::instance().runTests()

#define __deprecated_runAcaciaFileTests() \
acacia::Registry::instance().runTestsOfFile(__FILE__)

#define ACACIA_INCLUDES_BEGIN
#define ACACIA_INCLUDES_END

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
