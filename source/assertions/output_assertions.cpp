//
// Created by Michel on 07.06.2020.
//

#include "output_assertions.h"

#include <registry/registry.h>
#include <exceptions/assertion_exception.h>

using namespace acacia;

void assertions::__assertStandardOutputHas(const char *text, const char *fileName, unsigned int line) {
    auto &registry = acacia::Registry::instance();
    if (registry.getCurrentStdOut().find(text) == std::string::npos) {
        throw acacia::AssertionException(fileName, registry.currentTestName(), line, std::string("Expected string was not found in standard output: ") + text);
    }
}

void assertions::__assertStandardOutputHasNot(const char *text, const char *fileName, unsigned int line) {
    auto &registry = acacia::Registry::instance();
    if (registry.getCurrentStdOut().find(text) != std::string::npos) {
        throw acacia::AssertionException(fileName, registry.currentTestName(), line, std::string("String was found in standard output: ") + text);
    }
}

void assertions::__assertErrorOutputHas(const char *text, const char *fileName, unsigned int line) {
    auto &registry = acacia::Registry::instance();
    if (registry.getCurrentStdErr().find(text) == std::string::npos) {
        throw acacia::AssertionException(fileName, registry.currentTestName(), line, std::string("Expected string was not found in error output: ") + text);
    }
}

void assertions::__assertErrorOutputHasNot(const char *text, const char *fileName, unsigned int line) {
    auto &registry = acacia::Registry::instance();
    if (registry.getCurrentStdErr().find(text) != std::string::npos) {
        throw acacia::AssertionException(fileName, registry.currentTestName(), line, std::string("String was found in error output: ") + text);
    }
}
