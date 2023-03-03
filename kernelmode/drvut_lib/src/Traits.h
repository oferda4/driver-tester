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
    typedef T type;
};
template <class T>
struct remove_reference<T&> {
    typedef T type;
};
template <class T>
struct remove_reference<T&&> {
    typedef T type;
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

namespace detail {
template <class T>
auto test_returnable(int) -> decltype(void(static_cast<T (*)()>(nullptr)), std::true_type{});
template <class>
auto test_returnable(...) -> std::false_type;

template <class From, class To>
auto test_implicitly_convertible(int) -> decltype(void(declval<void (&)(To)>()(declval<From>())), std::true_type{});
template <class, class>
auto test_implicitly_convertible(...) -> std::false_type;
}

template <class T, class = void>
struct is_default_constructible : std::false_type {};
template <class T>
struct is_default_constructible<T, std::void_t<decltype(T())>> : std::true_type {};

}
}