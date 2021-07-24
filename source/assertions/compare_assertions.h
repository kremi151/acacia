//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_COMPARE_ASSERTIONS_H
#define ACACIA_COMPARE_ASSERTIONS_H

#include <registry/registry.h>
#include <exceptions/assertion_exception.h>
#include <sstream>

namespace acacia::assertions {

    template <class _type_biggest, class _type_smallest>
    void __assertBiggerThan(const _type_biggest &biggest, const _type_smallest &smallest, const char *file, unsigned int line) {
        if (smallest > biggest) {
            std::stringstream ss;
            ss << "Expected " << biggest << " to be bigger than " << smallest << ", but was smaller";
            throw acacia::AssertionException(file, acacia::Registry::instance().currentTestName(), line, ss.str());
        } else if (smallest == biggest) {
            std::stringstream ss;
            ss << "Expected " << biggest << " to be bigger than " << smallest << ", but was equal";
            throw acacia::AssertionException(file, acacia::Registry::instance().currentTestName(), line, ss.str());
        }
    }

    template <class _type_smallest, class _type_biggest>
    void __assertSmallerThan(const _type_smallest &smallest, const _type_biggest &biggest, const char *file, unsigned int line) {
        if (smallest > biggest) {
            std::stringstream ss;
            ss << "Expected " << smallest << " to be smaller than " << biggest << ", but was bigger";
            throw acacia::AssertionException(file, acacia::Registry::instance().currentTestName(), line, ss.str());
        } else if (smallest == biggest) {
            std::stringstream ss;
            ss << "Expected " << smallest << " to be smaller than " << biggest << ", but was equal";
            throw acacia::AssertionException(file, acacia::Registry::instance().currentTestName(), line, ss.str());
        }
    }

    template <class _type_biggest, class _type_smallest>
    void __assertBiggerOrEqualTo(const _type_biggest &biggest, const _type_smallest &smallest, const char *file, unsigned int line) {
        if (smallest > biggest) {
            std::stringstream ss;
            ss << "Expected " << biggest << " to be bigger than " << smallest << ", but was smaller";
            throw acacia::AssertionException(file, acacia::Registry::instance().currentTestName(), line, ss.str());
        }
    }

    template <class _type_smallest, class _type_biggest>
    void __assertSmallerOrEqualTo(const _type_smallest &smallest, const _type_biggest &biggest, const char *file, unsigned int line) {
        if (smallest > biggest) {
            std::stringstream ss;
            ss << "Expected " << smallest << " to be smaller than " << biggest << ", but was bigger";
            throw acacia::AssertionException(file, acacia::Registry::instance().currentTestName(), line, ss.str());
        }
    }

}

#define assertBiggerThan(biggest, smallest) \
acacia::assertions::__assertBiggerThan(biggest, smallest, __FILE__, __LINE__)

#define assertSmallerThan(smallest, biggest) \
acacia::assertions::__assertSmallerThan(smallest, biggest, __FILE__, __LINE__)

#define assertBiggerOrEqualTo(biggest, smallest) \
acacia::assertions::__assertBiggerOrEqualTo(biggest, smallest, __FILE__, __LINE__)

#define assertSmallerOrEqualTo(smallest, biggest) \
acacia::assertions::__assertSmallerOrEqualTo(smallest, biggest, __FILE__, __LINE__)

#endif //ACACIA_COMPARE_ASSERTIONS_H
