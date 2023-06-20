#include<iostream>
#include<vector>
#include<utility>
#include<iomanip>
#include <algorithm>

using namespace std;

void dfs(vector<vector<long long>>& ady, long long source, vector<bool>& visitado) {
    visitado[source] = true;
    for (long long u : ady[source]) {
        if (visitado[u]==false) {
            dfs(ady, u, visitado);
        }
    }
}
void swaps(long long *a,long long *b){
    long long *k=a;
    a=b;
    b=k;
}
void heapify(vector<long long> arr, long long N, long long i){

    long long largest = i;
    long long left = 2 * i + 1; 
    long long right = 2 * i + 2;

    if (left < N && arr[left] > arr[largest])
        largest = left;

    if (right < N && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swaps(&arr[i], &arr[largest]); 
        heapify(arr, N, largest);
    }
}

void heapSort(vector<long long> arr, long long N){
    for (long long i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);
    for (long long i = N - 1; i >= 0; i--) {
        swaps(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}
void swaps2(pair<long long,long long> *a,pair<long long,long long> *b){
    pair<long long,long long> *k=a;
    a=b;
    b=k;
}
void heapify2(vector<pair<long long,long long>> arr, long long N, long long i){

    long long largest = i;
    long long left = 2 * i + 1; 
    long long right = 2 * i + 2;

    if (left < N && arr[left].first > arr[largest].first)
        largest = left;

    if (right < N && arr[right].first > arr[largest].first)
        largest = right;

    if (largest != i) {
        swaps2(&arr[i], &arr[largest]); 
        heapify2(arr, N, largest);
    }
}
void heapSort2(vector<pair<long long,long long>> arr, long long N){
    for (long long i = N / 2 - 1; i >= 0; i--)
        heapify2(arr, N, i);
    for (long long i = N - 1; i >= 0; i--) {
        swaps2(&arr[0], &arr[i]);
        heapify2(arr, i, 0);
    }
}

int main() {
    long long n,m;  
    cin >> n >> m;
    
    long long v,w;
    vector<pair<long long,long long>> aristas;
    vector<vector<long long>> grafo(n+1,vector<long long>());
    for (long long i=0;i<m;i++) {
        cin>>v>>w;
        grafo[v].push_back(w);
        aristas.push_back(make_pair(v,w));
    }

    heapSort2(aristas,aristas.size());

    long long c=0;
    vector<long long> solucion;
    vector<bool> visitado(n+1,false);
    for(long long i = 0;i < aristas.size();i++){
        if(!visitado[aristas[i].first]){
            dfs(grafo,aristas[i].first,visitado);
            solucion.push_back(aristas[i].first);
            c++;
        }
    }
    for(long long i = 1;i < n+1 ; i++){
        if(!visitado[i]){
            c++;
            solucion.push_back(i);
        }
    }
    
    heapSort(solucion,solucion.size());
    
    cout << c<<endl;
    for(long long j=0;j<c-1;j++){
        cout << solucion[j]<< " ";
    }
    cout << solucion[c-1];
}
