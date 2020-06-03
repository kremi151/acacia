//
// Created by Michel on 03.06.2020.
//

#include "registrator.h"

#include <acacia.h>

using namespace acacia;

Registration::Registration(const char *fileName, const char *testName, void (*testPtr)()) noexcept {
    runtime().registerTest(fileName, testName, testPtr);
}