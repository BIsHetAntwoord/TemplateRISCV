#ifndef _TEMPLATERISC_RISCV_INSTR_RV32M_HPP
#define _TEMPLATERISC_RISCV_INSTR_RV32M_HPP

#include "riscv/instr/base.hpp"
#include "riscv/utils/signextend.hpp"

// MUL
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0110011, 0b000, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    ReadRegister<Reg, Decoder::rs1>::result * ReadRegister<Reg, Decoder::rs2>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// MULH
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0110011, 0b001, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    uint64_t(
                            ((__int128)(int64_t)ReadRegister<Reg, Decoder::rs1>::result
                            * (__int128)(int64_t)ReadRegister<Reg, Decoder::rs2>::result)
                            >> (__int128)64)
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// MULHSU
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0110011, 0b010, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    uint64_t(
                            ((__int128)(int64_t)ReadRegister<Reg, Decoder::rs1>::result
                            * (__int128)ReadRegister<Reg, Decoder::rs2>::result)
                            >> (__int128)64)
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// MULHU
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0110011, 0b011, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    uint64_t(
                            ((unsigned __int128)ReadRegister<Reg, Decoder::rs1>::result
                            * (unsigned __int128)ReadRegister<Reg, Decoder::rs2>::result)
                            >> (unsigned __int128)64)
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// DIV
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0110011, 0b100, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    ReadRegister<Reg, Decoder::rs2>::result == 0
                        ? uint64_t(0xFFFFFFFFFFFFFFFFull)
                        : uint64_t(
                            (int64_t)ReadRegister<Reg, Decoder::rs1>::result
                            / (int64_t)ReadRegister<Reg, Decoder::rs2>::result
                        )
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// DIVU
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0110011, 0b101, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    ReadRegister<Reg, Decoder::rs2>::result == 0
                        ? 0xFFFFFFFFFFFFFFFFull
                        : ReadRegister<Reg, Decoder::rs1>::result / ReadRegister<Reg, Decoder::rs2>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// REM
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0110011, 0b110, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    ReadRegister<Reg, Decoder::rs2>::result == 0
                        ? ReadRegister<Reg, Decoder::rs1>::result
                        : uint64_t(
                            (int64_t)ReadRegister<Reg, Decoder::rs1>::result
                            % (int64_t)ReadRegister<Reg, Decoder::rs2>::result
                        )
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// REMU
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0110011, 0b111, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    ReadRegister<Reg, Decoder::rs2>::result == 0
                        ? ReadRegister<Reg, Decoder::rs1>::result
                        : ReadRegister<Reg, Decoder::rs1>::result % ReadRegister<Reg, Decoder::rs2>::result
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

#endif
