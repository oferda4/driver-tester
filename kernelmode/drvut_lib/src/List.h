#pragma once

#include "Defs.h"

#include "Concepts.h"

namespace drvut {
namespace internal {

template<typename T>
struct Node {
    Node(T value);

    T value;
    Node<T>* next = nullptr;
};

template <typename T, typename Key, typename Func>
concept Comparator = requires(const T& obj, Key key, Func func) {
    { func(obj, key) } -> std::same_as<bool>;
};

template<typename T>
class List final {
public:
    List() = default;
    ~List();

    using Type = T;

    Node<T>* head();
    const Node<T>* head() const;
    void insert(T obj);
    size_t size() const;

private:
    Node<T>* m_head = nullptr;
};

class ListUtils {
public:
    ListUtils() = delete;

    template <typename Key, typename ListType, typename Func>
        requires(Comparator<typename ListType::Type, Key, Func>)
    static typename ListType::Type* find(ListType& list, const typename Key& key, Func func);
    template <typename Key, typename ListType, typename Func>
        requires(Comparator<typename ListType::Type, Key, Func>)
    static const typename ListType::Type* find(const ListType& list, const Key& key, Func func);
};

}
}

#include "List.inl"
