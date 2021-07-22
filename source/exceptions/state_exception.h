//
// Created by Michel on 33.07.2020.
//

#ifndef ACACIA_STATE_EXCEPTION_H
#define ACACIA_STATE_EXCEPTION_H

#include <exception>
#include <string>

namespace acacia {

    class StateException: public std::exception {
    private:
        const std::string message;
    public:
        StateException(std::string message);

        const char *what() const noexcept override;
    };

}

#endif //ACACIA_STATE_EXCEPTION_H
