//
// Created by Michel on 04.06.2020.
//

#include "junit.h"

void acacia::generateJUnitReport(Report &report, std::ofstream &file) {
    file << "<testsuite tests=\"" << report.getTestCount() << "\">" << std::endl;

    auto end = report.results_end();
    for (auto it = report.results_begin() ; it != end ; it++) {
        auto &fileName = (*it).first;
        auto &tests = (*it).second;
        for (const auto &test : tests) {
            file << "\t<testcase classname=\"" << fileName << "\" name=\"" << test.getTestName();
            if (test.isSuccess()) {
                file << "\" />" << std::endl;
                continue;
            }
            file << "\">" << std::endl;

            // TODO: Support different failure types
            // TODO: Escape assertion message
            file << "\t\t<failure type=\"AssertionError\" message=\"" << test.getAssertion() << " (line " << test.getErrorLine() << ")\">"
                 << test.getOutput() << "</failure>" << std::endl
                 << "\t</testcase>" << std::endl;
        }
    }

    file << "</testsuite>" << std::endl;
}