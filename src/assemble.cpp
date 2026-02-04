#include "opdata.hpp"
#include "helper.hpp"
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
        // int val = std::stoi(opr);
        // if (val > 255) return 1;
    
        // opr = int_to_hex(static_cast<uint8_t>(val));
        // // opr.erase(opr.begin());
    }
    else
    {
        if (*opr.rbegin() == ',') opr.pop_back();
    
        if (opr.size() <= 1 || (opr[0] != 'R' && opr[0] != 'r')) return 1;
        
        int val = std::stoi(opr.substr(1));
        if (val > 15) return 1;
    
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
    
    for (int i = 0; i < raw.size(); ++i)
    {
        std::string word = raw[i];
        auto* info = find_opcode(word);
    
        if (info)
        {
            std::string processed_word;
            processed_word += int_to_hex(info->opcode);

            for (int j = 0; j < 4; ++j)
            {
                Operand type = info->types[j - 1];
                std::string opr = raw[i + j];
            }
    
            i += info->operands;
            data.push_back(processed_word);
        }
    }
}
    
int main(int argc, char* argv[])
{
    if (argc < 2) return 1;
    
    std::vector<std::string> raw_data, processed_data;
    
    fetch_file(argv[1], raw_data);
    parse_data(raw_data, processed_data);
    
    for (std::string str : processed_data) std::cout << str << " ";
    std::cout << std::endl;
    
    return 0;
}
