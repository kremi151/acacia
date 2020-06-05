//
// Created by Michel on 05.06.2020.
//

#include <iostream>
#include "stream_capture.h"

using namespace acacia;

StreamCapture::StreamCapture(std::ostream &ostream): ostream(ostream), tee(ostream, buffer) {
    oldStream = ostream.rdbuf(tee.rdbuf());
}

StreamCapture::~StreamCapture() {
    ostream.rdbuf(oldStream);
}

std::string StreamCapture::str() {
    return buffer.str();
}
