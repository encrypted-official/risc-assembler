#pragma once

#include <string_view>
#include <array>

enum class Operand
{
    RegA,
    RegB,
    RegD,
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
    {"NOP", 0, 0, {Operand::None, Operand::None, Operand::None, Operand::None}},

    {"AND", 1, 3, {Operand::RegD, Operand::RegA, Operand::RegB, Operand::None}},
    {"ANDI", 5, 3, {Operand::RegD, Operand::RegA, Operand::None, Operand::Imm}},
    {"OR", 2, 3, {Operand::RegD, Operand::RegA, Operand::RegB, Operand::None}},
    {"ORI", 6, 3, {Operand::RegD, Operand::RegA, Operand::None, Operand::Imm}},
    {"EXR", 3, 3, {Operand::RegD, Operand::RegA, Operand::RegB, Operand::None}},
    {"EXRI", 7, 3, {Operand::RegD, Operand::RegA, Operand::None, Operand::Imm}},

    {"ADD", 4, 3, {Operand::RegD, Operand::RegA, Operand::RegB, Operand::None}},
    {"ADDI", 8, 3, {Operand::RegD, Operand::RegA, Operand::None, Operand::Imm}},
    {"SUB", 24, 3, {Operand::RegD, Operand::RegA, Operand::RegB, Operand::None}},

    {"MOV", 9, 2, {Operand::RegD, Operand::RegA, Operand::None, Operand::None}},
    {"MOVI", 10, 2, {Operand::RegD, Operand::None, Operand::None, Operand::Imm}},
    {"LD", 11, 2, {Operand::RegD, Operand::None, Operand::None, Operand::Addr}},
    {"LDI", 22, 2, {Operand::RegD, Operand::RegA,  Operand::None, Operand::None}},
    {"STR", 12, 2, {Operand::None, Operand::RegA, Operand::None, Operand::Addr}},
    {"STRI", 23, 2, {Operand::None, Operand::RegA, Operand::RegB,  Operand::None}},

    {"JMP", 13, 1, {Operand::None, Operand::None, Operand::None, Operand::Addr}},
    {"JMPZ", 14, 1, {Operand::None, Operand::None, Operand::None, Operand::Addr}},
    {"JMPZPR", 27, 1, {Operand::None,  Operand::None, Operand::None, Operand::Imm}},
    {"JMPNZ", 15, 1, {Operand::None, Operand::None, Operand::None, Operand::Addr}},
    {"JMPNZPR", 28, 1, {Operand::None,  Operand::None, Operand::None, Operand::Imm}},
    {"JMPC", 16, 1, {Operand::None, Operand::None, Operand::None, Operand::Addr}},
    {"JMPCPR", 29, 1, {Operand::None,  Operand::None, Operand::None, Operand::Imm}},
    {"JMPNC", 17, 1, {Operand::None, Operand::None, Operand::None, Operand::Addr}},
    {"JMPNCPR", 30, 1, {Operand::None,  Operand::None, Operand::None, Operand::Imm}},

    {"PUSH", 18, 1, {Operand::None, Operand::RegA, Operand::None, Operand::None}},
    {"POP", 19, 1, {Operand::None, Operand::RegA, Operand::None, Operand::None}},

    {"IN", 20, 1, {Operand::None, Operand::RegA, Operand::None, Operand::None}},
    {"OUT", 21, 1, {Operand::None, Operand::RegA, Operand::None, Operand::None}},

    {"SL", 26, 2, {Operand::RegD, Operand::RegA, Operand::None, Operand::None}},
    {"SR", 25, 2, {Operand::RegD, Operand::RegA, Operand::None, Operand::None}}
};

constexpr const OpcodeInfo* find_opcode(std::string_view opcode)
{
    for (const auto& op : OPCODE)
    {
        if (op.name == opcode) return &op;
    }

    return nullptr;
}