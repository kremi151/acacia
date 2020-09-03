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
acacia::BeforeRegistration __Acacia__BeforeRegistration_##name(__FILE__, __Acacia__BeforeFunc__##name); \
void __Acacia__BeforeFunc__##name()

#define AFTER(name) \
void __Acacia__AfterFunc__##name(); \
acacia::AfterRegistration __Acacia__AfterRegistration_##name(__FILE__, __Acacia__AfterFunc__##name); \
void __Acacia__AfterFunc__##name()

#define runAcaciaTests() \
acacia::Registry::instance().runTests()

#define runAcaciaFileTests() \
acacia::Registry::instance().runTestsOfFile(__FILE__)

#endif //ACACIA_ACACIA_H
