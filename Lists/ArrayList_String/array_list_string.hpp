//! Copyright [2018] <João Fellipe Uller>
#ifndef STRUCTURES_ARRAY_LIST_STRING_HPP
#define STRUCTURES_ARRAY_LIST_STRING_HPP

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>
#include "array_list.hpp"

namespace structures {

/// Implementa uma lista de strings baseada em vetor
class ArrayListString {
 public:
     ArrayListString();

     /// Construtor
     explicit ArrayListString(std::size_t max_size);

     ~ArrayListString();

     /// Limpa a lista e libera a memória ocupada
     void clear();

     /// Insere um elemento no final
     void push_back(const char *data);

     /// Insere um elemento no inicio
     void push_front(const char *data);

     /// Insere um elemento
     void insert(const char *data, std::size_t index);

     /// Insere um elemento ordenadamente
     void insert_sorted(const char *data);

     /// Retorna um elemento em determinado indice
     char *pop(std::size_t index);

     /// Retorna o elemento no fim da lista
     char *pop_back();

     /// Retorna o elemento no inicio da lista
     char *pop_front();

     /// Remove um elemento
     void remove(const char *data);

     /// Testa se a lista esta cheia
     bool full() const;

     /// Testa se a lista esta vazia
     bool empty() const;

     /// Verifica se dado elemento existe na lista
     bool contains(const char *data) const;

     /// Retorna o indice ocupado por data na lista (size_ se não existir)
     std::size_t find(const char *data) const;

     /// Retorna o tamanho da lista
     std::size_t size() const;

     /// Retorna o tamanho maximo da lista
     std::size_t max_size() const;

     /// Retorna o elemento em dado indice
     char *at(std::size_t index);

     /// Sobrecarga do operador []
     char *operator[](std::size_t index);

     /// Retona o elemento em dado indice
     const char *at(std::size_t index) const;

     /// Sobrecarga do operador []
     const char *operator[](std::size_t index) const;

 private:
    ArrayList<char *> *list;
};

}  // namespace structures

#endif

structures::ArrayListString::ArrayListString() {
    list = new ArrayList<char *>[DEFAULT_MAX];
}

structures::ArrayListString::ArrayListString(std::size_t max_size) {
    list = new ArrayList<char *>[max_size];
}

structures::ArrayListString::~ArrayListString() {
    clear();
    delete[] list;
}

void structures::ArrayListString::clear() {
    for (std::size_t i = 0; i < list->size(); i++)
        delete[] pop_back();

    list->clear();
}

void structures::ArrayListString::push_back(const char *data) {
    insert(data, list->size());
}

void structures::ArrayListString::push_front(const char *data) {
    insert(data, 0);
}

void structures::ArrayListString::insert(const char *data, std::size_t index) {
    if (full())
        throw std::out_of_range("Lista cheia!");

    int string_size = strlen(data) + 1;
    char* char_array = new char[string_size];
    snprintf(char_array, string_size, "%s", data);
    list->insert(char_array, index);
}

void structures::ArrayListString::insert_sorted(const char *data) {
    if (full())
        throw std::out_of_range("Lista cheia!");

    int i;
    int list_size = list->size();
    for (i = 0; i < list_size; i++) {
        int j = 0;
        while (data[j] == list[0][i][j])
            j++;

        if (data[j] < list[0][i][j])
            break;

    }

    insert(data, i);
}

char *structures::ArrayListString::pop(std::size_t index) {
    return list->pop(index);
}

char *structures::ArrayListString::pop_back() {
    return list->pop_back();
}

char *structures::ArrayListString::pop_front() {
    return list->pop_front();
}

void structures::ArrayListString::remove(const char *data) {
    if (contains(data))
        delete[] list->pop(find(data));
}

bool structures::ArrayListString::full() const {
    return list->full();
}

bool structures::ArrayListString::empty() const {
    return list->empty();
}

bool structures::ArrayListString::contains(const char *data) const {
    int list_size = list->size();
    for (int i = 0; i < list_size; i++) {
        if (strcmp(list->at(i), data) == 0)
            return true;
    }

    return false;
}

std::size_t structures::ArrayListString::find(const char *data) const {
    int i;
    int list_size = list->size();
    for (i = 0; i < list_size; i++) {
        if (strcmp(list->at(i), data) == 0)
            break;
    }
    
    return i;
}

std::size_t structures::ArrayListString::size() const {
    return list->size();
}

std::size_t structures::ArrayListString::max_size() const {
    return list->max_size();
}

char *structures::ArrayListString::at(std::size_t index) {
    return list->at(index);
}

char *structures::ArrayListString::operator[](std::size_t index) {
    return list->at(index);
}

const char *structures::ArrayListString::at(std::size_t index) const {
    return list->at(index);
}

const char *structures::ArrayListString::operator[](std::size_t index) const {
    return list->at(index);
}
