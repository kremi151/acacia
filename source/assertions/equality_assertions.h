//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_EQUALITY_ASSERTIONS_H
#define ACACIA_EQUALITY_ASSERTIONS_H

#include <acacia.h>
#include <exceptions/assertion_exception.h>
#include <sstream>

#define assertEquals(expected, actual) \
{auto ex = expected, ac = actual; \
if (ex != ac) { \
    std::stringstream ss; \
    ss << "Expected " << ex << " but got " << ac; \
    throw acacia::AssertionException(__FILE__, acacia::runtime().currentTest().testName.c_str(), __LINE__, ss.str().c_str()); \
}}

#define assertNotEquals(expected, actual) \
{auto ex = expected, ac = actual; \
if (ex == ac) { \
    std::stringstream ss; \
    ss << "Expected " << ex << " to not equal " << ac; \
    throw acacia::AssertionException(__FILE__, acacia::runtime().currentTest().testName.c_str(), __LINE__, ss.str().c_str()); \
}}

#endif //ACACIA_EQUALITY_ASSERTIONS_H
