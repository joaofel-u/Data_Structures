/// Copyright [2018] <Joao Fellipe Uller>
#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP
#include "array_list.hpp"

namespace structures {

template <typename T>
/// Implementa uma arvore binaria
class BinaryTree {
 public:
    /// Destrutor da arvore
    ~BinaryTree();

    /// Insere um elemento na arvore
    void insert(const T& data);

    /// Remove um elemento da arvore
    void remove(const T& data);

    /// Verifica se um dado elemento existe na arvore
    bool contains(const T& data) const;

    /// Retorna se a arvore esta vazia
    bool empty() const;

    /// Retorna o tamanho da arvore
    std::size_t size() const;

    /// Retorna a arvore percorrida em pre-ordem
    ArrayList<T> pre_order() const;

    /// Retorna a arvore percorrida em ordem
    ArrayList<T> in_order() const;

    /// Retorna a arvore percorrida em pos-ordem
    ArrayList<T> post_order() const;

 private:
    struct Node {
        T data_;
        Node* left_{nullptr};
        Node* right_{nullptr};

        explicit Node(const T& data) {
            data_ = data;
        }

        void insert(const T& data) {
            if (data < data_) {
                if (left_ == nullptr)
                    left_ = new Node(data);
                else
                    left_->insert(data);
            } else {
                if (right_ == nullptr)
                    right_ = new Node(data);
                else
                    right_->insert(data);
            }
        }

        bool remove(const T& data) {
            if ((data > data_) && (right_ != nullptr)) {
                if (!right_->remove(data)) {
                    delete right_;
                    right_ = nullptr;
                }
            } else if ((data < data_) && (left_ != nullptr)) {
                if(!left_->remove(data)) {
                    delete left_;
                    left_ = nullptr;
                }
            } else {
                if ((right_ != nullptr) && (left_ != nullptr)) {
                    data_ = right_->minimun();
                    right_->remove(data_);
                } else if (right_ != nullptr) {
                    data_ = right_->data_;
                    right_->remove(data_);
                } else if (left_ != nullptr) {
                    data_ = left_->data_;
                    left_->remove(data_);
                } else {
                    return false;
                }
            }

            return true;
        }

        bool contains(const T& data) const {
            if (data == data_) {
                return true;
            } else {
                if ((data < data_) && (left_ != nullptr))
                    return left_->contains(data);
                else if (right_ != nullptr)
                    return right_->contains(data);
                else
                    return false;
            }
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data_);
            if (left_ != nullptr)
                left_->pre_order(v);
            if (right_ != nullptr)
                right_->pre_order(v);
        }

        void in_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->in_order(v);
            v.push_back(data_);
            if (right_ != nullptr)
                right_->in_order(v);
        }

        void post_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->post_order(v);
            if (right_ != nullptr)
                right_->post_order(v);
            v.push_back(data_);
        }

        T minimun() {
            if (left_ == nullptr)
                return data_;
            else
                return left_->minimun();
        }

    };  // struct Node

    Node* root_;
    std::size_t size_;
};

}  // namespace structures

// IMPLEMENTACAO

template <typename T>
structures::BinaryTree<T>::~BinaryTree() {
    while (size_ > 0) {
        Node *aux = root_;
        while ((aux->left_ != nullptr) || (aux->right_ != nullptr)) {
            if (aux->left_ != nullptr)
                aux = aux->left_;
            else
                aux = aux->right_;
        }

        aux->remove(aux->data_);
        size_--;
    }
}

template <typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (empty()) {
        root_ = new Node(data);
    } else if (!contains(data)) {
        if (data < root_->data_) {
            if (root_->left_ == nullptr)
                root_->left_ = new Node(data);
            else
                root_->left_->insert(data);
        } else {
            if (root_->right_ == nullptr)
                root_->right_ = new Node(data);
            else
                root_->right_->insert(data);
        }
    }
    size_++;
}

template <typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (contains(data)) {
        if (root_->data_ == data) {
            if (root_->left_ == nullptr) {
                if (root_->right_ == nullptr) {
                    delete root_;
                    root_ = nullptr;
                } else {
                    Node *aux = root_->right_;
                    delete root_;
                    root_ = aux;
                }
            } else {
                if (root_->right_ == nullptr) {
                    Node *aux = root_->left_;
                    delete root_;
                    root_ = aux;
                } else {
                    T temp = root_->right_->minimun();
                    remove(temp);
                    root_->data_ = temp;
                }
            }
        } else {
            if (data < root_->data_)
                root_->left_->remove(data);
            else
                root_->right_->remove(data);
        }

        size_--;
    }
}

template <typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (root_->data_ == data) {
        return true;
    } else {
        if ((data <= root_->data_) && (root_->left_ != nullptr))
            return root_->left_->contains(data);
        else if (root_->right_ != nullptr)
            return root_->right_->contains(data);
        else
            return false;
    }
}

template <typename T>
bool structures::BinaryTree<T>::empty() const {
    return size_ == 0;
}

template <typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template <typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    ArrayList<T> *list = new ArrayList<T>(size_);

    list->push_back(root_->data_);
    if (root_->left_ != nullptr)
        root_->left_->pre_order(*list);
    if (root_->right_ != nullptr)
        root_->right_->pre_order(*list);

    return *list;
}

template <typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    ArrayList<T> *list = new ArrayList<T>(size_);

    if (root_->left_ != nullptr)
        root_->left_->in_order(*list);
    list->push_back(root_->data_);
    if (root_->right_ != nullptr)
        root_->right_->in_order(*list);

    return *list;
}

template <typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    ArrayList<T>* list = new ArrayList<T>(size_);

    if (root_->left_ != nullptr)
        root_->left_->post_order(*list);
    if (root_->right_ != nullptr)
        root_->right_->post_order(*list);
    list->push_back(root_->data_);

    return *list;
}

#endif
