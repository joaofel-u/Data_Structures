/// Copyright [2018] <João Fellipe Uller>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
/// Classe Lista Encadeada
class LinkedList {
 public:
    /// Construtor / Destrutor
    LinkedList();

    ~LinkedList();

    /// limpar lista
    void clear();

    /// inserir no fim
    void push_back(const T& data);

    /// inserir no início
    void push_front(const T& data);

    /// inserir na posição
    void insert(const T& data, std::size_t index);

    /// inserir em ordem
    void insert_sorted(const T& data);

    /// acessar um elemento na posição index
    T& at(std::size_t index);

    /// retirar da posição
    T pop(std::size_t index);

    /// retirar do fim
    T pop_back();

    /// retirar do início
    T pop_front();

    /// remover específico
    void remove(const T& data);

    /// lista vazia
    bool empty() const;

    /// contém
    bool contains(const T& data) const;

    /// posição do dado
    std::size_t find(const T& data) const;

    /// tamanho da lista
    std::size_t size() const;

 private:
    class Node {  /// Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

template <typename T>
structures::LinkedList<T>::LinkedList() {
	// Empty constructor
}

template <typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void structures::LinkedList<T>::clear() {
    Node *actual = head;
    for (unsigned int i = 0; i < size_; i++) {
        Node *aux = actual->next();
        delete actual;
        actual = aux;
    }

    head = nullptr;
    size_ = 0;
}

template <typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

template <typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    insert(data, 0);
}

template <typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if ((index > size_) || (index < 0))
        throw std::out_of_range("Invalid index");

    if (empty() || (index == 0)) {
        head = new Node(data, head);
    } else {
        Node *actual = head;
        for (unsigned int i = 0; i < index - 1; i++)
            actual = actual->next();

        actual->next(new Node(data, actual->next()));  /// Insere o elemento em index
    }

    size_++;
}

template <typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    unsigned int i = 0;
    if (!empty()) {
        Node *actual = head;
        while ((i < size_) && (data > actual->data())) {
            actual = actual->next();
            i++;
        }
    }
    insert(data, i);
}

template <typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if ((index < 0) || (index >= size_))
        throw std::out_of_range("Invalid index");

    Node *actual = head;
    for (unsigned int i = 0; i < index; i++)
        actual = actual->next();

    return actual->data();
}

template <typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Empty list");
    if ((index >= size_) || (index < 0))
        throw std::out_of_range("Invalid index");

    Node *actual = head;
    Node *aux;
    if (index == 0) {
        aux = actual;
        head = actual->next();
    } else {
        for (unsigned int i = 0; i < index - 1; i++)
            actual = actual->next();

        aux = actual->next();
        actual->next(aux->next());  /// Seta como próximo, o elemento após index
    }

    T data = aux->data();
    delete aux;
    size_--;
    return data;
}

template <typename T>
T structures::LinkedList<T>::pop_back() {
    return pop(size_ - 1);
}

template <typename T>
T structures::LinkedList<T>::pop_front() {
    return pop(0);
}

template <typename T>
void structures::LinkedList<T>::remove(const T& data) {
    if (contains(data))
        pop(find(data));
}

template <typename T>
bool structures::LinkedList<T>::empty() const {
    return size_ == 0;
}

template <typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    Node *actual = head;
    for (unsigned int i = 0; i < size_; i++) {
        if (actual->data() == data)
            return true;

        actual = actual->next();
    }
    return false;
}

template <typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    Node *actual = head;
    unsigned int i = 0;
    while ((i < size_) && (actual->data() != data)) {
        actual = actual->next();
        i++;
    }

    return i;
}

template <typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}
