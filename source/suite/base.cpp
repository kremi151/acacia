//
// Created by Michel on 13.07.2021.
//

#include "base.h"
#include <registry/registry.h>

using namespace acacia;

void BaseTestSuite::name(const std::string &name) {
    state.suiteName = name;
}

void BaseTestSuite::it(const std::string &description, const std::function<void()> &func) {
    auto &elem = state.tests.emplace_back();
    elem.description = description;
    elem.func = func;
}

TestSuiteState BaseTestSuite::describe() {
    state = TestSuiteState{};
    doDescribe();
    TestSuiteState theState = state;
    theState.fileName = fileName();
    if (theState.suiteName.empty()) {
        theState.suiteName = defaultSuiteName();
    }
    state = TestSuiteState{};
    return theState;
}

void BaseTestSuite::beforeAll(const std::function<void()> &func) {
    state.beforeAll.emplace_back(func);
}

void BaseTestSuite::before(const std::function<void()> &func) {
    state.before.emplace_back(func);
}

void BaseTestSuite::after(const std::function<void()> &func) {
    state.after.emplace_back(func);
}

void BaseTestSuite::afterAll(const std::function<void()> &func) {
    state.afterAll.emplace_back(func);
}
