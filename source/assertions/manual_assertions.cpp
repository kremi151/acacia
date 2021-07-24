//
// Created by Michel on 21.07.2020.
//

#include "manual_assertions.h"

#include <registry/registry.h>
#include <exceptions/assertion_exception.h>

using namespace acacia;

void assertions::__fail(const std::string& message, const char *file, unsigned int line) {
    throw acacia::AssertionException(file, acacia::Registry::instance().currentTestName(), line, message);
}
