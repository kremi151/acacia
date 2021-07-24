//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_EQUALITY_ASSERTIONS_H
#define ACACIA_EQUALITY_ASSERTIONS_H

#include <registry/registry.h>
#include <exceptions/assertion_exception.h>
#include <sstream>

namespace acacia::assertions {

    template<class _type_expected, class _type_actual>
    void __assertEquals(const _type_expected &expected, const _type_actual &actual, const char *file,
                               unsigned int line) {
        if (expected != actual) {
            std::stringstream ss;
            ss << "Expected " << expected << " but got " << actual;
            throw acacia::AssertionException(file, acacia::Registry::instance().currentTestName(), line, ss.str());
        }
    }

    template<class _type_expected, class _type_actual>
    void __assertNotEquals(const _type_expected &expected, const _type_actual &actual, const char *file,
                                  unsigned int line) {
        if (expected == actual) {
            std::stringstream ss;
            ss << "Expected " << expected << " to not equal " << actual;
            throw acacia::AssertionException(file, acacia::Registry::instance().currentTestName(), line, ss.str());
        }
    }

}

#define assertEquals(expected, actual) \
acacia::assertions::__assertEquals(expected, actual, __FILE__, __LINE__)

#define assertNotEquals(expected, actual) \
acacia::assertions::__assertNotEquals(expected, actual, __FILE__, __LINE__)

#endif //ACACIA_EQUALITY_ASSERTIONS_H
