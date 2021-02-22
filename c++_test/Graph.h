#include<string>
#include<vector>
#include<deque>
#define Maxinum 40
using namespace std;
 struct EdgeListNode{
    int adjId;
    int weight;
    EdgeListNode *next;
};

 struct VertextListNode{
    int in;
    int data;
    EdgeListNode *first_adj;
};
 struct GraphAdjList{
    int vertext_number;
    int edge_number;
    vector<VertextListNode> vertext_list;
};

class Graph{
public:   
   Graph(){
       graph.vertext_number = 0;
   }
private:
    GraphAdjList graph;
    int dfs_marked[Maxinum];
    int dfs_from[Maxinum];
    deque<int> bfs_not_search;
    int bfs_marked[Maxinum];
    int bfs_from[Maxinum];

public:
    void addNode(int data){
        graph.vertext_number++;
        VertextListNode node = {0,data,nullptr};
        graph.vertext_list.push_back(node);
    };

    int addEdge(int from,int to,int weight){
        if(from>=graph.vertext_number||to>=graph.vertext_number)
            return -1;
        graph.edge_number++;
        EdgeListNode *node = (EdgeListNode *)malloc(sizeof(EdgeListNode));
        node->adjId = to;
        node->weight = weight;
        node->next = nullptr;
        graph.vertext_list[to].in++;
        
        if(graph.vertext_list[from].first_adj==nullptr)
            graph.vertext_list[from].first_adj = node;
        else
        {
            EdgeListNode *former =  graph.vertext_list[from].first_adj;
            while(former->next!=nullptr)
                former = former->next;
            former->next = node;
        }
        
    }
    int DFS(int s);
    int BFS(int s);
    void Prime(int s);
    EdgeListNode PrimeAddEEdge();
    void Kruskal(int s);
    vector<int> TopSort();
    vector<int> CriticalPath();
};
template<typename ElementType>
class Heap {
  public:
    Heap(vector<ElementType> raw_data) {
        MakeHeap(raw_data);
    }
    Heap() {}
    int AdjustNode(int i, ElementType new_node) {
        if(origin_heap[i] < 0 || origin_heap[i] >= size)
            return -1;
        bool decrease = true;
        if(heap[origin_heap[i]] < new_node)
             decrease = false;
        heap[origin_heap[i]] = new_node;
        if(decrease)
            AdjustNodeDown(origin_heap[i]);
        else
            AdjustNodeUp(origin_heap[i]);
        return 0;       
    }
    void MakeHeap(const vector<ElementType>& raw_data);
    int Maximum(ElementType& maximum) {
        if(size <= 0) 
            return -1;
        maximum = heap[0];
        return 0;
    }
    int ExtraMaximum() {
        if(size <= 0)
            return -1;
        swap(0, --size);
        heap.pop_back();
        AdjustNodeDown(0);
        return 0;
    }
    void Insert(const ElementType& node) {
        heap_origin.push_back(size);
        origin_heap.push_back(size);
        heap.push_back(node);     
        AdjustNodeUp(size++);
    }
    vector<ElementType> heap;
    vector<int> heap_origin;//heap的每个序列对应原先vector的序列
    vector<int> origin_heap;//vector原先的序列对应现在heap的序列
    void AdjustNodeDown(int i);
    void AdjustNodeUp(int i);
    void swap(int left, int right) {
        ElementType tmp = heap[right];
        heap[right] = heap[left];
        heap[left] = tmp;
        std::swap(heap_origin[left], heap_origin[right]);
        origin_heap[heap_origin[left]] = left;
        origin_heap[heap_origin[right]] = right;
        
    }

    int size;
};
