#pragma once

#include "drvut/Defs.h"

#include "drvut/internal/Concepts.h"

namespace drvut {
namespace internal {

template <typename T>
struct Node {
    Node(T value);

    T value;
    Node<T>* next = nullptr;
};

template <typename T, typename Key, typename Func>
concept Comparator = requires(const T& obj, Key key, Func func) {
                         { func(obj, key) } -> std::same_as<bool>;
                     };

template <typename T>
class List final {
public:
    using Type = T;

    List() = default;
    ~List();

    NOCOPY(List);
    NOMOVE(List);

    Node<T>* head();
    const Node<T>* head() const;
    void push_back(T obj);
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

#include "drvut/internal/List.inl"
