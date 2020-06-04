//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_COMPARE_ASSERTIONS_H
#define ACACIA_COMPARE_ASSERTIONS_H

#include <acacia.h>
#include <exceptions/assertion_exception.h>
#include <sstream>

template <class _type>
void __acacia_assertBiggerThan(_type biggest, _type smallest, const char *file, unsigned int line) {
    if (smallest > biggest) {
        std::stringstream ss;
        ss << "Expected " << biggest << " to be bigger than " << smallest << ", but was smaller";
        throw acacia::AssertionException(file, acacia::Registry::instance().currentTest().testName, line, ss.str());
    } else if (smallest == biggest) {
        std::stringstream ss;
        ss << "Expected " << biggest << " to be bigger than " << smallest << ", but was equal";
        throw acacia::AssertionException(file, acacia::Registry::instance().currentTest().testName, line, ss.str());
    }
}

#define assertBiggerThan(biggest, smallest) \
__acacia_assertBiggerThan(biggest, smallest, __FILE__, __LINE__);

template <class _type>
void __acacia_assertSmallerThan(_type smallest, _type biggest, const char *file, unsigned int line) {
    if (smallest > biggest) {
        std::stringstream ss;
        ss << "Expected " << smallest << " to be smaller than " << biggest << ", but was bigger";
        throw acacia::AssertionException(file, acacia::Registry::instance().currentTest().testName, line, ss.str());
    } else if (smallest == biggest) {
        std::stringstream ss;
        ss << "Expected " << smallest << " to be smaller than " << bigger << ", but was equal";
        throw acacia::AssertionException(file, acacia::Registry::instance().currentTest().testName, line, ss.str());
    }
}

#define assertSmallerThan(smallest, biggest) \
__acacia_assertSmallerThan(smallest, biggest, __FILE__, __LINE__);

template <class _type>
void __acacia_assertBiggerOrEqualTo(_type biggest, _type smallest, const char *file, unsigned int line) {
    if (smallest > biggest) {
        std::stringstream ss;
        ss << "Expected " << biggest << " to be bigger than " << smallest << ", but was smaller";
        throw acacia::AssertionException(file, acacia::Registry::instance().currentTest().testName, line, ss.str());
    }
}

#define assertBiggerOrEqualTo(biggest, smallest) \
__acacia_assertBiggerOrEqualTo(biggest, smallest, __FILE__, __LINE__);

template <class _type>
void __acacia_assertSmallerOrEqualTo(_type smallest, _type biggest, const char *file, unsigned int line) {
    if (smallest > biggest) {
        std::stringstream ss;
        ss << "Expected " << smallest << " to be smaller than " << biggest << ", but was bigger";
        throw acacia::AssertionException(file, acacia::Registry::instance().currentTest().testName, line, ss.str());
    }
}

#define assertSmallerOrEqualTo(smallest, biggest) \
__acacia_assertSmallerOrEqualTo(smallest, biggest, __FILE__, __LINE__);

#endif //ACACIA_COMPARE_ASSERTIONS_H
