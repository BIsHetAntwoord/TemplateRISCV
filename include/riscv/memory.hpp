#ifndef _TEMPLATERISC_RISCV_MEMORY_HPP
#define _TEMPLATERISC_RISCV_MEMORY_HPP

#include "riscv/list.hpp"

#include <cstdint>

template <size_t S>
struct MakeMemory {
    using result = MakeList<uint8_t, S>::result;
};

template <typename Datatype, typename Memory, uint64_t Addr>
struct Read;

template <typename Memory, uint64_t Addr>
struct Read<uint8_t, Memory, Addr> {
    const static uint8_t result = Get<Memory, Addr>::result;
};

template <typename Memory, uint64_t Addr>
struct Read<uint16_t, Memory, Addr> {
    const static uint16_t result = static_cast<uint16_t>(Get<Memory, Addr>::result)
                                    | (static_cast<uint16_t>(Get<Memory, Addr+1>::result) << 8);
};

template <typename Memory, uint64_t Addr>
struct Read<uint32_t, Memory, Addr> {
    const static uint32_t result = static_cast<uint32_t>(Get<Memory, Addr>::result)
                                    | (static_cast<uint32_t>(Get<Memory, Addr+1>::result) << 8)
                                    | (static_cast<uint32_t>(Get<Memory, Addr+2>::result) << 16)
                                    | (static_cast<uint32_t>(Get<Memory, Addr+3>::result) << 24);
};

template <typename Memory, uint64_t Addr>
struct Read<uint64_t, Memory, Addr> {
    const static uint64_t result = static_cast<uint64_t>(Get<Memory, Addr>::result)
                                    | (static_cast<uint64_t>(Get<Memory, Addr+1>::result) << 8)
                                    | (static_cast<uint64_t>(Get<Memory, Addr+2>::result) << 16)
                                    | (static_cast<uint64_t>(Get<Memory, Addr+3>::result) << 24)
                                    | (static_cast<uint64_t>(Get<Memory, Addr+4>::result) << 32)
                                    | (static_cast<uint64_t>(Get<Memory, Addr+5>::result) << 40)
                                    | (static_cast<uint64_t>(Get<Memory, Addr+6>::result) << 48)
                                    | (static_cast<uint64_t>(Get<Memory, Addr+7>::result) << 56);
};

template <typename Datatype, typename Memory, uint64_t Addr, Datatype value>
struct Write;

template <typename Memory, uint64_t Addr, uint8_t Value>
struct Write<uint8_t, Memory, Addr, Value> {
    using result = Set<Memory, Addr, Value>::result;
};

template <typename Memory, uint64_t Addr, uint16_t Value>
struct Write<uint16_t, Memory, Addr, Value> {
    using result = typename Set<
                        typename Set<Memory, Addr, (uint8_t)(Value & 0xFF)>::result,
                        Addr + 1, (uint8_t)(Value >> 8)>::result;
};

template <typename Memory, uint64_t Addr, uint32_t Value>
struct Write<uint32_t, Memory, Addr, Value> {
    using result = typename Write<
                        uint16_t,
                        typename Write<uint16_t, Memory, Addr, Value & 0xFFFF>::result,
                        Addr + 2,
                        (Value >> 16)>::result;
};

template <typename Memory, uint64_t Addr, uint64_t Value>
struct Write<uint64_t, Memory, Addr, Value> {
    using result = typename Write<
                        uint32_t,
                        typename Write<uint32_t, Memory, Addr, Value & 0xFFFFFFFF>::result,
                        Addr + 4,
                        (Value >> 32ull)>::result;
};

#endif
