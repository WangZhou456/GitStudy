#include "BinomialHeap.h"
#incldue "stdlib.h"
template<typename T> void BinomialHeap::MakeHeap(const vector<Node<T>*>& list) {
    for(int i = 0; i < list.size(); ++i) {
        Insert(list[i]);
    }
    
}

//TODO 应该作成可以插入任意度数的
template<typename T> void BinomialHeap::Insert(const Node<T>* node) {
    if(tree_list_.tree_head == nullptr) {
        tree_list_.tree_head = node;
    }
    else {
        BinomialHeap tmp(node);
        this->Union(tmp);
    }
}

template<typename T> void BinomialHeap::ExtraMaximum() {
    BinomialTree<T>* tree = tree_list_;
    BinomialTree<T>* max_tree = tree;
    while(tree != nullptr) {
        if(max_tree->tree_head->key < tree->tree_head->key) {
            max_tree = tree;
        }
        tree = tree->next;
    }
    Node<T>* child = max_tree->tree_head->left_child;
    max_tree->former->next = max_tree->next;
    max_tree->next->former = max_tree->former;
    while(child->sibling != nullptr ) {
        child->father = nullptr;
        --child->degree; 
        this->Insert(child);
    }  
}

//如果heap为空，会返回nullptr
template<T> Node<T>* BinomialHeap::Maximum() {
    BinomialTree<T>* tree = tree_list_;
    BinomialTree<T>* max_tree = tree;
    while(tree != nullptr) {
        if(max_tree->tree_head->key < tree->tree_head->key) {
            max_tree = tree;
        }
        tree = tree->next;
    }
    return max_tree;
}

// template<T> void AdjustKey(Node<T>* node, const T& key) {
    
//     if(node->key < key) {
//         while(node != nullptr) {
//             Node<T>* child = node->left_child;
//             Node<T>* former = node;
//             Node<T>* max_node = child;
            
//         }
//     }
    
// }

template<T> void BinomialHeap::Union(BinomialHeap<T> heap) {
    Merge(heap);
    Tree<T>* tree = tree_list_;
    Tree<T>* next_tree = tree_list->next;
    Tree<T>* pre_tree = nullptr;
    while(tree != nullptr && next_tree != nullptr) {
        // 连续两个度数不一样或者连续三个度数相同
        if(tree->tree_head->degree != next_tree->tree_head->degree || (next_tree->next != nullptr && next_tree->next->tree_head->degree = tree->tree_head->degree)) {
            pre_tree = tree;
            tree = next_tree;
            next_tree = next_tree->next;           
        }
        else if(tree->tree_head->key > next_tree->tree_head->key) { // 前一个比较大
            Link(tree, next_tree);
            tree->next = next_tree->next;
            delete next_tree;
        }
        else if(tree->tree_head->key < next_tree->tree_head->key) { // 后一个比较大
            Link(next_tree, tree);
            if(pre_tree == nullptr) {
                this->tree_list = next_tree;
            }
            else {
                pre_tree->next = next_tree;
            }
            delete(tree);
            tree = next_tree;
            next_tree = tree->next; 
        }
    }
}

template<T> void Merge(BinomialHeap<T>&) {

}
template<T> Link(Tree<T>* subject, Tree<T>* brach) {

}