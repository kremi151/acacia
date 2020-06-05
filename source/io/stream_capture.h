//
// Created by Michel on 05.06.2020.
//

#ifndef ACACIA_STREAM_CAPTURE_H
#define ACACIA_STREAM_CAPTURE_H

#include <iosfwd>
#include <sstream>
#include <io/teestream.h>

namespace acacia {

    class StreamCapture {
    private:
        std::ostream &ostream;
        std::streambuf *oldStream;
        std::stringstream buffer;
        TeeStream tee;
    public:
        StreamCapture(std::ostream &ostream);
        ~StreamCapture();

        std::string str();
    };

}

#endif //ACACIA_STREAM_CAPTURE_H
