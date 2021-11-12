#ifndef _TEMPLATERISC_RISCV_UTILS_SIGNEXTEND_HPP
#define _TEMPLATERISC_RISCV_UTILS_SIGNEXTEND_HPP

template <uint64_t Const, uint64_t Bit, bool enabled>
struct SignExtendInternal;

template <uint64_t Const, uint64_t Bit>
struct SignExtendInternal<Const, Bit, true> {
    const static uint64_t mask = uint64_t(-1) ^ ((uint64_t(1) << Bit) - 1);
    const static uint64_t result = Const | mask;
};

template <uint64_t Const, uint64_t Bit>
struct SignExtendInternal<Const, Bit, false> {
    const static uint64_t result = Const;
};

template <uint64_t Const, uint64_t Bit>
struct SignExtend {
    const static uint64_t result = SignExtendInternal<Const, Bit, (Const >> Bit) & 1>::result;
};

#endif
