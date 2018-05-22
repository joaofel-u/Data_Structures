/// Copyright [2018] <Joao Fellipe Uller>
#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <algorithm>
#include "array_list.hpp"

namespace structures {

template <typename T>
/// Implementa uma arvore binaria AVL
class AVLTree {
public:
    /// Destrutor
    ~AVLTree();

    /// Insere um dado na arvore
    void insert(const T& data);

    /// Remove um dado da arvore
    void remove(const T& data);

    /// Retorna se um dado especifico ja existe dentro da arvore
    bool contains(const T& data) const;

    /// Retorna se a arvore esta vazia
    bool empty() const;

    /// Retorna o numero de elementos da arvore
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
        std::size_t height_{0u};
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

            updateHeight();

            int fb_node = fb();
            int sqrd_fb = fb_node * fb_node;
            if (sqrd_fb > 1) {  // No' desbalanceado
                if (fb_node > 0) {
                    if (left_->fb() > 0)
                        left_ = simpleRight();
                    else
                        left_ = doubleRight();
                } else {
                    if (right_->fb() > 0)
                        right_ = simpleLeft();
                    else
                        right_ = doubleLeft();
                }
            }
        }

        bool remove(const T& data) {
            if ((data > data_) && (right_ != nullptr)) {
                if (!right_->remove(data)) {
                    delete right_;
                    right_ = nullptr;
                }
            } else if ((data < data_) && (left_ != nullptr)) {
                if (!left_->remove(data)) {
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

            updateHeight();
            int fb_node = fb();
            int sqrd_fb = fb_node * fb_node;
            while (sqrd_fb > 1) {  // No' desbalanceado
                if (fb_node > 0) {
                    if (left_->fb() > 0)
                        left_ = simpleRight();
                    else
                        left_ = doubleRight();
                } else {
                    if (right_->fb() > 0)
                        right_ = simpleLeft();
                    else
                        right_ = doubleLeft();
                }

                updateHeight();
                fb_node = fb();
                sqrd_fb = fb_node * fb_node;
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

        void updateHeight() {
            if ((left_ != nullptr) && (right_ != nullptr)) {
                height_ = max(left_->height_, right_->height_);
            } else if (left_ != nullptr) {
                height_ = left_->height_;
            } else if (right_ != nullptr) {
                height_ = right_->height_;
            } else {
                height_ = 0;
            }
        }

        Node* simpleLeft() {
            Node* aux = right_;
            aux->left_ = this;
            right_ = right_->left_;
            aux->updateHeight();
            aux->left_->updateHeight();
            aux->right_->updateHeight();
            return aux;
        }

        Node* simpleRight() {
            Node* aux = left_;
            aux->right_ = this;
            left_ = left_->right_;
            aux->updateHeight();
            aux->left_->updateHeight();
            aux->right_->updateHeight();
            return aux;
        }

        Node* doubleLeft() {
            right_ = right_->simpleRight();
            return simpleLeft();
        }

        Node* doubleRight() {
            left_ = left_->simpleLeft();
            return simpleRight();
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

        /// METODOS AUXILIARES
        /// Retorna o menor valor da subarvore
        T minimun() {
            if (left_ == nullptr)
                return data_;
            else
                return left_->minimun();
        }

        /// Retorna o maior entre dois inteiros
        int max(int data1, int data2) {
            if (data1 >= data2)
                return data1;
            else
                return data2;
        }

        /// Retorna o fator de balanceamento do no'
        int fb() {
            if ((left_ != nullptr) && (right_ != nullptr))
                return left_->height_ - right_->height_;
            else if (left_ != nullptr)
                return left_->height_;
            else if (right_ != nullptr)
                return 0 - right_->height_;
            else
                return 0;
        }
    };

    Node* root_{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

/// IMPLEMENTACAO DOS METODOS DE AVL_TREE

template <typename T>
structures::AVLTree<T>::~AVLTree() {
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
void structures::AVLTree<T>::insert(const T& data) {
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

        root_->updateHeight();

        int fb = root_->fb();
        int sqrd_fb = fb * fb;
        if (sqrd_fb > 1) {  // No' desbalanceado
            if (fb > 0) {
                if (root_->left_->fb() > 0)
                    root_ = root_->simpleRight();
                else
                    root_ = root_->doubleRight();
            } else {
                if (root_->right_->fb() > 0)
                    root_ = root_->simpleLeft();
                else
                    root_ = root_->doubleLeft();
            }
        }
    }

    size_++;
}

template <typename T>
void structures::AVLTree<T>::remove(const T& data) {
    if ((data > root_->data_) && (root_->right_ != nullptr)) {
        if (!root_->right_->remove(data)) {
            delete root_->right_;
            root_->right_ = nullptr;
        }
    } else if ((data < root_->data_) && (root_->left_ != nullptr)) {
        if (!root_->left_->remove(data)) {
            delete root_->left_;
            root_->left_ = nullptr;
        }
    } else {
        if ((root_->right_ != nullptr) && (root_->left_ != nullptr)) {
            root_->data_ = root_->right_->minimun();
            root_->right_->remove(root_->data_);
        } else if (root_->right_ != nullptr) {
            root_->data_ = root_->right_->data_;
            root_->right_->remove(root_->data_);
        } else if (root_->left_ != nullptr) {
            root_->data_ = root_->left_->data_;
            root_->left_->remove(root_->data_);
        } else {
            delete root_;
            root_ = nullptr;
        }
    }

    if (root_ != nullptr) {
        root_->updateHeight();

        int fb_node = root_->fb();
        int sqrd_fb = fb_node * fb_node;
        while (sqrd_fb > 1) {  // Raiz desbalanceada
            if (fb_node > 0) {
                if (root_->left_->fb() > 0)
                    root_->left_ = root_->simpleRight();
                else
                    root_->left_ = root_->doubleRight();
            } else {
                if (root_->right_->fb() > 0)
                    root_->right_ = root_->simpleLeft();
                else
                    root_->right_ = root_->doubleLeft();
            }

            root_->updateHeight();
            fb_node = root_->fb();
            sqrd_fb = fb_node * fb_node;
        }
    }

    size_--;
}

template <typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
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
bool structures::AVLTree<T>::empty() const {
    return size_ == 0;
}

template <typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    ArrayList<T> list{size_};

    list.push_back(root_->data_);
    if (root_->left_ != nullptr)
        root_->left_->pre_order(list);
    if (root_->right_ != nullptr)
        root_->right_->pre_order(list);

    return list;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    ArrayList<T> list{size_};

    if (root_->left_ != nullptr)
        root_->left_->in_order(list);
    list.push_back(root_->data_);
    if (root_->right_ != nullptr)
        root_->right_->in_order(list);

    return list;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    ArrayList<T> list{size_};

    if (root_->left_ != nullptr)
        root_->left_->post_order(list);
    if (root_->right_ != nullptr)
        root_->right_->post_order(list);
    list.push_back(root_->data_);

    return list;
}

#endif
