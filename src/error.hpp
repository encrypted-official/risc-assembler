#pragma once

#include <string>
#include <iostream>

enum class Error
{
    AssemblyFileMissing,
    AddressOutOfBound,
    ImmediateDataOutOfBound,
    InvalidRegister,
    NonNumericValue
};

struct ErrorInfo
{
    std::string data, msg;
    Error type;
};

std::string err_to_str(Error err)
{
    std::string cnv[] = {"AssemblyFileMissing", "AddressOutOfBound", "ImmediateDataOutOfBound", "InvalidRegister", "NonNumericValue"};
    return cnv[static_cast<int>(err)];
}

void console_error(ErrorInfo info)
{
    std::cout << "| Error: " << err_to_str(info.type) << "\n";
    std::cout << "| At : " << info.data << "\n";
    std::cout << "| Msg: " << info.msg << std::endl;
}