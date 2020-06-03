//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_ASSERTION_EXCEPTION_H
#define ACACIA_ASSERTION_EXCEPTION_H

#include <exception>
#include <string>

namespace acacia {

    class AssertionException: public std::exception {
    private:
        const std::string fileName;
        const std::string testName;
        const unsigned int line;
        const std::string message;
    public:
        AssertionException(const char* fileName, const char* testName, unsigned int line, const char* message);

        const char *what() const override;
        const std::string &getFileName() const;
        const std::string &getTestName() const;
        unsigned int getLine() const;
    };

}

#endif //ACACIA_ASSERTION_EXCEPTION_H
