/// Copyright [2018] <João Fellipe Uller>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>
#include <stdexcept>  // C++ Exceptions

#define DEFAULT_SIZE 10u

namespace structures {

template<typename T>
/// Classe que implementa uma fila baseada em vetor
class ArrayQueue {
 public:
    ArrayQueue();

    /// Construtor parametrizado
    explicit ArrayQueue(std::size_t max);

    ~ArrayQueue();

    /// Adiciona um elemento da fila
    void enqueue(const T& data);

    /// Remove um elemento da fila
    T dequeue();

    /// Retorna o ultimo elemento da fila
    T& back();

    /// Limpa a fila
    void clear();

    /// Retorna o tamanho atual da fila
    std::size_t size();

    /// Retorna o tamanho maximo da fila
    std::size_t max_size();

    /// Retorna se a fila está vazia
    bool empty();

    /// Retorna se a fila está cheia
    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    /// Faz a fila "andar" quando algum elemento sai
    void moveElements();
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    contents = new T[DEFAULT_SIZE];
    size_ = 0;
    max_size_ = DEFAULT_SIZE;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    contents = new T[max];
    size_ = 0;
    max_size_ = max;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full())
        throw std::out_of_range("Full queue!");

    contents[size_++] = data;
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty())
        throw std::out_of_range("Empty queue!");

    T aux = contents[0];
    size_--;
    moveElements();
    return aux;
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty())
        throw std::out_of_range("Empty queue!");

    return contents[size_ - 1];
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    size_ = 0;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return size_ == 0;
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    return size_ == max_size_;
}

template<typename T>
void structures::ArrayQueue<T>::moveElements() {
    for (unsigned int i = 0; i < size_; i++) {
        contents[i] = contents[i+1];
    }
}
