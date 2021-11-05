#ifndef _TEMPLATERISC_RISCV_REGISTERS_HPP
#define _TEMPLATERISC_RISCV_REGISTERS_HPP

#include "riscv/list.hpp"

template <uint64_t PC, typename Regs>
struct Registers {
    const static uint64_t pc = PC;
    using general = Regs;
};

template <uint64_t PC>
struct MakeRegisters {
    using result = Registers<PC, typename MakeList<uint64_t, 32>::result>;
};

template <typename Regs, uint32_t Regid, uint64_t Value>
struct WriteRegister {
    using result = Registers<Regs::pc, typename Set<typename Regs::general, Regid, Value>::result>;
};

template <typename Regs, uint32_t Regid>
struct ReadRegister {
    const static uint64_t result = Get<typename Regs::general, Regid>::result;
};

template <typename Regs, uint64_t Delta>
struct RegisterAddPC {
    using result = Registers<Regs::pc + Delta, typename Regs::general>;
};

#endif
