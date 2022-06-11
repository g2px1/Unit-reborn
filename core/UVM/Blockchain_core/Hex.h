//
// Created by Kirill Zhukov on 11.06.2022.
//

#ifndef UVM_HEX_H
#define UVM_HEX_H
#include "iostream"
#include <sstream>

std::string string_to_hex(std::string &value_to_hex) {
    std::stringstream stream;
    for (const auto &item : value_to_hex) {
        stream << std::hex << int(item);
    }
    return stream.str();
}

std::string bytes_to_hex(uint8_t value_to_hex[32]) {
    std::stringstream stream;
    for (int i = 0; i < 32; i++) {
        stream << std::hex << static_cast<int>(value_to_hex[i]);
    }
    return stream.str();
}
#endif //UVM_HEX_H
