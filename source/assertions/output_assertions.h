//
// Created by Michel on 07.06.2020.
//

#ifndef ACACIA_OUTPUT_ASSERTIONS_H
#define ACACIA_OUTPUT_ASSERTIONS_H

namespace acacia::assertions {

    void __assertStandardOutputHas(const char *text, const char *fileName, unsigned int line);

    void __assertStandardOutputHasNot(const char *text, const char *fileName, unsigned int line);

    void __assertErrorOutputHas(const char *text, const char *fileName, unsigned int line);

    void __assertErrorOutputHasNot(const char *text, const char *fileName, unsigned int line);

}

#define assertStandardOutputHas(text) \
acacia::assertions::__assertStandardOutputHas(text, __FILE__, __LINE__)

#define assertStandardOutputHasNot(text) \
acacia::assertions::__assertStandardOutputHasNot(text, __FILE__, __LINE__)

#define assertErrorOutputHas(text) \
acacia::assertions::__assertErrorOutputHas(text, __FILE__, __LINE__)

#define assertErrorOutputHasNot(text) \
acacia::assertions::__assertErrorOutputHasNot(text, __FILE__, __LINE__)

#endif //ACACIA_OUTPUT_ASSERTIONS_H
