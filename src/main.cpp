#include "riscv/executor.hpp"

#include <iostream>
#include <bitset>
#include <typeinfo>
#include <cxxabi.h>

using empty_memory = MakeMemory<32>::result;
using memory_t1 = Write<uint32_t, empty_memory, 0,  0b0000000'00001'00011'000'00001'0000011>::result;
using memory_t2 = Write<uint32_t, memory_t1, 10, 0x12348687>::result;
using memory = memory_t2;

using empty_registers = MakeRegisters<0>::result;
using registers_t1 = WriteRegister<empty_registers, 3, 9>::result;
using registers = registers_t1;

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
        uint64_t reg = Get<Mem, Ind-1>::result;

        std::cout << reg << "\t" << std::hex << reg << "\t" << std::bitset<64>(reg) << std::dec << std::endl;
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