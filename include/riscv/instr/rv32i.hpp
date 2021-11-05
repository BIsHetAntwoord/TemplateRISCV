#ifndef _TEMPLATERISC_RISCV_INSTR_RV32I_HPP
#define _TEMPLATERISC_RISCV_INSTR_RV32I_HPP

#include "riscv/instr/base.hpp"

template <typename Mem, typename Reg, uint32_t Funct3, uint32_t Funct7, typename Decoder>
struct Instr<Mem, Reg, 0b0110111, Funct3, Funct7, Decoder> {
    using mem = Mem;
    using reg = WriteRegister<Reg, Decoder::rd, Decoder::u_imm>::result;

    const static bool done = false;
    const static bool update_pc = true;
};

#endif
