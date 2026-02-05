#pragma once

#include <string>
#include <iostream>

enum class Error
{
    AssemblyFileMissing,
    OutOfBoundRegister,
    OutOfBoundAddress,
    OutOfBoundImmediateData,
    InvalidRegister,
    InvalidAddress,
    InvalidImmediateData
};

struct ErrorInfo
{
    std::string data, msg;
    Error type;
};

std::string err_to_str(Error err)
{
    std::string cnv[] = {"AssemblyFileMissing", "OutOfBoundRegister", "OutOfBoundAddress", "OutOfBoundImmediateData", "InvalidRegister", "InvalidAddress", "InvalidImmediateData"};
    return cnv[static_cast<int>(err)];
}

void console_error(ErrorInfo info)
{
    std::cout << "| Error: " << err_to_str(info.type) << "\n";
    std::cout << "| At : " << info.data << "\n";
    std::cout << "| Msg: " << info.msg << std::endl;
}