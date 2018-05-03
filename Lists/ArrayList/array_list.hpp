/// Copyright [2018] <João Fellipe Uller>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions

#define DEFAULT_MAX 10u

namespace structures {

template<typename T>

/// Implementa uma lista baseada em vetor
class ArrayList {
 public:
    /// Construtores/Destrutor
    ArrayList();

    explicit ArrayList(std::size_t max_size);

    ~ArrayList();

    /// Limpa a lista logicamente
    void clear();

    /// Insere um elemento no fim da lista
    void push_back(const T& data);

    /// Insere um elemento no inicio da lista
    void push_front(const T& data);

    /// Insere um elemento
    void insert(const T& data, std::size_t index);

    /// Insere um elemento em ordem
    void insert_sorted(const T& data);

    /// Retorna um elemento
    T pop(std::size_t index);

    /// Retorna o ultimo elemento
    T pop_back();

    /// Retorna o primeiro elemento
    T pop_front();

    /// Remove um elemento
    void remove(const T& data);

    /// Testa se a lista esta cheia
    bool full() const;

    /// Testa se a lista esta vazia
    bool empty() const;

    /// Verifica se um elemento existe na lista
    bool contains(const T& data) const;

    /// Retorna o indice de dado elemento na lista (-1 se nao existir)
    std::size_t find(const T& data) const;

    /// Retorna o tamanho da lista
    std::size_t size() const;

    /// Retorna o tamanho maximo da lista
    std::size_t max_size() const;

    /// Retorna o elemento em determinado indice
    T& at(std::size_t index);

    /// Sobrecarga do operador []
    T& operator[](std::size_t index);

    /// Retorna o elemento em determinado indice
    const T& at(std::size_t index) const;

    /// Sobrecarga de operador
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
};

}  // namespace structures
#endif

template <typename T>
structures::ArrayList<T>::ArrayList() {
    contents = new T[DEFAULT_MAX];
    size_ = 0;
    max_size_ = DEFAULT_MAX;
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    contents = new T[max_size];
    size_ = 0;
    max_size_ = max_size;
}

template <typename T>
structures::ArrayList<T>::~ArrayList() {
    delete[] contents;
}

template <typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template <typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    insert(data, size_);
}

template <typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    insert(data, 0);
}

template <typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full())
        throw std::out_of_range("Full list!");
    if (index >= max_size_)
        throw std::out_of_range("Invalid index!");

    if (index < size_)
        for (unsigned int i = size_; i > index; i--)
            contents[i] = contents[i-1];

    contents[index] = data;
    size_++;
}

template <typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full())
        throw std::out_of_range("Full list!");

    unsigned int i = 0;
    while ((i < size_) && (data >= contents[i]))
        i++;

    insert(data, i);
}

template <typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty() || (index >= size_))
        throw std::out_of_range("Invalid index!");

    T data = contents[index];
    for (unsigned int i = index; i < size_ - 1; i++)
        contents[i] = contents[i+1];
    size_--;
    return data;
}

template <typename T>
T structures::ArrayList<T>::pop_back() {
    return pop(size_ - 1);
}

template <typename T>
T structures::ArrayList<T>::pop_front() {
    return pop(0);
}

template <typename T>
void structures::ArrayList<T>::remove(const T& data) {
    pop(find(data));
}

template <typename T>
bool structures::ArrayList<T>::full() const {
    return size_ == max_size_;
}

template <typename T>
bool structures::ArrayList<T>::empty() const {
    return size_ == 0;
}

template <typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (unsigned int i = 0; i < size_; i++) {
        if (contents[i] == data)
            return true;
    }
    return false;
}

template <typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    unsigned int i = 0;
    while ((i < size_) && (contents[i] != data)) {
        i++;
    }

    return i;
}

template <typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template <typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template <typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("Invalid index!");

    return contents[index];
}

template <typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("Invalid index!");

    return contents[index];
}

template <typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index >= size_)
        throw std::out_of_range("Invalid index!");

    return contents[index];
}

template <typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    if (index >= max_size_)
        throw std::out_of_range("Invalid index!");

    return contents[index];
}
