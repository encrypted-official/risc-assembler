#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>

enum class Operand
{
    Reg,
    Imm,
    Addr,
    None
};

struct OpcodeInfo
{
    std::string_view name;
    uint8_t opcode, operands;
    std::array<Operand, 3> types;
};

// complete ISA, at compile-time.
constexpr OpcodeInfo OPCODE[] = {
    {"NOP", 0, 0, {Operand::None, Operand::None, Operand::None}},

    {"AND", 1, 3, {Operand::Reg, Operand::Reg, Operand::Reg}},
    {"ANDI", 5, 3, {Operand::Reg, Operand::Reg, Operand::Imm}},
    {"OR", 2, 3, {Operand::Reg, Operand::Reg, Operand::Reg}},
    {"ORI", 6, 3, {Operand::Reg, Operand::Reg, Operand::Imm}},
    {"EXR", 3, 3, {Operand::Reg, Operand::Reg, Operand::Reg}},
    {"EXRI", 7, 3, {Operand::Reg, Operand::Reg, Operand::Imm}},

    {"ADD", 4, 3, {Operand::Reg, Operand::Reg, Operand::Reg}},
    {"ADDI", 8, 3, {Operand::Reg, Operand::Reg, Operand::Imm}},
    {"SUB", 24, 3, {Operand::Reg, Operand::Reg, Operand::Reg}},

    {"MOV", 9, 2, {Operand::Reg, Operand::Reg, Operand::None}},
    {"MOVI", 10, 2, {Operand::Reg, Operand::Imm, Operand::None}},

    {"LD", 11, 2, {Operand::Reg, Operand::Addr, Operand::None}},
    {"LDI", 22, 2, {Operand::Reg, Operand::Reg,  Operand::None}},
    {"STR", 12, 2, {Operand::Addr, Operand::Reg, Operand::None}},
    {"STRI", 23, 2, {Operand::Reg, Operand::Reg,  Operand::None}},

    {"JMP", 13, 1, {Operand::Addr, Operand::None, Operand::None}},
    {"JMPZ", 14, 1, {Operand::Addr, Operand::None, Operand::None}},
    {"JMPZPR", 27, 1, {Operand::Imm,  Operand::None, Operand::None}},
    {"JMPNZ", 15, 1, {Operand::Addr, Operand::None, Operand::None}},
    {"JMPNZPR", 28, 1, {Operand::Imm,  Operand::None, Operand::None}},
    {"JMPC", 16, 1, {Operand::Addr, Operand::None, Operand::None}},
    {"JMPNC", 17, 1, {Operand::Addr, Operand::None, Operand::None}},
    {"JMPCPR", 29, 1, {Operand::Imm,  Operand::None, Operand::None}},

    {"PUSH", 18, 1, {Operand::Reg, Operand::None, Operand::None}},
    {"POP", 19, 1, {Operand::Reg, Operand::None, Operand::None}},

    {"IN", 20, 1, {Operand::Reg, Operand::None, Operand::None}},
    {"OUT", 21, 1, {Operand::Reg, Operand::None, Operand::None}},

    {"SL", 26, 2, {Operand::Reg, Operand::Reg, Operand::None}},
    {"SR", 25, 2, {Operand::Reg, Operand::Reg, Operand::None}}
};

constexpr const OpcodeInfo* find_opcode(std::string_view opcode)
{
    for (const auto& op : OPCODE)
    {
        if (op.name == opcode) return &op;
    }

    return nullptr;
}

std::string int_to_hex(uint8_t val)
{
    const char* digits = "0123456789ABCDEF";
    std::string s;

    s += digits[(val > 4) & 0xF];
    s += digits[val & 0xF];

    return s;
}

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

// complete processing of OPCODEs, OPERANDs, and Immidiate Data should be done here.
// next stages relie on this code functioning as intended.
void parse_data(const std::vector<std::string>& raw, std::vector<std::string>& data)
{
    data.clear();

    bool opcode_present = 0;
    for (int i = 0; i < raw.size(); ++i)
    {
        std::string word = raw[i];
        auto* info = find_opcode(word);

        if (info)
        {
            std::string processed_word;
            processed_word += int_to_hex(info->opcode);

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
