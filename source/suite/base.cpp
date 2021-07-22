//
// Created by Michel on 13.07.2021.
//

#include "base.h"
#include <registry/registry.h>
#include <exceptions/state_exception.h>

using namespace acacia;

TestSuiteState& BaseTestSuite::accessState(const char *fnName) {
    if (state == nullptr) {
        throw StateException(std::string("Suite function \"") + fnName + "\" should not be called in tests!");
    }
    return *state;
}

void BaseTestSuite::name(const std::string &name) {
    accessState("name").suiteName = name;
}

void BaseTestSuite::it(const std::string &description, const std::function<void()> &func) {
    auto &elem = accessState("it").tests.emplace_back();
    elem.description = description;
    elem.func = func;
}

void BaseTestSuite::describe(TestSuiteState *s) {
    this->state = s;
    doDescribe();
    s->fileName = fileName();
    if (s->suiteName.empty()) {
        s->suiteName = defaultSuiteName();
    }
    this->state = nullptr;
}

void BaseTestSuite::beforeAll(const std::function<void()> &func) {
    accessState("beforeAll").beforeAll.emplace_back(func);
}

void BaseTestSuite::before(const std::function<void()> &func) {
    accessState("before").before.emplace_back(func);
}

void BaseTestSuite::after(const std::function<void()> &func) {
    accessState("after").after.emplace_back(func);
}

void BaseTestSuite::afterAll(const std::function<void()> &func) {
    accessState("afterAll").afterAll.emplace_back(func);
}
