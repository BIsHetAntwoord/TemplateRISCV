#ifndef _TEMPLATERISC_RISCV_INSTR_BASE_HPP
#define _TEMPLATERISC_RISCV_INSTR_BASE_HPP

template <typename Mem, typename Reg, uint32_t Opcode, uint32_t Funct3, uint32_t Funct7, typename Decoder>
struct Instr {};

// Temporary "halt execution" instruction
template <typename Mem, typename Reg, typename Decoder>
struct Instr<Mem, Reg, 0, 0, 0, Decoder> {
    using mem = Mem;
    using reg = Reg;

    const static bool done = true;
    const static bool update_pc = false;
};

#endif
