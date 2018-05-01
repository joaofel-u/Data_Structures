/// Copyright [2018] <João Fellipe Uller>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
/// Classe Fila Encadeada
class LinkedQueue {
 public:
    LinkedQueue();

    ~LinkedQueue();
    /// limpar
    void clear();
    /// enfileirar
    void enqueue(const T& data);
    /// desenfileirar
    T dequeue();
    /// primeiro dado
    T& front() const;
    /// último dado
    T& back() const;
    /// fila vazia
    bool empty() const;
    /// tamanho
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

    Node* head{nullptr};  // nodo-cabeça
    Node* tail{nullptr};  // nodo-fim
    std::size_t size_{0u};  // tamanho
};

}  /// namespace structures

#endif

template <typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    /// Empty constructor
}

template <typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template <typename T>
void structures::LinkedQueue<T>::clear() {
    Node *aux = head;
    for (unsigned int i = 0; i < size_; i++) {
        Node *next = aux->next();
        delete aux;
        aux = next;
    }
    size_ = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node *node = new Node(data);
    if (empty()) {
        head = node;
    } else {
        tail->next(node);
    }
    tail = node;
    size_++;
}

template <typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty())
        throw std::out_of_range("Empty queue");

    T data = head->data();
    head = head->next();
    size_--;
    return data;
}

template <typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty())
        throw std::out_of_range("Empty queue");

    return head->data();
}

template <typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty())
        throw std::out_of_range("Empty queue");

    return tail->data();
}

template <typename T>
bool structures::LinkedQueue<T>::empty() const {
    return size_ == 0;
}

template <typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}
