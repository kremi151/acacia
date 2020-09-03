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

#define BEFORE \
void __Acacia__BeforeTests__##__FILE__##__LINE__##(); \
acacia::BeforeRegistration __Acacia__BeforeRegistration_##__FILE__##__LINE__##(__FILE__, __Acacia__BeforeTests__##__FILE__##__LINE__##); \
void __Acacia__BeforeTests__##__FILE__##__LINE__##()

#define AFTER \
void __Acacia__AfterTests__##__FILE__##__LINE__##(); \
acacia::AfterRegistration __Acacia__AfterRegistration##__FILE__##__LINE__##(__FILE__, __Acacia__AfterTests__##__FILE__##__LINE__##); \
void __Acacia__AfterTests__##__FILE__##__LINE__##()

#define runAcaciaTests() \
acacia::Registry::instance().runTests()

#define runAcaciaFileTests() \
acacia::Registry::instance().runTestsOfFile(__FILE__)

#endif //ACACIA_ACACIA_H
