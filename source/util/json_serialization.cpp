//
// Created by Michel Kremer on 28.07.2020.
//

#include "json_serialization.h"

#include <sstream>
#include <iomanip>

std::string acacia::util::escapeJsonString(const std::string &str) {
    std::ostringstream o;
    for (auto &c : str) {
        switch (c) {
            case '"': o << "\\\""; break;
            case '\\': o << "\\\\"; break;
            case '\b': o << "\\b"; break;
            case '\f': o << "\\f"; break;
            case '\n': o << "\\n"; break;
            case '\r': o << "\\r"; break;
            case '\t': o << "\\t"; break;
            default: {
                if (c >= '\x00' && c <= '\x1f') {
                    o << "\\u" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(c);
                } else {
                    o << c;
                }
                break;
            }
        }
    }
    return o.str();
}
