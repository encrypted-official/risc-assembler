#pragma once

#include "opdata.hpp"
#include <string>

std::string int_to_hex(uint8_t val)
{
    const char* digits = "0123456789abcdef";
    std::string s;

    s += digits[(val >> 4) & 0xF];
    s += digits[val & 0xF];

    return s;
}