//
// Created by Michel on 07.06.2020.
//

#include "output_assertions.h"

#include <registry/registry.h>
#include <exceptions/assertion_exception.h>

void __acacia_assertStandardOutputHas(const char *text, const char *fileName, unsigned int line) {
    auto &registry = acacia::Registry::instance();
    if (registry.getCurrentStdOut().find(text) == std::string::npos) {
        throw acacia::AssertionException(fileName, registry.currentTest().testName, line, std::string("Expected string was not found in standard output: ") + text);
    }
}

void __acacia_assertStandardOutputHasNot(const char *text, const char *fileName, unsigned int line) {
    auto &registry = acacia::Registry::instance();
    if (registry.getCurrentStdOut().find(text) != std::string::npos) {
        throw acacia::AssertionException(fileName, registry.currentTest().testName, line, std::string("String was found in standard output: ") + text);
    }
}

void __acacia_assertErrorOutputHas(const char *text, const char *fileName, unsigned int line) {
    auto &registry = acacia::Registry::instance();
    if (registry.getCurrentStdErr().find(text) == std::string::npos) {
        throw acacia::AssertionException(fileName, registry.currentTest().testName, line, std::string("Expected string was not found in error output: ") + text);
    }
}

void __acacia_assertErrorOutputHasNot(const char *text, const char *fileName, unsigned int line) {
    auto &registry = acacia::Registry::instance();
    if (registry.getCurrentStdErr().find(text) != std::string::npos) {
        throw acacia::AssertionException(fileName, registry.currentTest().testName, line, std::string("String was found in error output: ") + text);
    }
}
