/// COPYRIGHT 2018 João Fellipe Uller
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>
#include <stdexcept>

#define DEFAULT_SIZE 10u

namespace structures {

template<typename T>
/// Classe que define uma pilha baseada em vetor
class ArrayStack {
 public:
    /// Construtores/Destrutores
    ArrayStack();

    explicit ArrayStack(std::size_t max);

    ~ArrayStack();

    /// empilha
    void push(const T& data);

    /// desempilha
    T pop();

    /// retorna o elemento do topo
    T& top();

    /// limpa
    void clear();

    /// tamanho da pilha
    std::size_t size();

    /// tamanho maximo da pilha
    std::size_t max_size();

    /// vazia
    bool empty();

    /// cheia
    bool full();

 private:
    T* contents;
    int top_;
    std::size_t max_size_;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[DEFAULT_SIZE];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete[] contents;
}

template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full())
        throw std::out_of_range("Full stack!");
    else
        contents[++top_] = data;
}

template<typename T>
T structures::ArrayStack<T>::pop() {
    if (empty())
        throw std::out_of_range("Empty stack!");
    else
        return contents[top_--];
}

template<typename T>
T& structures::ArrayStack<T>::top() {
    if (empty())
        throw std::out_of_range("Empty stack!");
    else
        return contents[top_];
}

template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    return top_ + 1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayStack<T>::empty() {
    return top_ == -1;
}

template<typename T>
bool structures::ArrayStack<T>::full() {
    return top_ == (max_size_ - 1);
}
