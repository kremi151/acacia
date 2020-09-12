//
// Created by Michel Kremer on 05.08.2020.
//

#include "boolean_assertions.h"

#include <registry/registry.h>
#include <exceptions/assertion_exception.h>

void __acacia_assertTrue(bool value, const char *file, unsigned int line) {
    if (!value) {
        throw acacia::AssertionException(file, acacia::Registry::instance().currentTest().testName,
                line, "Expected value to be true, but was false");
    }
}

void __acacia_assertFalse(bool value, const char *file, unsigned int line) {
    if (value) {
        throw acacia::AssertionException(file, acacia::Registry::instance().currentTest().testName,
                line, "Expected value to be false, but was true");
    }
}