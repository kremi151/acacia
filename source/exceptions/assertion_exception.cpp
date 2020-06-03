//
// Created by Michel on 03.06.2020.
//

#include "assertion_exception.h"

using namespace acacia;

AssertionException::AssertionException(const char *fileName, const char *testName, unsigned int line,
                                       const char *message): std::exception(message), fileName(fileName), testName(testName), line(line), message(message) {
}

const char * AssertionException::what() const {
    return message.c_str();
}

unsigned int AssertionException::getLine() const {
    return line;
}

const std::string & AssertionException::getFileName() const {
    return fileName;
}

const std::string & AssertionException::getTestName() const {
    return testName;
}