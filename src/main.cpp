#include "riscv/executor.hpp"

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

using empty_memory = MakeMemory<16>::result;
using memory = Write<uint32_t, empty_memory, 0, 0b1000000'00000'00000'001'00011'0110111>::result;
using empty_registers = MakeRegisters<0>::result;
using registers = WriteRegister<empty_registers, 1, 2>::result;

using executor = Executor<memory, registers>;
using result = executor::result;

template <typename Mem, size_t Ind>
struct DumpMemory {
    static void dump() {
        DumpMemory<Mem, Ind-1>::dump();
        std::cout << (int)Read<uint8_t, Mem, Ind-1>::result << std::endl;
    }
};

template <typename Mem>
struct DumpMemory<Mem, 0> {
    static void dump() {
    }
};

template <typename Mem, size_t Ind>
struct DumpRegisters {
    static void dump() {
        DumpRegisters<Mem, Ind-1>::dump();
        std::cout << Get<Mem, Ind-1>::result << std::endl;
    }
};

template <typename Mem>
struct DumpRegisters<Mem, 0> {
    static void dump() {
    }
};

int main() {
    using result_mem = result::mem;
    using result_regs = result::regs;

    int status = 0;
    char* name = abi::__cxa_demangle(typeid(result).name(), 0, 0, &status);
    std::cout << name << std::endl;
    free(name);

    DumpMemory<result_mem, result_mem::size>::dump();
    std::cout << std::endl;
    std::cout << "PC: " << result_regs::pc << std::endl;
    DumpRegisters<result_regs::general, result_regs::general::size>::dump();
    return 0;
}