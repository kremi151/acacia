//
// Created by Michel on 22.07.2021.
//

#include "state_exception.h"

using namespace acacia;

StateException::StateException(std::string message): message(std::move(message)) {
}

const char *StateException::what() const noexcept {
    return message.c_str();
}
