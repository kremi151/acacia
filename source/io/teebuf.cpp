//
// Created by Michel on 05.06.2020.
//

#include "teebuf.h"

using namespace acacia;

TeeBuffer::TeeBuffer(std::streambuf *buf1, std::streambuf *buf2): buf1(buf1), buf2(buf2) {
}

int TeeBuffer::overflow(int c) {
    if (c == EOF) {
        return !EOF;
    } else {
        int rbuf1 = buf1->sputc(c);
        int rbuf2 = buf2->sputc(c);
        return (rbuf1 == EOF || rbuf2 == EOF) ? EOF : c;
    }
}

int TeeBuffer::sync() {
    int rbuf1 = buf1->pubsync();
    int rbuf2 = buf2->pubsync();
    return (rbuf1 == 0 && rbuf2 == 0) ? 0 : EOF;
}