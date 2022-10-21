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

template <typename Func, typename T, typename Key>
concept Comparator = requires(const T& obj, const Key& key, Func func) {
    { func(obj, key) } -> std::same_as<bool>;
};

template<typename T>
class List final {
public:
    List() = default;
    ~List();

    Node<T>* head();
    void insert(T obj);
    size_t size();
    
    template <typename Key, Comparator<T, Key> Func>
    T* find(const T& key, Func func);
    template <typename Key, Comparator<T, Key> Func>
    const T* find(const T& key, Func func) const;

private:
    Node<T>* m_head = nullptr;
};

}
}

#include "List.inl"
