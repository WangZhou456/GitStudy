#include <iostream>
#include <vector>

using namespace std;

template<typename T>
typedef struct BinomialHeapNode{
    int key;
    int degree;
    Node<T>* left_child;
    Node<T>* sibling;
    Node<T>* father;
} Node;

template<tyoename T>
typedef struct BinomialTree {
    Node* tree_head;
    BinomialTree* next;
    BinomialTree* former;
} Tree; 

template<typename T>
class BinomialHeap {
  public:
    BinomialHeap(const vector<Node<T>>& list) {
        MakeHeap(list);
    }
    BinomialHeap(){}
    BinomialHeap(Node<T>* node) {
        Insert(node);
    }
    ~BinomialHeap() {
        while(tree_list_ != nullptr){
            DeleteNode(tree_list_.tree_head);
            tree_list_ = tree_list_->next;
        }
    }
    void MakeHeap(const vector<Node<T>>& list);
    void Insert(const Node<T>* node);
    void ExtraMaximum();
    Node<T>* Maximum();
    void AdjustKey(Node<T>* node, const T& key);
    
    void Union(BinomialHeap<T>& heap);
    void DeleteNode(Node* node) noexcept {
        if(node->left_child != nullptr)
            DeleteNode(node->left_child);
        if(node->right_child != nullptr)
            DeleteNode(node->right_child);
        delete node;
    }   
  private:
    BinomialTree<T>* tree_list_;//二项树链表
    void Merge(BinomialHeap<T>&);//l与r相邻
    void Link(Tree<T>* subject, Tree<T>* brach);//从入参开始反复连接
}