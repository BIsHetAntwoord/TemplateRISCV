#ifndef _TEMPLATERISC_RISCV_INSTR_RV64I_HPP
#define _TEMPLATERISC_RISCV_INSTR_RV64I_HPP

#include "riscv/instr/base.hpp"
#include "riscv/utils/signextend.hpp"

// LWU
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0000011, 0b110, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    Read<uint32_t, Mem,
                            ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::i_imm, 11>::result
                    >::result>::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// LD
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0000011, 0b011, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    Read<uint64_t, Mem,
                            ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::i_imm, 11>::result
                    >::result>::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SD
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0100011, 0b011, Funct7, Decoder> {
    using mem = Write<uint64_t, Mem,
                    ReadRegister<Reg, Decoder::rs1>::result + SignExtend<Decoder::s_imm, 11>::result,
                    uint64_t(ReadRegister<Reg, Decoder::rs2>::result)
                >::result;
    using reg = Reg;

    const static bool done = false;
    const static bool update_pc = true;
};

// ADDIW
template <typename Mem, typename Reg, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0011011, 0b000, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        uint32_t(ReadRegister<Reg, Decoder::rs1>::result)
                        + uint32_t(SignExtend<Decoder::i_imm, 11>::result),
                        31>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SLLIW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0011011, 0b001, 0b0000000, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        uint32_t(ReadRegister<Reg, Decoder::rs1>::result)
                        << uint32_t(SignExtend<Decoder::i_imm, 11>::result),
                        31>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SRLIW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0011011, 0b101, 0b0000000, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        (uint32_t(ReadRegister<Reg, Decoder::rs1>::result)
                        >> uint32_t(SignExtend<Decoder::i_imm, 11>::result)),
                        31>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SRAIW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0011011, 0b101, 0b0100000, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        (int32_t(ReadRegister<Reg, Decoder::rs1>::result)
                        >> int32_t(SignExtend<Decoder::i_imm, 11>::result)),
                        31>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// ADDW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0111011, 0b000, 0b0000000, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        (uint32_t(ReadRegister<Reg, Decoder::rs1>::result)
                        + uint32_t(ReadRegister<Reg, Decoder::rs2>::result)),
                        31>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SUBW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0111011, 0b000, 0b0100000, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        (uint32_t(ReadRegister<Reg, Decoder::rs1>::result)
                        - uint32_t(ReadRegister<Reg, Decoder::rs2>::result)),
                        31>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SLLW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0111011, 0b001, 0b0000000, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        (uint32_t(ReadRegister<Reg, Decoder::rs1>::result)
                        << (uint32_t(ReadRegister<Reg, Decoder::rs2>::result) & 0x1Fu)),
                        31>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SRLW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0111011, 0b101, 0b0000000, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        (uint32_t(ReadRegister<Reg, Decoder::rs1>::result)
                        >> (uint32_t(ReadRegister<Reg, Decoder::rs2>::result) & 0x1Fu)),
                        31>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// SRAW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0111011, 0b001, 0b0100000, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    SignExtend<
                        (int32_t(ReadRegister<Reg, Decoder::rs1>::result)
                        >> (int32_t(ReadRegister<Reg, Decoder::rs2>::result) & 0x1F)),
                        31>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

#endif
