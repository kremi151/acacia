//
// Created by Michel on 13.07.2021.
//

#ifndef ACACIA_SUITE_BASE_H
#define ACACIA_SUITE_BASE_H

#include <functional>

namespace acacia {

    class BaseTestSuite {
    private:
        std::string customName;

    public:
        virtual const char *suiteName();
        virtual const char *fileName() = 0;

        virtual void describe() = 0;

    protected:

        void before(const std::function<void()> &func);
        void beforeAll(const std::function<void()> &func);

        void after(const std::function<void()> &func);
        void afterAll(const std::function<void()> &func);

        void name(const std::string &name);

        void it(const std::string &description, const std::function<void()> &func);
    };

}

#endif //ACACIA_SUITE_BASE_H
