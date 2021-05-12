//
// Created by Michel on 12.05.2021.
//

#ifndef ACACIA_TEST_SUITES_H
#define ACACIA_TEST_SUITES_H

#include <acacia.h>

#include <map>

namespace acacia {
    typedef acacia::Report(*SuiteRunner)();

    void populateSuites(std::map<std::string, SuiteRunner> &suites);
}

#endif //ACACIA_TEST_SUITES_H
