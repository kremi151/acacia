//
// Created by Michel on 05.06.2020.
//

#ifndef ACACIA_TEESTREAM_H
#define ACACIA_TEESTREAM_H

#include <iostream>
#include <io/teebuf.h>

namespace acacia {

    class TeeStream: public std::ostream {
    private:
        TeeBuffer tee;
    public:
        TeeStream(std::ostream &stream1, std::ostream &stream2);
    };

}

#endif //ACACIA_TEESTREAM_H
