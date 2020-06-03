//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_COMPARE_ASSERTIONS_H
#define ACACIA_COMPARE_ASSERTIONS_H

#include <acacia.h>
#include <exceptions/assertion_exception.h>
#include <sstream>

#define assertBiggerThan(biggest, smallest) \
{auto bg = biggest, sm = smallest; \
if (sm > bg) { \
    std::stringstream ss; \
    ss << "Expected " << bg << " to be bigger than " << sm << ", but was smaller"; \
    throw acacia::AssertionException(__FILE__, acaciaRuntime.currentTest().testName.c_str(), __LINE__, ss.str().c_str()); \
} else if (sm == bg) { \
    std::stringstream ss; \
    ss << "Expected " << bg << " to be bigger than " << sm << ", but was equal"; \
    throw acacia::AssertionException(__FILE__, acaciaRuntime.currentTest().testName.c_str(), __LINE__, ss.str().c_str()); \
}}

#define assertBiggerOrEqualTo(biggest, smallest) \
{auto bg = biggest, sm = smallest; \
if (sm > bg) { \
    std::stringstream ss; \
    ss << "Expected " << bg << " to be bigger than " << sm << ", but was smaller"; \
    throw acacia::AssertionException(__FILE__, acaciaRuntime.currentTest().testName.c_str(), __LINE__, ss.str().c_str()); \
}}

#define assertSmallerThan(smallest, biggest) \
{auto bg = biggest, sm = smallest; \
if (sm > bg) { \
    std::stringstream ss; \
    ss << "Expected " << sm << " to be smaller than " << bg << ", but was bigger"; \
    throw acacia::AssertionException(__FILE__, acaciaRuntime.currentTest().testName.c_str(), __LINE__, ss.str().c_str()); \
} else if (sm == bg) { \
    std::stringstream ss; \
    ss << "Expected " << sm << " to be smaller than " << bg << ", but was equal"; \
    throw acacia::AssertionException(__FILE__, acaciaRuntime.currentTest().testName.c_str(), __LINE__, ss.str().c_str()); \
}}

#define assertSmallerOrEqualTo(smallest, biggest) \
{auto bg = biggest, sm = smallest; \
if (sm > bg) { \
    std::stringstream ss; \
    ss << "Expected " << sm << " to be smaller than " << bg << ", but was bigger"; \
    throw acacia::AssertionException(__FILE__, acaciaRuntime.currentTest().testName.c_str(), __LINE__, ss.str().c_str()); \
}}

#endif //ACACIA_COMPARE_ASSERTIONS_H
