// yek seri piyade sazi ha va function ha serfan baraye debug kardan implement shodan va dar code nahayi naghshi nadaran(mesle function traverse va show)
#include<iostream>
#include <algorithm>
using namespace std;
#define N 2 // N is maximum number of keys in one Node in B-Tree
const int INT_MAX = 100000;
int **makeAdj(int ** , int m ,int n); // makes adj matrix (graph)
void dijkstra(int ** ,int ** , int , int , int);
int minDistance(int * , bool *, int);
int **findPath(int * , int **, int **,int * , int , int , int); //find start point and finish point
int **makePath(int *  , int , int **,int ** ,int  ); // defines the path
inline int calcCount(int , int , int);
template<typename T>
struct Node{
    Node<T> *parent;
    T *keys;
    Node<T> **childs;
    int cnt;

    bool isLeaf(){return this->childs[0] == nullptr ? true : false;}
    Node():cnt(0) , parent(nullptr) {
        keys = new T [N];
        childs = new Node<T> *[N+1];
        for(int i = 0 ; i < N+1 ; i++)
            childs[i] = nullptr;
    }
    void insert(T );
    unsigned int search(T );
    void traverse() { 
    int i; 
    for (i = 0; i < cnt; i++) { 
        if (this->isLeaf() == false) 
            childs[i]->traverse(); 
        cout << " " << keys[i]; 
    } 
    if (isLeaf() == false) 
        childs[i]->traverse(); 
} 
    void show(){
        for(int i = 0 ; i < this->cnt ; i++)
            cout<<this->keys[i]<<" ";
        cout<<endl;
    }
    
};
template<typename T>
class BTree{
    private:
        Node<T> *root;
    public:
        BTree():root(nullptr) {}
        void insert(T );
        T minData();
        Node<T> *getRoot(){return root;}
    protected:
        Node<T> *dataLocation(T );
        void split(Node<T> *  );
};
int main(){
    BTree<int> b;
    int m , n ; cin >> m >> n;
    int **p = new int *[m];
    for(int i = 0; i < m; i++)
        p[i] = new int [n];
    for(int i = 0 ; i < m ; i++)
        for(int j = 0 ; j < n ; j++)
            cin>>p[i][j];;

    int **graphAdj = makeAdj(p , m , n);
    dijkstra(graphAdj , p , m*n , m , n);

    for(int i = 0 ; i < m ; i++){
        for(int j = 0 ; j < n ; j++){
            cout<<p[i][j]<<"  ";
        }
        cout<<endl;
    }
    return 0;
}
template<typename T>
unsigned int Node<T>::search(T data){
    for(int i = 0 ; i < this->cnt ; i++)
        if(this->keys[i] == data)
            return i;
}
template<typename T>
void Node<T>::insert(T data){
    for(int i = 0 ; i < this->cnt ; i++){
        if(data < this->keys[i]){
            for(int j = this->cnt - 1 ; j >= i ; j--)
                this->keys[j+1] = this->keys[j];
            this->keys[i] = data;
            this->cnt++;
            return;
        }
    }
    this->keys[cnt] = data;
    this->cnt++;
    return;
}
template<typename T>
Node<T> *BTree<T>::dataLocation(T k ){
    Node<T> *currentNode = root;
    if(currentNode){
        while(!currentNode->isLeaf()){
            bool flag(false);
            for(int i = 0 ; i < currentNode->cnt ; i++){
                if(k < currentNode->keys[i]){
                    flag =true;
                    currentNode = currentNode->childs[i];
                    break;
                }
            }
            if(!flag)
                currentNode = currentNode->childs[currentNode->cnt];
        }
        return currentNode;
    }
}
template<typename T>
void BTree<T>::insert(T k){
    if(root == nullptr){
        root = new Node<T>();
        root->keys[0] = k;
        root->cnt++;
        return;
    }
    else{
        Node<T> *m = dataLocation(k);
        if(m->cnt == 0){
            m->keys[0] = k;
            m->cnt++;
            return;
        }
        else if(m->cnt < N){
            m->insert(k);
        }
        else if(m->cnt == N){
            m->insert(k);
            split(m);
        }
    }
}
template<typename T>
void BTree<T>::split(Node<T> *n){
    Node<T> *newNodeL = new Node<T>();
    Node<T> *newNodeR = new Node<T>();
    Node<T> *parent = n == root ? new Node<T>() : n->parent;

    if(n == root)
        root = parent;
    T middle = n->keys[N/2];
    for(int i = 0 ; i < N/2 ; i++)
        newNodeL->insert(n->keys[i]);
    for(int i = N/2+1 ; i <= N ; i++)
        newNodeR->insert(n->keys[i]);
    newNodeR->parent = parent;
    newNodeL->parent = parent;
    if(!n->isLeaf()){
        for(int i = 0 ; i <= N/2 ; i++){
            newNodeL->childs[i] = n->childs[i];
            n->childs[i]->parent = newNodeL;
        }
        for(int i = N/2 + 1 ; i <= N+1 ; i++){
            newNodeR->childs[i - N/2 - 1] = n->childs[i];
            n->childs[i]->parent = newNodeR;
        }
    }
 
    parent->insert(middle);

    unsigned int ind = parent->search(middle);
    parent->childs[ind] = newNodeL;
    if(!parent->isLeaf()){
        for(int i = parent->cnt-1 ; i >= ind+1 ; i--){
            if(parent->childs[i] != nullptr)
                parent->childs[i+1] = parent->childs[i];
        }
    }

    parent->childs[ind+1] = newNodeR;
    if(parent->cnt == N+1){
        split(parent);
    }
}
template<typename T>
T BTree<T>::minData(){
    Node<T> *it = root;
    while(!it->isLeaf()){
        it = it->childs[0];
    }
    return it->keys[0];
}
int **makeAdj(int **p ,int m , int n){

    int **adj = new int *[n*m];
    for(int i = 0 ; i < n*m ; i++)
        adj[i] = new int [n*m];
    for(int i = 0 ; i < n*m ; i++){
        for(int j = 0 ; j < n*m ; j++)
            adj[i][j] = -1;
    }
    int cnt = 0 ;

    for(int i = 0; i < m ; i++){
        for(int j = 0 ; j < n;j++){
            if(p[i][j] == 0){
                for(int k = 0 ; k < m*n ; k++)
                    adj[cnt][k] = 0;
            }
            else  // if(p[i][j] == 1)
            {
                if(i != 0 && p[i-1][j] != 0)
                    adj[cnt][calcCount(i-1 , j , n)] = p[i][j]+ p[i-1][j];
                if(j != 0 && p[i][j-1] != 0)
                    adj[cnt][calcCount(i , j-1 , n)] = p[i][j] + p[i][j-1];
                if(i != m-1 && p[i+1][j] != 0)
                    adj[cnt][calcCount(i+1 , j , n)] = p[i][j] + p[i+1][j];
                if(j != n-1 && p[i][j+1])
                    adj[cnt][calcCount(i , j+1 , n)] = p[i][j] + p[i][j+1];
                for(int k = 0 ; k < m*n ; k ++)
                    if(adj[cnt][k] == -1)
                        adj[cnt][k] = 0;
            } 
            cnt++;
        }
    }

    return adj;
    
}
inline int calcCount(int i, int j ,int n){
    return n*i + j;
}
void dijkstra(int **adj ,int **matrix , int size ,int m , int n){
    pair<int , int > minVer ; 
    minVer.first = INT_MAX;
    minVer.second = -1;
    for(int start = 0 ; start <= calcCount(0 , n-1 , n); start++){
        int minDist = INT_MAX;
        int *distances = new int [size];
        bool *visitedVertexes = new bool [size];
        int *parent = new int [size];
        parent[0] = -1; 
        for (int i = 0; i < size; i++){ 
            distances[i] = INT_MAX; 
            visitedVertexes[i] = false;
        } 
        distances[start] = 0;
        for (int cnt = 0; cnt < size - 1; cnt++) { 
            int u = minDistance(distances, visitedVertexes , size); 
            visitedVertexes[u] = true;
            for(int i = 0 ; i < size ; i++){
                    if (!visitedVertexes[i] && adj[u][i] && distances[u] + adj[u][i] < distances[i]){
                        parent[i] = u; 
                        distances[i] = distances[u] + adj[u][i]; 
                    }

            }
        }
        for(int cnt = calcCount(m-1 , 0 , n) ; cnt < size ; cnt++){
            if(distances[cnt] < minDist)
                minDist = distances[cnt];
        }
        if(minDist < minVer.first){
            minVer.first = minDist;
            minVer.second = start;
        }
    }
    int *distances = new int [size];
    bool *visitedVertexes = new bool [size];
    int *parent = new int [size];
    parent[0] = -1; 
    for (int i = 0; i < size; i++){ 
        distances[i] = INT_MAX; 
        visitedVertexes[i] = false;
    } 
    distances[minVer.second] = 0;
    for (int cnt = 0; cnt < size - 1; cnt++) { 
        int u = minDistance(distances, visitedVertexes , size); 
        visitedVertexes[u] = true;
        for(int i = 0 ; i < size ; i++){
                if (!visitedVertexes[i] && adj[u][i] && distances[u] + adj[u][i] < distances[i]){
                    parent[i] = u; 
                    distances[i] = distances[u] + adj[u][i]; 
                }
        }
    }
    if(minVer.first != INT_MAX)
        findPath(distances , adj , matrix , parent , minVer.first , m , n);
    return;
}
int minDistance(int *dist , bool *visited , int size){
    int min(INT_MAX), minInd;
    for (int i = 0; i < size; i++)
        if (visited[i] == false && dist[i] <= min) {
            min = dist[i];
            minInd = i; 
        }
    return minInd;
}
int **findPath(int *dist , int **adj , int **matrix ,int *parent, int source , int rowNum , int colNum){
    BTree<int > b;
    int min(INT_MAX);
    int dest;
    for(int i = calcCount(rowNum-1,0 ,colNum) ; i <= calcCount(rowNum-1,colNum-1,colNum) ; i++){
        b.insert(dist[i]);
        min = b.minData() < min ? b.minData() : min;
        if(min == dist[i])
            dest = i;
    }
    return makePath(parent  , dest , adj , matrix,colNum);

}
int **makePath(int *parent  ,int dest , int **adj ,int **matrix , int colNum ){
    int i , j;
    i = dest / colNum;
    j = dest % colNum;
    if(parent[dest] != -1 ){
        if(matrix[i][j])
            matrix[i][j] = -1;
        makePath(parent  , parent[dest] , adj , matrix , colNum );
    }
    else if(matrix[i][j]){
        matrix[i][j] = -1;
    }
    return matrix;
}