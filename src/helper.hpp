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

bool validate_numeric(std::string str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(str[i]))) return 0;
    }

    return 1;
}