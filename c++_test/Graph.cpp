#include"Graph.h"
#include<map>
#include<queue>
#include <iostream>
#include <algorithm>
bool operator<(const EdgeListNode& l, const EdgeListNode& r) {
    return l.weight < r.weight;
}
bool operator>(const EdgeListNode& l, const EdgeListNode& r) {
    return  operator<(r,l);
}
EdgeListNode operator-(EdgeListNode l, const EdgeListNode& r) {
    l.weight -= r.weight;
    return l;
}
template<typename ElementType> void Heap<ElementType>::MakeHeap(const vector<ElementType>& list)
{
    for(int i = 0; i < list.size(); ++i) {
        heap_origin.push_back(i);
        origin_heap.push_back(i);
    }
        
    heap = list;
    for(int i = heap.size()-1;i>=0;--i){
        if(i>heap.size()/2)
            continue;
        int j = i;    
        while((2*j+1 < heap.size()&&heap[j]<heap[2*j+1])||(2*j+2<heap.size()&&heap[2*j]<heap[2*j]))
        {
            if(2*j+2>=heap.size()||heap[2*j+1]>heap[2*j+2]){
                swap(j,2*j+1);
                j = 2*j+1;
            }
            else{
                swap(j,2*j+2);
                j = 2*j+2;
            }
            
        }
    } 
    size = heap.size();
}


template<typename ElementType> void Heap<ElementType>::AdjustNodeUp(int i) {
    while(i != 0 && heap[i] > heap[(i-1)/2]) {
        swap(i, (i-1)/2);
        i = (i-1)/2;
    }
}
template<typename ElementType> void Heap<ElementType>::AdjustNodeDown(int i) {
    while(i*2+2<heap.size()&&(heap[i]<heap[i*2+1]||heap[i]<heap[i*2+2])){
        if(heap[i*2+1]>heap[i*2+2]){
            swap(2*i+1, i);
            i = 2*i+1;
        }
        else{
            swap(i,2*i+2);
            i = 2*i+2;
        }
    }
    if(2*i+1 < heap.size() && heap[2*i+1] > heap[i]) {
            swap(i,2*i+1);
    }
}


int Graph::DFS(int s){
    dfs_marked[s] = 1;
    for(EdgeListNode *former = graph.vertext_list[s].first_adj;former!=nullptr;former=former->next){
        if(dfs_marked[former->adjId]==0){
            dfs_from[former->adjId] = s;
            DFS(former->adjId);
        }
    }
    return 0;
}
int Graph::BFS(int s){
    bfs_not_search.clear();
    bfs_not_search.push_front(s);
    for(int i=0;i<Maxinum;i++){
        bfs_marked[i] = 0;
        bfs_from[i] = 0;
    }
    while(bfs_not_search.size()!=0){

        int s = bfs_not_search.back();
        bfs_not_search.pop_back();
        for(EdgeListNode* former = graph.vertext_list[s].first_adj;former !=nullptr;former = former->next){
            if(bfs_marked[former->adjId]==0){
                bfs_from[former->adjId] == s;
                bfs_marked[former->adjId] == 1;           
                bfs_not_search.push_front(former->adjId);
            }
        }
    
    }
   return 0; 
} 
void deleteNode(GraphAdjList& graph,int s){
    for(EdgeListNode* former = graph.vertext_list[s].first_adj;former!=nullptr;former=former->next){
        graph.vertext_list[former->adjId].in--;
    }
}
void Graph::Prime(int s) {
    vector<int> dis;
    vector<int> visited;
    vector<int> former;
    vector<EdgeListNode> list_node;
    for(int i = 0; i < graph.vertext_number; ++i) {
        list_node.push_back({i, INT32_MIN, nullptr});
        dis.push_back(INT32_MAX);
        visited.push_back(0);
        former.push_back(s);
    }
    list_node[s].weight = 0;//设置第一个目标点的距离为最近
    Heap<EdgeListNode> node_heap(list_node);
    vector<pair<int, int> > chosen_edg;
    EdgeListNode maximum{0, INT32_MIN, nullptr};
    EdgeListNode kMinNode{0, INT32_MIN, nullptr};
    node_heap.Maximum(maximum);
    while(node_heap.size > 0 && maximum > kMinNode) {
        chosen_edg.push_back(make_pair(former[maximum.adjId], maximum.adjId));
        node_heap.ExtraMaximum();
        visited[maximum.adjId] = 1;
        EdgeListNode* edg = graph.vertext_list[maximum.adjId].first_adj;
        while(edg != nullptr) {
            if(edg->weight < dis[edg->adjId] && visited[edg->adjId] != 1) {
                dis[edg->adjId] = edg->weight;
                former[edg->adjId] = maximum.adjId;
                edg->weight = -edg->weight;
                node_heap.AdjustNode(edg->adjId, *edg);               
            }
            edg =edg->next;
        }
        maximum = {0, INT32_MIN, nullptr};
        node_heap.Maximum(maximum);
    }
    for(int i = 0; i < chosen_edg.size(); ++i)
        cout << chosen_edg[i].first << "->" << chosen_edg[i].second << endl;
}
struct Edge {
    int from;
    int to;
    int weight;
};

void Graph::Kruskal(int s) {
    vector<Edge> sorted_edge;
    vector<int> former;
    vector<Edge> chosen_edge;
    for(int i = 0; i < graph.vertext_list.size(); ++i) {
        EdgeListNode* edge = graph.vertext_list[i].first_adj;
        while(edge != nullptr) {
            sorted_edge.push_back(Edge{i, edge->adjId, edge->weight});
            edge =edge->next;
        }
        former.push_back(-1);
    }
    std::sort(sorted_edge.begin(), sorted_edge.end(), [](const Edge& l, const Edge& r){
        return l.weight < r.weight;} );
    int count = 0;

    for(int i = 0; count < graph.vertext_number && i <graph.edge_number; ++i) {
        int j = sorted_edge[i].to;
        while(former[j] != -1 && former[j] != sorted_edge[i].from)
            j = former[j];
        if(former[j] == -1) {
            former[j] = sorted_edge[i].from;
            chosen_edge.push_back(sorted_edge[i]);
            ++count;
        }
    }
    for(int i = 0; i < chosen_edge.size(); ++i) {
        cout << chosen_edge[i].from << "->" << chosen_edge[i].to << "weight:" << chosen_edge[i].weight << endl;
    }
    
}
vector<int> Graph::TopSort(){
    GraphAdjList tmp = graph;
    vector<int>top_sort;
    int begin = 0;
    while(begin < tmp.vertext_number){
        for(int i =0;i<tmp.vertext_number;i++){
            if(tmp.vertext_list[i].in==0){
                top_sort.push_back(i);
                deleteNode(tmp,i);
                break;
            }
        }
        begin++;
    }
    return top_sort;
}
void test_reference(string& a) {
    cout << "test_reference: do nothing";
}
int main() {
    Graph g;
    for(int i = 0; i < 10; ++i) {
        g.addNode(i);
    }
    for(int i = 0; i < 8; ++i) {
        for(int j = 1; j < 3; ++j)
            g.addEdge(i,(i+j)%10,10-i);
    } 
    cout << "Kruskal:" << endl;
    g.Kruskal(0);
    cout << endl << "Prime:" << endl;
    g.Prime(0);
    cin.get();


}