#ifndef _TEMPLATERISC_RISCV_INSTR_HPP
#define _TEMPLATERISC_RISCV_INSTR_HPP

#include "riscv/memory.hpp"
#include "riscv/registers.hpp"
#include "riscv/instr/rv32i.hpp"

template <bool Update, typename Regs, uint64_t Delta>
struct UpdatePC;

template<typename Regs, uint64_t Delta>
struct UpdatePC<true, Regs, Delta> {
    using result = typename RegisterAddPC<Regs, Delta>::result;
};

template <typename Regs, uint64_t Delta>
struct UpdatePC<false, Regs, Delta> {
    using result = Regs;
};

template <uint32_t Opcode>
struct Decoder {
    const static uint32_t opcode = Opcode & 0x7F;
    const static uint32_t rd = (Opcode >> 7) & 0x1F;
    const static uint32_t funct3 = (Opcode >> 12) & 0x07;
    const static uint32_t rs1 = (Opcode >> 15) & 0x1F;
    const static uint32_t rs2 = (Opcode >> 20) & 0x1F;
    const static uint32_t funct7 = (Opcode >> 25) & 0x7F;

    const static uint32_t i_imm = rs2 | (funct7 << 5);
    const static uint32_t s_imm = rd | (funct7 << 5);
    const static uint32_t b_imm = (rd & 0x1E) | ((funct7 & 0x3F) << 5) | ((rd & 0x01) << 11) | ((funct7 & 0x40) << (12 - 6));
    const static uint32_t u_imm = Opcode & 0xFFFFF000;
    const static uint32_t j_imm = (funct3 << 12) | (rs1 << 15) | ((rs2 & 0x01) << 11) | (rs2 & 0x1E) | ((funct7 & 0x3F) << 5) | ((funct7 & 0x40) << 20);
};

template <typename Mem, typename Reg>
struct ExecuteInstr {
    const static uint32_t opcode = Read<uint32_t, Mem, Reg::pc>::result;
    using decoded = Decoder<opcode>;
    using instr = Instr<Mem, Reg, decoded::opcode, decoded::funct3, decoded::funct7, decoded>;

    using mem = typename instr::mem;
    using reg = typename UpdatePC<!instr::done && instr::update_pc, typename instr::reg, 4>::result;
    const static bool done = instr::done;
};

#endif
