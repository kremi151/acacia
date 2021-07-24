//
// Created by Michel Kremer on 05.08.2020.
//

#ifndef ACACIA_BOOLEAN_ASSERTIONS_H
#define ACACIA_BOOLEAN_ASSERTIONS_H

#include <registry/registry.h>
#include <exceptions/assertion_exception.h>

namespace acacia::assertions {

    template<class T>
    void __assertTrue(const T &value, const char *file, unsigned int line) {
        if (!value) {
            throw acacia::AssertionException(file, acacia::Registry::instance().currentTestName(),
                                             line, "Expected value to be true, but was false");
        }
    }

    template<class T>
    void __assertFalse(const T &value, const char *file, unsigned int line) {
        if (value) {
            throw acacia::AssertionException(file, acacia::Registry::instance().currentTestName(),
                                             line, "Expected value to be false, but was true");
        }
    }

}

#define assertTrue(value) \
acacia::assertions::__assertTrue(value, __FILE__, __LINE__)

#define assertFalse(value) \
acacia::assertions::__assertFalse(value, __FILE__, __LINE__)

#endif //ACACIA_BOOLEAN_ASSERTIONS_H
