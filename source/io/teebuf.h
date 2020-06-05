//
// Created by Michel on 05.06.2020.
//

#ifndef ACACIA_TEEBUF_H
#define ACACIA_TEEBUF_H

#include <streambuf>

namespace acacia {

    class TeeBuffer: public std::streambuf {
    private:
        std::streambuf *buf1, *buf2;
    protected:
        virtual int overflow(int c) override;
        virtual int sync() override;
    public:
        TeeBuffer(std::streambuf *buf1, std::streambuf *buf2);
    };

}

#endif //ACACIA_TEEBUF_H
