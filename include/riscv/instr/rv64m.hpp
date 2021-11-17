#ifndef _TEMPLATERISC_RISCV_INSTR_RV64M_HPP
#define _TEMPLATERISC_RISCV_INSTR_RV64M_HPP

#include "riscv/instr/base.hpp"
#include "riscv/utils/signextend.hpp"

// MULW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0111011, 0b000, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    (int64_t)((int32_t)ReadRegister<Reg, Decoder::rs1>::result * (int32_t)ReadRegister<Reg, Decoder::rs2>::result)
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// DIVW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0111011, 0b100, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    uint32_t(ReadRegister<Reg, Decoder::rs2>::result) == 0
                        ? uint64_t(0xFFFFFFFFFFFFFFFFull)
                        : uint64_t(int64_t(
                            (int32_t)ReadRegister<Reg, Decoder::rs1>::result
                            / (int32_t)ReadRegister<Reg, Decoder::rs2>::result
                        ))
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// DIVUW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0111011, 0b101, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    uint32_t(ReadRegister<Reg, Decoder::rs2>::result) == 0
                        ? uint64_t(0xFFFFFFFFFFFFFFFFull)
                        : uint64_t(
                            (uint32_t)ReadRegister<Reg, Decoder::rs1>::result
                            / (uint32_t)ReadRegister<Reg, Decoder::rs2>::result
                        )
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// REMW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0111011, 0b110, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    uint32_t(ReadRegister<Reg, Decoder::rs2>::result) == 0
                        ? int64_t(int32_t(ReadRegister<Reg, Decoder::rs1>::result))
                        : uint64_t(int64_t(
                            (int32_t)ReadRegister<Reg, Decoder::rs1>::result
                            % (int32_t)ReadRegister<Reg, Decoder::rs2>::result
                        ))
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

// REMUW
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0b0111011, 0b111, 0b0000001, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd,
                    uint32_t(ReadRegister<Reg, Decoder::rs2>::result) == 0
                        ? uint32_t(ReadRegister<Reg, Decoder::rs1>::result)
                        : uint64_t(
                            (uint32_t)ReadRegister<Reg, Decoder::rs1>::result
                            % (uint32_t)ReadRegister<Reg, Decoder::rs2>::result
                        )
                >::result;

    const static bool done = false;
    const static bool update_pc = true;
};

#endif
