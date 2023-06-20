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

    sort(aristas.begin(),aristas.end());

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
    
    sort(solucion.begin(),solucion.end());
    
    cout << c<<endl;
    for(long long j=0;j<c;j++){
        cout << solucion[j]<< " ";
    }   
}
