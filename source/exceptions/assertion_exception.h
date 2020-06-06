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
        AssertionException(const char* fileName, std::string testName, unsigned int line, std::string message);

        const char *what() const noexcept override;
        const std::string &getFileName() const;
        const std::string &getTestName() const;
        unsigned int getLine() const;
    };

}

#endif //ACACIA_ASSERTION_EXCEPTION_H
