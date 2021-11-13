#include "riscv/executor.hpp"

#include <iostream>
#include <iomanip>
#include <bitset>
#include <typeinfo>
#include <cxxabi.h>

using empty_memory = MakeMemory<32>::result;
using memory_t1 = Write<uint32_t, empty_memory, 0,  0b0000000'00011'00001'101'00100'0010011>::result;
using memory_instr_end = memory_t1;
using memory_const_t1 = Write<uint32_t, memory_instr_end, 16, 0x12345678>::result;
using memory_const_t2 = Write<uint32_t, memory_const_t1, 20, 0x9ABCDEF0>::result;
using memory = memory_const_t2;

using empty_registers = MakeRegisters<0>::result;
using regs_temp_1 = WriteRegister<empty_registers, 1, 0x8000000000000000>::result;
using registers = regs_temp_1;

using executor = Executor<memory, registers>;
using result = executor::result;

template <typename Mem, size_t Ind>
struct DumpMemory {
    static void dump() {
        DumpMemory<Mem, Ind-1>::dump();
        std::cout << std::hex << std::uppercase << std::setfill('0') << std::setw(2)
            << (int)Read<uint8_t, Mem, Ind-1>::result << " " << std::resetiosflags(std::ios_base::basefield);

        if constexpr(Ind % 16 == 0) {
            std::cout << std::endl;
        }
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