#pragma once

namespace drvut {
namespace internal {

namespace std {
template <class T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const { return value; }
    constexpr value_type operator()() const { return value; }
};

template <bool B>
using bool_constant = integral_constant<bool, B>;

using true_type  = bool_constant<true>;
using false_type = bool_constant<false>;

template <class T, class U>
struct is_same : std::false_type {};

template <class T>
struct is_same<T, T> : std::true_type {};

template <class T, class U>
inline constexpr bool is_same_v = is_same<T, U>::value;

template<bool B, class T, class F>
struct conditional { using type = T; };
template<class T, class F>
struct conditional<false, T, F> { using type = F; };
template< bool B, class T, class F >
using conditional_t = typename conditional<B,T,F>::type;

template <class...>
struct conjunction : std::true_type {};
template <class B1>
struct conjunction<B1> : B1 {};
template <class B1, class... Bn>
struct conjunction<B1, Bn...>
    : conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};
template <class... B>
inline constexpr bool conjunction_v = conjunction<B...>::value;

namespace detail {
template <class T>
struct type_identity { using type = T; }; // or use std::type_identity (since C++20)
 
template <class T>
auto try_add_lvalue_reference(int) -> type_identity<T&>;
template <class T>
auto try_add_lvalue_reference(...) -> type_identity<T>;
 
template <class T>
auto try_add_rvalue_reference(int) -> type_identity<T&&>;
template <class T>
auto try_add_rvalue_reference(...) -> type_identity<T>;
}

template <class T>
struct add_lvalue_reference : decltype(detail::try_add_lvalue_reference<T>(0)) {};
template <class T>
struct add_rvalue_reference : decltype(detail::try_add_rvalue_reference<T>(0)) {};

template <class T, class... Args>
struct is_nothrow_constructible : bool_constant<__is_nothrow_constructible(T, Args...)> {};
template <class T, class... Args>
inline constexpr bool is_nothrow_constructible_v = is_nothrow_constructible<T, Args>::value;

template <class To, class From>
struct is_nothrow_assignable : bool_constant<__is_nothrow_assignable(To, From)> {};
template <class To, class From>
inline constexpr bool is_nothrow_assignable_v = is_nothrow_assignable<To, From>::value;

template <class T>
struct is_nothrow_move_constructible : is_nothrow_constructible<T, typename add_rvalue_reference<T>::type> {};
}

}
}