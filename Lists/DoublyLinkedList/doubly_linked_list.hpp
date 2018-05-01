/// Copyright [2018] <João Fellipe Uller>
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
/// Classe Lista Duplamente Encadeada
class DoublyLinkedList {
 public:
    DoublyLinkedList();

    ~DoublyLinkedList();

    /// Limpar
    void clear();

    /// insere no fim
    void push_back(const T& data);

    /// insere no início
    void push_front(const T& data);

    /// insere na posição
    void insert(const T& data, std::size_t index);

    /// insere em ordem
    void insert_sorted(const T& data);

    /// retira da posição
    T pop(std::size_t index);

    /// retira do fim
    T pop_back();

    /// retira do início
    T pop_front();

    /// retira específico
    void remove(const T& data);

    /// lista vazia
    bool empty() const;

    /// contém
    bool contains(const T& data) const;

    /// acesso a um elemento (checando limites)
    T& at(std::size_t index);

    /// getter constante a um elemento
    const T& at(std::size_t index) const;

    /// posição de um dado
    std::size_t find(const T& data) const;

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

        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            prev_ = prev;
            next_ = next;
        }

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

      private:
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

}  /// namespace structures

#endif

template <typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    /// Empty constructor
}

template <typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
void structures::DoublyLinkedList<T>::clear() {
    Node *aux = head;
    for (unsigned int i = 0; i < size_; i++) {
        Node *next = aux->next();
        delete aux;
        aux = next;
    }

    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template <typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

template <typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    insert(data, 0);
}

template <typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if ((index > size_) || (index < 0))
        throw std::out_of_range("Invalid index");

    Node *new_node;
    if (empty()) {
        new_node = new Node(data);
        head = new_node;
        tail = new_node;
    } else {
        Node *aux;  /// Nodo no indice a ser trabalhado
        if (index == size_) {
            new_node = new Node(data, tail, nullptr);
            tail->next(new_node);
            tail = new_node;
        } else if (index == 0) {
            new_node = new Node(data, head);
            head->prev(new_node);
            head = new_node;
        } else {
            if (index <= (size_ / 2)) {
                aux = head;
                for (unsigned int i = 0; i < index; i++)
                    aux = aux->next();
            } else {
                aux = tail;
                for (unsigned int i = 0; i < (size_ - index - 1); i++)
                    aux = aux->prev();
            }
            new_node = new Node(data, aux->prev(), aux);
            aux->prev()->next(new_node);
            aux->prev(new_node);
        }
    }

    size_++;
}

template <typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    unsigned int i = 0;
    if (!empty()) {
        Node *actual = head;
        while ((i < size_) && (data > actual->data())) {
            i++;
            actual = actual->next();
        }
    }

    insert(data, i);
}

template <typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Empty list");

    if ((index >= size_) || (index < 0))
        throw std::out_of_range("Invalid index");

    Node *node;
    if (index < (size_ / 2)) {
        node = head;
        for (unsigned int i = 0; i < index; i++)
            node = node->next();
    } else {
        node = tail;
        for (unsigned int i = (size_ - 1); i > index; i--)
            node = node->prev();
    }

    T node_data = node->data();

    /// Acerto dos ponteiros
    if (size_ > 1) {
        if (index == 0) {
            head = node->next();
            head->prev(nullptr);
        } else if (index == size_ - 1) {
            tail = node->prev();
            tail->next(nullptr);
        } else {
            Node *node_prev = node->prev();
            node->prev()->next(node->next());
            node->next()->prev(node_prev);
        }
    } else {
        head = nullptr;
        tail = nullptr;
    }

    /// Remoção do node
    delete node;
    size_--;
    return node_data;
}

template <typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    return pop(size_ - 1);
}

template <typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    return pop(0);
}

template <typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    if (contains(data))
        pop(find(data));
}

template <typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return size_ == 0;
}

template <typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    if (empty())
        throw std::out_of_range("Empty list");

    Node *actual = head;
    for (unsigned int i = 0; i < size_; i++) {
        if (actual->data() == data)
            return true;

        actual = actual->next();
    }
    return false;
}

template <typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    if (empty())
        throw std::out_of_range("Empty list");
    if ((index >= size_) || (index < 0))
        throw std::out_of_range("Invalid index");

    Node *actual;
    if (index < (size_ / 2)) {
        actual = head;
        for (unsigned int i = 0; i < index; i++)
            actual = actual->next();
    } else {
        actual = tail;
        for (unsigned int i = (size_ - 1); i > index; i--)
            actual = actual->prev();
    }

    return actual->data();
}

template <typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
    if (empty())
        throw std::out_of_range("Empty list");
    if ((index >= size_) || (index < 0))
        throw std::out_of_range("Invalid index");

    Node *actual;
    if (index < (size_ / 2)) {
        actual = head;
        for (int i = 0; i < index; i++)
            actual = actual->next();
    } else {
        actual = tail;
        for (int i = (size_ - 1); i > index; i--)
            actual = actual->prev();
    }

    return actual->data();
}

template <typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    if (empty())
        throw std::out_of_range("Empty list");

    unsigned int i = 0;
    Node *actual = head;
    while ((i < size_) && (actual->data() != data)) {
        actual = actual->next();
        i++;
    }

    return i;
}

template <typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}
