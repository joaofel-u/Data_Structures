/// Copyright [2018] <João Fellipe Uller>
#ifndef STRUCTURES_LINKED_STACK_HPP
#define STRUCTURES_LINKED_STACK_HPP

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
/// Classe Pilha Encadeada
class LinkedStack {
 public:
    /// Construtor/Destrutor
    LinkedStack();

    ~LinkedStack();

    /// Limpa lista
    void clear();

    /// Empilha elemento
    void push(const T& data);

    /// Desempilha elemento
    T pop();

    /// Retorna o topo da pilha
    T& top() const;

    /// Testa pilha vazia
    bool empty() const;

    /// Tamanho da pilha
    std::size_t size() const;

 private:
    class Node {
     public:
        explicit Node(const T& data) {
            data_ = data;
        }
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        T& data() {  // getter: info
            return data_;
        }
        const T& data() const {  // getter-constante: info
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }
        const Node* next() const {  // getter-constante: próximo
            return next_;
        }

        void next(Node* next) {  // setter: próximo
            next_ = next;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_;  // nodo-topo
    std::size_t size_{0};  // tamanho
};

}  // namespace structures

#endif

template <typename T>
structures::LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
}

template <typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template <typename T>
void structures::LinkedStack<T>::clear() {
    Node *aux = top_;
    for (unsigned int i = 0; i < size_; i++) {
        Node *next = aux->next();
        delete aux;
        aux = next;
    }
    size_ = 0;
}

template <typename T>
void structures::LinkedStack<T>::push(const T& data) {
    top_ = new Node(data, top_);
    size_++;
}

template <typename T>
T structures::LinkedStack<T>::pop() {
    if (empty())
        throw std::out_of_range("Empty list");

    Node *aux = top_;
    T node_data = aux->data();
    top_ = aux->next();
    delete aux;
    size_--;
    if (size_ == 0)
        top_ = nullptr;
    return node_data;
}

template <typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty())
        throw std::out_of_range("Empty list");

    return top_->data();
}

template <typename T>
bool structures::LinkedStack<T>::empty() const {
    return size_ == 0;
}

template <typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
