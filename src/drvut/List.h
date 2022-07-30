#pragma once

#include "Defs.h"

namespace drvut {
namespace internal {

template<typename T>
struct Node {
    Node(T value);

    T value;
    Node<T>* next = nullptr;
};

template<typename T>
class List final {
public:
    List() = default;
    ~List();

    void insert(T obj);

private:
    Node<T>* m_head = nullptr;
};

}
}

#include "List.inl"
