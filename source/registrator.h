//
// Created by Michel on 03.06.2020.
//

#ifndef ACACIA_REGISTRATOR_H
#define ACACIA_REGISTRATOR_H

namespace acacia {

    class Registration{
    public:
        Registration(const char *fileName, const char *testName, void (*testPtr)()) noexcept;
    };

}

#endif //ACACIA_REGISTRATOR_H
