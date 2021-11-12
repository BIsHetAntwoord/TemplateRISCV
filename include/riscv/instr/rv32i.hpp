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
    //TODO
    using mem = Mem;
    using reg = Reg;

    const static bool done = true;
    const static bool update_pc = false;
};

// BNE
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100011, 0b001, Funct7, Decoder> {
    //TODO
    using mem = Mem;
    using reg = Reg;

    const static bool done = true;
    const static bool update_pc = false;
};

// BLT
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100011, 0b100, Funct7, Decoder> {
    //TODO
    using mem = Mem;
    using reg = Reg;

    const static bool done = true;
    const static bool update_pc = false;
};

// BGE
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100011, 0101, Funct7, Decoder> {
    //TODO
    using mem = Mem;
    using reg = Reg;

    const static bool done = true;
    const static bool update_pc = false;
};

// BLTU
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100011, 0b110, Funct7, Decoder> {
    //TODO
    using mem = Mem;
    using reg = Reg;

    const static bool done = true;
    const static bool update_pc = false;
};

// BGEU
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b1100011, 0b111, Funct7, Decoder> {
    //TODO
    using mem = Mem;
    using reg = Reg;

    const static bool done = true;
    const static bool update_pc = false;
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

#endif
