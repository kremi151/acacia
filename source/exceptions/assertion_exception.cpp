//
// Created by Michel on 03.06.2020.
//

#include "assertion_exception.h"

using namespace acacia;

AssertionException::AssertionException(const char *fileName, std::string testName, unsigned int line,
                                       std::string message): std::exception(), fileName(fileName), testName(std::move(testName)), line(line), message(std::move(message)) {
}

const char * AssertionException::what() const noexcept {
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