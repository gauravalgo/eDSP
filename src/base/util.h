//
// Created by Mohammed Boujemaoui on 08/10/2017.
//

#ifndef EDSP_UTIL_H
#define EDSP_UTIL_H

#include "config.h"
#include "types.h"

#include <type_traits>

E_BEGING_NAMESPACE

    template <typename T>
    constexpr int compare(const T& x, const T& y) {
        static_assert(std::is_scalar<T>::value, "Only scalar values are supported");
        return (x > y) - (x < y);
    }

    template <typename T>
    constexpr int sign(const T& x) {
        static_assert(std::is_scalar<T>::value, "Only scalar values are supported");
        return x > 0 ? 1 : 0;
    }

    template <typename T>
    constexpr int size(const T* array) {
        return (array == E_NULLPTR) ? 0 : (sizeof(array) / sizeof(T));
    }

    template <template <typename T> class Container,  typename T>
    inline void set(const Container& array, const T& value) {
        std::memset(array.begin(), array.end(), value);
    }

    template <typename T>
    constexpr bool isNaN(const T& x) {
        static_assert(std::is_scalar<T>::value, "Only scalar values are supported");
        return (x) != (x);
    }

    template <typename T>
    inline void swap(T& x, T& y) {
        const T tmp = x;
        x = y;
        y = tmp;
    }

E_END_NAMESPCE

#endif //EDSP_UTIL_H
