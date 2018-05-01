/// Copyright [2018] <João Fellipe Uller>
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
/// Lista duplamente encadeada
class DoublyCircularList {
  public:
    DoublyCircularList();

    ~DoublyCircularList();

    /// limpar
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
        Node() {
            data_ = 0;
        }
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

        Node* head;  // sentinela
        std::size_t size_{0u};
    };

}  // namespace structures

#endif

template <typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    head = new Node();
}

template <typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
    delete head;
}

template <typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        Node *actual = head->next();
        head->next(actual->next());
        delete actual;
        size_--;
    }

    head->next(nullptr);
    head->prev(nullptr);
}

template <typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    insert(data, size_);
}

template <typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    insert(data, 0);
}

template <typename T>
void structures::DoublyCircularList<T>::insert(const T& data, std::size_t index) {
    if ((index < 0) || (index > size_))
    	throw std::out_of_range("Invalid index");

    Node *new_node;
    if (size_ == 0) {
        new_node = new Node(data, head, head);
        head->prev(new_node);
        head->next(new_node);
    } else {
        Node *actual = head;
        if (index < (size_ / 2)) {
            for (unsigned int i = 0; i < index; i++) {
                actual = actual->next();
            }
        } else {
            for (unsigned int i = 0; i <= (size_ - index); i++) {
                actual = actual->prev();
            }
        }
        new_node = new Node(data, actual, actual->next());
        actual->next()->prev(new_node);
        actual->next(new_node);
    }

    size_++;
}

template <typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    unsigned int i = 0;
    if (size_ != 0) {
        Node *actual = head;
        while ((i < size_) && (data > actual->next()->data())) {
            i++;
            actual = actual->next();
        }
    }

    insert(data, i);
}

template <typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (empty())
    	throw std::out_of_range("Empty list");
    if ((index < 0) || (index >= size_))
    	throw std::out_of_range("Invalid index");

    Node *node = head;
    if (index < (size_ / 2)) {
        for (unsigned int i = 0; i <= index; i++)
            node = node->next();
    } else {
        for (unsigned int i = 0; i < (size_ - index); i++)
            node = node->prev();
    }

    /// Acerto dos ponteiros
    if (size_ > 1) {
        node->prev()->next(node->next());
        node->next()->prev(node->prev());
    } else {
        head->next(nullptr);
        head->prev(nullptr);
    }

    T data = node->data();
    delete node;
    size_--;
    return data;
}

template <typename T>
T structures::DoublyCircularList<T>::pop_back() {
    return pop(size_ - 1);
}

template <typename T>
T structures::DoublyCircularList<T>::pop_front() {
    return pop(0);
}

template <typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    if (contains(data))
    	pop(find(data));
}

template <typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return size_ == 0;
}

template <typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    Node *actual = head->next();
    for (unsigned int i = 0; i < size_; i++) {
        if (data == actual->data())
        	return true;

        actual = actual->next();
    }

    return false;
}

template <typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if ((index < 0) || (index >= size_))
    	throw std::out_of_range("Invalid index");

    Node *node = head;
    if (index < (size_ / 2)) {
        for (unsigned int i = 0; i <= index; i++) {
            node = node->next();
        }
    } else {
        for (unsigned int i = 0; i < (size_ - index); i++) {
            node = node->prev();
        }
    }

    return node->data();
}

template <typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    if ((index < 0) || (index >= size_))
    	throw std::out_of_range("Invalid index");

    Node *node = head;
    if (index < (size_ / 2)) {
        for (unsigned int i = 0; i <= index; i++) {
            node = node->next();
        }
    } else {
        for (unsigned int i = 0; i < (size_ - index); i++) {
            node = node->prev();
        }
    }

    return node->data();
}

template <typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    if (!contains(data)) {
        return size_;
    } else {
        Node *actual = head->next();
        int i = 0;
        while (data != actual->data()) {
            actual = actual->next();
            i++;
        }

        return i;
    }
}

template <typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}
