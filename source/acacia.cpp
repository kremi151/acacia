//
// Created by Michel on 12.05.2021.
//

#include "acacia.h"

#include <iostream>
#include <set>
#include <cstring>

namespace acacia {

    void printSuiteResults(const acacia::Report &report, const char *suiteName) {
        std::cout << "Test results for suite " << suiteName << ":" << std::endl;
        for (auto it = report.results_begin() ; it != report.results_end() ; it++) {
            auto &tests = it->second;
            for (const auto & test : tests) {
                if (test.isSuccess()) {
                    std::cout << "[PASSED] ";
                } else {
                    std::cout << "[FAILED] ";
                }
                std::cout << test.getTestName() << std::endl;
            }
        }
    }

    int runTests(int argc, char **argv, Report *outReport) {
        acacia::Report report;

        std::set<suite_name> suites;
        std::set<suite_name> executableSuites;
        bool excludeMode = true;

        // populateSuites(suites);
        Registry::instance().collectSuiteNames(suites);

        executableSuites = suites;

        for (int i = 1 ; i < argc ; i++) {
            char *arg = argv[i];
            if (std::strcmp(arg, "-e") == 0) {
                if (i + 1 >= argc) {
                    std::cerr << "Expected test suite name to exclude with -e option" << std::endl;
                    return 1;
                }
                char *exc = argv[++i];
                executableSuites.erase(exc);
            } else if (std::strcmp(arg, "-t") == 0) {
                if (i + 1 >= argc) {
                    std::cerr << "Expected test suite name to include with -t option" << std::endl;
                    return 1;
                }
                if (excludeMode) {
                    excludeMode = false;
                    executableSuites.clear();
                }
                char *inc = argv[++i];
                auto entry = suites.find(inc);
                if (entry == suites.end()) {
                    std::cerr << "Unknown test suite: " << inc << std::endl;
                    return 1;
                }
                executableSuites.insert(*entry);
            }
        }

        for (auto & suiteName : executableSuites) {
            acacia::Report suiteReport = Registry::instance().runTestsOfSuite(suiteName);
            printSuiteResults(suiteReport, suiteName.c_str());
            report += suiteReport;
        }

        if (outReport != nullptr) {
            *outReport = report;
        }

        return report.getErrorCount();
    }

}