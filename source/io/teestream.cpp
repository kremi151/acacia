//
// Created by Michel on 05.06.2020.
//

#include "teestream.h"

using namespace acacia;

TeeStream::TeeStream(std::ostream &stream1, std::ostream &stream2): std::ostream(&tee), tee(stream1.rdbuf(), stream2.rdbuf()) {
}