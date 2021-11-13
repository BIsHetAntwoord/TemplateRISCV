#ifndef _TEMPLATERISC_RISCV_INSTR_RV32I_HPP
#define _TEMPLATERISC_RISCV_INSTR_RV32I_HPP

#include "riscv/instr/base.hpp"
#include "riscv/utils/signextend.hpp"

// LUI
template <typename Mem, typename Reg, uint32_t Funct3, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0110111, Funct3, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd, SignExtend<Decoder::u_imm, 31>::result>::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// AUIPC
template <typename Mem, typename Reg, uint32_t Funct3, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0010111, Funct3, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd, SignExtend<Decoder::u_imm, 31>::result + Reg::pc>::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// JAL
template <typename Mem, typename Reg, uint32_t Funct3, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1101111, Funct3, Funct7, Decoder> {
    using mem = Mem;
    using reg = RegisterAddPC<
                    typename WriteRegister<Reg, Decoder::rd, Reg::pc + 4>::result,
                    SignExtend<Decoder::j_imm, 20>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = false;
};

// JALR
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100111, 0b000, Funct7, Decoder> {
    using mem = Mem;
    using reg = RegisterSetPC<
                    typename WriteRegister<Reg, Decoder::rd, Reg::pc + 4>::result,
                    (SignExtend<Decoder::i_imm, 11>::result + ReadRegister<Reg, Decoder::rs1>::result) & ~uint64_t(1)
                >::result;

    const static bool done = false;
    const static bool update_pc = false;
};

// BEQ
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100011, 0b000, Funct7, Decoder> {
    const static bool cond = ReadRegister<Reg, Decoder::rs1>::result == ReadRegister<Reg, Decoder::rs2>::result;

    using mem = Mem;
    using reg = RegisterSetPC<
                    Reg,
                    Reg::pc + (cond ? SignExtend<Decoder::b_imm, 12>::result : 0)
                >::result;

    const static bool done = false;
    const static bool update_pc = !cond;
};

// BNE
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100011, 0b001, Funct7, Decoder> {
    const static bool cond = ReadRegister<Reg, Decoder::rs1>::result != ReadRegister<Reg, Decoder::rs2>::result;

    using mem = Mem;
    using reg = RegisterSetPC<
                    Reg,
                    Reg::pc + (cond ? SignExtend<Decoder::b_imm, 12>::result : 0)
                >::result;

    const static bool done = false;
    const static bool update_pc = !cond;
};

// BLT
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100011, 0b100, Funct7, Decoder> {
    const static bool cond = (int64_t(ReadRegister<Reg, Decoder::rs1>::result) < int64_t(ReadRegister<Reg, Decoder::rs2>::result));

    using mem = Mem;
    using reg = RegisterSetPC<
                    Reg,
                    Reg::pc + (cond ? SignExtend<Decoder::b_imm, 12>::result : 0)
                >::result;

    const static bool done = false;
    const static bool update_pc = !cond;
};

// BGE
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100011, 0101, Funct7, Decoder> {
    const static bool cond = int64_t(ReadRegister<Reg, Decoder::rs1>::result) >= int64_t(ReadRegister<Reg, Decoder::rs2>::result);

    using mem = Mem;
    using reg = RegisterSetPC<
                    Reg,
                    Reg::pc + (cond ? SignExtend<Decoder::b_imm, 12>::result : 0)
                >::result;

    const static bool done = false;
    const static bool update_pc = !cond;
};

// BLTU
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100011, 0b110, Funct7, Decoder> {
    const static bool cond = (ReadRegister<Reg, Decoder::rs1>::result < ReadRegister<Reg, Decoder::rs2>::result);

    using mem = Mem;
    using reg = RegisterSetPC<
                    Reg,
                    Reg::pc + (cond ? SignExtend<Decoder::b_imm, 12>::result : 0)
                >::result;

    const static bool done = false;
    const static bool update_pc = !cond;
};

// BGEU
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100011, 0b111, Funct7, Decoder> {
    const static bool cond = ReadRegister<Reg, Decoder::rs1>::result >= ReadRegister<Reg, Decoder::rs2>::result;

    using mem = Mem;
    using reg = RegisterSetPC<
                    Reg,
                    Reg::pc + (cond ? SignExtend<Decoder::b_imm, 12>::result : 0)
                >::result;

    const static bool done = false;
    const static bool update_pc = !cond;
};

// LB
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0000011, 0b000, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        Read<uint8_t, Mem,
                            ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::i_imm, 11>::result
                        >::result,
                        7
                    >::result>::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// LH
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0000011, 0b001, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        Read<uint16_t, Mem,
                            ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::i_imm, 11>::result
                        >::result,
                        15
                    >::result>::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// LW
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0000011, 0b010, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        Read<uint32_t, Mem,
                            ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::i_imm, 11>::result
                        >::result,
                        31
                    >::result>::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// LBU
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0000011, 0b100, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    Read<uint8_t, Mem,
                        ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::i_imm, 11>::result
                    >::result>::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// LHU
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0000011, 0b101, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    Read<uint16_t, Mem,
                            ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::i_imm, 11>::result
                    >::result>::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SB
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0100011, 0b000, Funct7, Decoder> {
    using mem = Write<uint8_t, Mem,
                    ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::s_imm, 11>::result,
                    uint8_t(ReadRegister<Reg, Decoder::rs2>::result & 0xFF)
                >::result;
    using reg = Reg;

    const static bool done = false;
    const static bool update_pc = true;
};

// SH
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0100011, 0b001, Funct7, Decoder> {
    using mem = Write<uint16_t, Mem,
                    ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::s_imm, 11>::result,
                    uint16_t(ReadRegister<Reg, Decoder::rs2>::result & 0xFFFF)
                >::result;
    using reg = Reg;

    const static bool done = false;
    const static bool update_pc = true;
};

// SW
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0100011, 0b010, Funct7, Decoder> {
    using mem = Write<uint32_t, Mem,
                    ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::s_imm, 11>::result,
                    uint32_t(ReadRegister<Reg, Decoder::rs2>::result & 0xFFFFFFFF)
                >::result;
    using reg = Reg;

    const static bool done = false;
    const static bool update_pc = true;
};

// ADDI
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0010011, 0b000, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::i_imm, 11>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SLTI
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0010011, 0b010, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    (int64_t(ReadRegister<Reg, Decoder::rs1>::result) < int64_t(SignExtend<Decoder::i_imm, 11>::result))
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SLTIU
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0010011, 0b011, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    (ReadRegister<Reg, Decoder::rs1>::result < SignExtend<Decoder::i_imm, 11>::result)
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// XORI
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0010011, 0b100, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    ReadRegister<Reg, Decoder::rs1>::result ^ SignExtend<Decoder::i_imm, 11>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// ORI
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0010011, 0b110, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    ReadRegister<Reg, Decoder::rs1>::result | SignExtend<Decoder::i_imm, 11>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// ANDI
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0010011, 0b111, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    ReadRegister<Reg, Decoder::rs1>::result & SignExtend<Decoder::i_imm, 11>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SLLI
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0010011, 0b001, 0b0000000, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    ReadRegister<Reg, Decoder::rs1>::result << Decoder::i_imm
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SRLI
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0010011, 0b101, 0b0000000, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    (ReadRegister<Reg, Decoder::rs1>::result >> Decoder::i_imm)
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SRAI
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0010011, 0b101, 0b0100000, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    (int64_t(ReadRegister<Reg, Decoder::rs1>::result) >> int64_t(Decoder::i_imm & 0x1F))
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

#endif
