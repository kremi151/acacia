//
// Created by Michel on 04.06.2020.
//

#include "junit.h"

#include <sstream>

void acacia::generateJUnitReport(Report &report, std::ofstream &file) {
    file << "<testsuite tests=\"" << report.getTestCount() << "\">" << std::endl;

    std::stringstream totalStdout;
    std::stringstream totalStderr;

    auto end = report.results_end();
    for (auto it = report.results_begin() ; it != end ; it++) {
        auto &fileName = (*it).first;
        auto &tests = (*it).second;
        for (const auto &test : tests) {
            totalStdout << test.getOutput();
            totalStderr << test.getErrorOutput();

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

    file << "\t<system-out>" << totalStdout.str() << "</system-out>" << std::endl;
    file << "\t<system-err>" << totalStderr.str() << "</system-err>" << std::endl;

    file << "</testsuite>" << std::endl;
}