#ifndef _TEMPLATERISC_RISCV_EXECUTOR_HPP
#define _TEMPLATERISC_RISCV_EXECUTOR_HPP

#include "riscv/instr.hpp"

template <typename Mem, typename Reg>
struct FinalState {
    using mem = Mem;
    using regs = Reg;
};

template <typename Mem, typename Reg, bool done = false>
struct Executor;

template <typename Mem, typename Reg>
struct Executor<Mem, Reg, false> {
    using next_instr = ExecuteInstr<Mem, Reg>;

    using result = Executor<
                        typename next_instr::mem,
                        typename next_instr::reg,
                        next_instr::done
                    >::result;
};

template <typename Mem, typename Reg>
struct Executor<Mem, Reg, true> {
    using result = FinalState<Mem, Reg>;
};

#endif
