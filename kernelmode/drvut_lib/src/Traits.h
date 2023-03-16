#pragma once

namespace drvut::internal {

namespace std {

template <typename...>
using void_t = void;

template <class T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const {
        return value;
    }
    constexpr value_type operator()() const {
        return value;
    }
};

template <bool B>
using bool_constant = integral_constant<bool, B>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

template <class T, class U>
struct is_same : std::false_type {};

template <class T>
struct is_same<T, T> : std::true_type {};

template <class T, class U>
inline constexpr bool is_same_v = is_same<T, U>::value;

template <bool B, class T = void>
struct enable_if {};
template <class T>
struct enable_if<true, T> {
    typedef T type;
};
template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <bool B, class T, class F>
struct conditional {
    using type = T;
};
template <class T, class F>
struct conditional<false, T, F> {
    using type = F;
};
template <bool B, class T, class F>
using conditional_t = typename conditional<B, T, F>::type;

template <class...>
struct conjunction : std::true_type {};
template <class B1>
struct conjunction<B1> : B1 {};
template <class B1, class... Bn>
struct conjunction<B1, Bn...> : conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};
template <class... B>
inline constexpr bool conjunction_v = conjunction<B...>::value;

template <class...>
struct disjunction : std::false_type {};
template <class B1>
struct disjunction<B1> : B1 {};
template <class B1, class... Bn>
struct disjunction<B1, Bn...> : std::conditional_t<bool(B1::value), B1, disjunction<Bn...>> {};

template <class... B>
inline constexpr bool disjunction_v = disjunction<B...>::value;

namespace detail {
template <class T>
struct type_identity {
    using type = T;
}; // or use std::type_identity (since C++20)

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
struct is_nothrow_move_constructible :
    is_nothrow_constructible<T, typename add_rvalue_reference<T>::type> {};

template <class T>
struct remove_reference {
    using type = T;
};
template <class T>
struct remove_reference<T&> {
    using type = T;
};
template <class T>
struct remove_reference<T&&> {
    using type = T;
};
template <class T>
using remove_reference_t = typename remove_reference<T>::type;

namespace detail {
template <typename Base>
true_type is_base_of_test(volatile const Base*) noexcept;
template <typename Base>
false_type is_base_of_test(volatile const void*) noexcept;
template <typename Base, typename Derived>
using pre_is_base_of = decltype(is_base_of_test<Base>(declval<Derived*>()));
template <typename Base, typename Derived, typename = void>
struct pre_is_base_of2 : public true_type {};
template <typename Base, typename Derived>
struct pre_is_base_of2<Base, Derived, std::void_t<pre_is_base_of<Base, Derived>>> :
    public pre_is_base_of<Base, Derived> {};
}

template <typename Base, typename Derived>
struct is_base_of : public detail::pre_is_base_of2<Base, Derived> {};
template <class Base, class Derived>
inline constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;

template <class T, class = void>
struct is_default_constructible : std::false_type {};
template <class T>
struct is_default_constructible<T, std::void_t<decltype(T())>> : std::true_type {};

template <class T>
struct is_void : std::is_same<void, T> {};

template <class _From, class _To>
struct is_convertible : bool_constant<__is_convertible_to(_From, _To)> {};

template <class From, class To>
inline constexpr bool is_convertible_v = is_convertible<From, To>::value;

template <class T>
struct is_floating_point :
    integral_constant<bool,
                      disjunction_v<is_same<float, T>,
                                    is_same<double, T>,
                                    is_same<long double, T>>> {};

template <class T>
struct is_integral :
    bool_constant <requires(T t, T* p, void (*f)(T)) {
    reinterpret_cast<T>(t);
    f(0);
    p + t;
}> {};

template <class T>
struct is_arithmetic :
    integral_constant<bool, is_integral<T>::value || is_floating_point<T>::value> {};

namespace detail {
template <typename T>
struct is_unsigned : integral_constant<bool, static_cast<T>(0) < static_cast<T>(-1)> {};
}

template <typename T>
struct is_unsigned : detail::is_unsigned<T>::type {};
template <class T>
inline constexpr bool is_unsigned_v = is_unsigned<T>::value;

}

template <class T, template <class...> class Base>
struct is_specialization : std::false_type {};
template <template <class...> class Base, class... Args>
struct is_specialization<Base<Args...>, Base> : std::true_type {};

}