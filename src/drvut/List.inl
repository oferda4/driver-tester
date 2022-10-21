#pragma once

#include "List.h"

namespace drvut {
namespace internal {

namespace detail {
template<typename T>
Node<T> findLast(Node<T>& node);
}

template <typename T>
List<T>::~List() {
    Node<T>* curr = m_head;
    while (curr) {
        auto next = curr->next;
        delete curr;
        curr = next;
    }
}

template<typename T>
Node<T>::Node(T value) : value(std::move(value)) {
    // Left blank intentionally
}

template <typename T>
Node<T>* List<T>::head() {
    return m_head;
}

template<typename T>
void List<T>::insert(T obj) {
    auto newNode = new T(std::move(obj));
    if (!m_head) {
        m_head = newNode;
    } else {
        auto last = findLast(m_head);
        last.next = newNode;
    }
}

template<typename T>
size_t List<T>::size() {
    size_t count = 0;
    for (auto* node = head(); node; node = node->next) {
        count++;
    }
    return count;
}

template <typename T>
template <typename Key, Comparator<T, Key> Func>
T* List<T>::find(const T& key, Func func) {
    return const_cast<T*>(static_cast<const List<T>*>(this)->find(key, func));
}

template <typename T>
template <typename Key, Comparator<T, Key> Func>
const T* List<T>::find(const T& key, Func func) const {
    for (auto* node = head(); node; node = node->next) {
        if (func(node->value, key)) {
            return &node->value;
        }
    }
    return nullptr;
}

template <typename T>
Node<T> detail::findLast(Node<T>& node) {
    Node<T>& curr = node;
    while (curr.next()) {
        curr = *curr.next();
    }
    return curr;
}

}
}