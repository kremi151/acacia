//
// Created by Michel on 13.07.2021.
//

#include "base.h"
#include <registry/registry.h>

using namespace acacia;

void BaseTestSuite::it(const std::string &description, const std::function<void()> &func) {
    Registry::instance().registerTest(fileName(), suiteName(), description.c_str(), func);
}

void BaseTestSuite::beforeAll(const std::function<void()> &func) {
    Registry::instance().registerBefore(true, fileName(), suiteName(), func);
}

void BaseTestSuite::before(const std::function<void()> &func) {
    Registry::instance().registerBefore(false, fileName(), suiteName(), func);
}

void BaseTestSuite::after(const std::function<void()> &func) {
    Registry::instance().registerAfter(false, fileName(), suiteName(), func);
}

void BaseTestSuite::afterAll(const std::function<void()> &func) {
    Registry::instance().registerAfter(true, fileName(), suiteName(), func);
}
