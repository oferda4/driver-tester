#pragma once

#include "List.h"

namespace drvut {
namespace internal {

namespace impl {
template <typename T>
Node<T>* findLast(Node<T>* node);
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

template <typename T>
Node<T>::Node(T value) : value(std::move(value)) {
    // Left blank intentionally
}

template <typename T>
Node<T>* List<T>::head() {
    return m_head;
}

template <typename T>
const Node<T>* List<T>::head() const {
    return m_head;
}

template <typename T>
void List<T>::push_back(T obj) {
    auto newNode = new Node<T>(std::move(obj));
    if (m_head) {
        auto* last = impl::findLast(m_head);
        last->next = newNode;
    } else {
        m_head = newNode;
    }
}

template <typename T>
size_t List<T>::size() const {
    size_t count = 0;
    for (auto* node = head(); node; node = node->next) {
        count++;
    }
    return count;
}

template <typename Key, typename ListType, typename Func>
    requires(Comparator<typename ListType::Type, Key, Func>)
typename ListType::Type* ListUtils::find(ListType& list, const typename Key& key, Func func) {
    return const_cast<ListType::Type*>(
        ListUtils::find(static_cast<const ListType&>(list), key, func));
}

template <typename Key, typename ListType, typename Func>
    requires(Comparator<typename ListType::Type, Key, Func>)
const typename ListType::Type* ListUtils::find(const ListType& list, const typename Key& key,
                                               Func func) {
    for (auto* node = list.head(); node; node = node->next) {
        if (func(node->value, key)) {
            return &node->value;
        }
    }
    return nullptr;
}

template <typename T>
Node<T>* impl::findLast(Node<T>* node) {
    Node<T>* curr = node;
    while (curr->next) {
        curr = curr->next;
    }
    return curr;
}

}
}