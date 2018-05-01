/// Copyright [2018] <João Fellipe Uller>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
/// Classe Lista Circular Simples
class CircularList {
 public:
    CircularList();

    ~CircularList();

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

   /// acessar em um indice (com checagem de limites)
   T& at(std::size_t index);

   /// versão const do acesso ao indice
   const T& at(std::size_t index) const;

   /// retirar da posição
   T pop(std::size_t index);

   /// retirar do fim
   T pop_back();

   /// retirar do início
   T pop_front();

   /// remover dado específico
   void remove(const T& data);

   /// lista vazia
   bool empty() const;

   /// lista contém determinado dado?
   bool contains(const T& data) const;

   /// posição de um item na lista
   std::size_t find(const T& data) const;

   /// tamanho da lista
   std::size_t size() const;

 private:
     class Node {  // Elemento
       public:
          Node() {
            data_ = 0;
          }

          explicit Node(const T& data) {
              data_ = &data;
          }

          Node(const T& data, Node* next) {
              data_ = data;
              next_ = next;
          }

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
          auto it = sentinel;
          for (unsigned int i = 0; i < size(); i++)
              it = it->next();

          return it;
      }

      Node *sentinel;  // Nodo vazio no inicio da lista
      std::size_t size_{0u};
  };

}  // namespace structures

#endif

template <typename T>
structures::CircularList<T>::CircularList() {
	sentinel = new Node();
}

template <typename T>
structures::CircularList<T>::~CircularList() {
	clear();
	delete sentinel;
}

template <typename T>
void structures::CircularList<T>::clear() {
	Node *actual = sentinel->next();
	for (unsigned int i = 0; i < size_; i++) {
		Node *aux = actual->next();
		delete actual;
		actual = aux;
	}

	size_ = 0;
	sentinel->next(nullptr);
}

template <typename T>
void structures::CircularList<T>::push_back(const T& data) {
	insert(data, size_);
}

template <typename T>
void structures::CircularList<T>::push_front(const T& data) {
	insert(data, 0);
}

template <typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
	if ((index < 0) || (index > size_))
		throw std::out_of_range("Invalid index");

	if (index == 0) {
		sentinel->next(new Node(data, sentinel->next()));
	} else if (index == size_) {
		end()->next(new Node(data, sentinel));
	} else {
		Node *actual = sentinel;
		for (unsigned int i = 0; i < index; i++)
			actual = actual->next();

		actual->next(new Node(data, actual->next()));
	}

	size_++;
}

template <typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
	unsigned int i = 0;
	if (size_ != 0) {
		Node *actual = sentinel;
		while ((i < size_) && (data > actual->next()->data())) {
			i++;
			actual = actual->next();
		}
	}

	insert(data, i);
}

template <typename T>
T& structures::CircularList<T>::at(std::size_t index) {
	if ((index < 0) || (index >= size_))
		throw std::out_of_range("Invalid index");

	Node *node = sentinel->next();
	for (unsigned int i = 0; i < index; i++)
		node = node->next();

	return node->data();
}

template <typename T>
const T& structures::CircularList<T>::at(std::size_t index) const {
	if ((index < 0) || (index >= size_))
		throw std::out_of_range("Invalid index");

	Node *node = sentinel->next();
	for (unsigned int i = 0; i < index; i++)
		node = node->next();

	return node->data();
}

template <typename T>
T structures::CircularList<T>::pop(std::size_t index) {
	if (empty())
		throw std::out_of_range("Empty list");
	if ((index < 0) || (index >= size_))
		throw std::out_of_range("Invalid index");

	Node *actual = sentinel;
	for (unsigned int i = 0; i < index; i++)
		actual = actual->next();

	Node *node = actual->next();
	T data = node->data();
	actual->next(node->next());
	delete node;

	size_--;
	return data;
}

template <typename T>
T structures::CircularList<T>::pop_back() {
	return pop(size_ - 1);
}

template <typename T>
T structures::CircularList<T>::pop_front() {
	return pop(0);
}

template <typename T>
void structures::CircularList<T>::remove(const T& data) {
	if (contains(data))
		pop(find(data));
}

template <typename T>
bool structures::CircularList<T>::empty() const {
	return size_ == 0;
}

template <typename T>
bool structures::CircularList<T>::contains(const T& data) const {
	Node *actual = sentinel->next();
	for (unsigned int i = 0; i < size_; i++) {
		if (data == actual->data())
			return true;

		actual = actual->next();
	}

	return false;
}

template <typename T>
std::size_t structures::CircularList<T>::find(const T& data) const {
	if (!contains(data)) {
		return size_;
	} else {
		Node *actual = sentinel->next();
		int i = 0;
		while (data != actual->data()) {
			actual = actual->next();
			i++;
		}

		return i;
	}
}

template <typename T>
std::size_t structures::CircularList<T>::size() const {
	return size_;
}
