#ifndef _TEMPLATERISC_RISCV_LIST_HPP
#define _TEMPLATERISC_RISCV_LIST_HPP

#include <cstddef>
#include <utility>

template <typename T, typename Next, T Value>
struct List {
    using type = T;
    using next = Next;
    const static T value = Value;
    const static size_t size = next::size + 1;
};

template <typename T, T Value>
struct List<T, void, Value> {
    using type = T;
    using next = void;
    const static T value = Value;
    const static size_t size = 1;
};

template <typename T, size_t N>
struct MakeList;

template <typename T>
struct MakeList<T, 0> {
    using result = void;
};

template <typename T, size_t N>
struct MakeList {
    const static T def_value = T();
    using result = List<T, typename MakeList<T, N-1>::result, def_value>;
};

template <typename List, size_t index>
struct Get {
    const static auto result = Get<typename List::next, index - 1>::result;
};

template <typename List>
struct Get<List, 0> {
    const static auto result = List::value;
};

template <typename L, size_t Ind, typename L::type Value>
struct Set {
    using result = List<typename L::type,
                        typename Set<typename L::next, Ind-1, Value>::result,
                        L::value>;
};

template <typename L, typename L::type Value>
struct Set<L, 0, Value> {
    using result = List<typename L::type, typename L::next, Value>;
};

#endif
