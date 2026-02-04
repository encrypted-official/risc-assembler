#include "opdata.hpp"
#include "helper.hpp"
#include "error.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>

void fetch_file(const std::string& path, std::vector<std::string>& words)
{
    std::ifstream file(path);
    std::string line;
    
    words.clear();

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word)
        {
            if (word == ";") break;     // ignore comments at fetching phase.
            words.push_back(word);
        }
    }
}

bool validate_and_parse_operand(std::string& opr, const Operand type)
{
    if (type == Operand::Imm || type == Operand::Addr)
    {
        // todo: invalidate if not pure decimal value.
        int val = std::stoi(opr);
        if (val > 255) return 1;

        if (opr.length() <= 1) opr.insert(0, 2 - opr.length(), '0');
    }
    else
    {
        if (*opr.rbegin() == ',') opr.pop_back();

        auto fail = [&]()
        {
            ErrorInfo err{opr, "register not available (use R0-R15)", Error::InvalidRegister};
            console_error(err);
            exit(0);
        };
        
        if (opr.size() <= 1 && opr.size() > 3 || (opr[0] != 'R' && opr[0] != 'r')) fail();

        for (size_t i = 1; i < opr.size(); ++i)
        {
            if (!std::isdigit(static_cast<unsigned char>(opr[i]))) fail();
        }
        
        int val = std::stoi(opr.substr(1));
        if (val > 15) fail();
    
        opr = int_to_hex(static_cast<uint8_t>(val));
        opr.erase(opr.begin());
    }
    
    return 0;
}
    
// complete processing of OPCODEs, OPERANDs, and Immidiate Data should be done here.
// next stages relie on this code functioning as intended.
void parse_data(const std::vector<std::string>& raw, std::vector<std::string>& data)
{
    data.clear();
    
    for (size_t i = 0; i < raw.size(); ++i)
    {
        std::string word = raw[i];
        auto* info = find_opcode(word);
    
        if (info)
        {
            std::string processed_word;
            processed_word += int_to_hex(info->opcode);

            int offset = 1;
            for (int j = 0; j < 4; ++j)
            {
                Operand type = info->types[j];

                if (type == Operand::None) processed_word += (j == 3 ? "00" : "0");
                else {
                    std::string opr = raw[i + offset];
                    offset++;
                    
                    // todo: change loop i to skip remaining operands.
                    if (validate_and_parse_operand(opr, type) == 1) 
                    {
                        break;
                    }

                    processed_word += opr;
                }
            }
    
            i += info->operands;
            data.push_back(processed_word);
        }
    }
}
    
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        ErrorInfo err{"input detection", "required first argument is input assembly file.", Error::AssemblyFileMissing};
        console_error(err);
        exit(0);
    }
    
    std::vector<std::string> raw_data, processed_data;
    
    fetch_file(argv[1], raw_data);
    parse_data(raw_data, processed_data);
    
    for (std::string str : processed_data) std::cout << str << " ";
    std::cout << std::endl;
    
    exit(0);
}
