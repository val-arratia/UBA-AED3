#include<iostream>
#include<vector>
#include<utility>
#include<iomanip>
#include <set>
#include <math.h>
#include <algorithm>


using namespace std;
//int test;
 /*
using ll = long long;
const ll inf = 1e18;

int n,m;
// vector<tuple<ll,int,int>> E;
vector <pair <int, pair<int, int>>> E;
*/
struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],
        rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

void kruskal( int n, int r, int w, int u, int v, vector <pair <double, pair<int, int>>> E, double cableUtp_costo, double fibraOptica_costo, int k, int test){
    sort(E.begin(),E.end()); 

    //ll res = 0;
    int aristas = 0;
    DSU dsu(n);

    for(int i = 0; i < E.size(); i++){ 
        
        //si (u,v) es arista segura    
        if(dsu.find(E[i].second.first) != dsu.find(E[i].second.second)){
            // agregar
            dsu.unite(E[i].second.first,E[i].second.second);
            aristas++;
        

            if (E[i].first <= r) {
                cableUtp_costo +=  E[i].first * u;
            } else {
                fibraOptica_costo +=  E[i].first * v;
            }
            
        
            //res += E[i].first;
            k--;
            if (k == w) {
                break;
            }
        }
    }
    
    cout<<std::fixed << std::setprecision(3) << "Caso #"<< test <<": "<< cableUtp_costo << " " << fibraOptica_costo << endl;
    
}

int main() {

    int c, n, r, w, u, v;
    
    cin >> c;

    vector <pair <double, pair<int, int>>> E;

    for (int test = 1; test <= c; test++) {

        E.clear();
        
        //while(!E.empty()) E.pop_back();
        

        cin >> n >> r >> w >> u >> v;

        double cableUtp_costo = 0;
        double fibraOptica_costo = 0;
        int k = n;

        vector<pair<int,int>> posiciones;
    
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            posiciones.push_back(make_pair(x, y));
        }
 
        for (int i = 0; i < n ; i++) {
            for (int j = i+1; j < n; j++ ){
                double d = sqrt(pow((posiciones[i].first - posiciones[j].first),2)+pow((posiciones[i].second - posiciones[j].second),2));
                E.push_back(make_pair(d, make_pair(i+1, j+1))); 
            }
        
        }
   
        kruskal(n, r, w, u, v, E, cableUtp_costo, fibraOptica_costo, k, test);

    }

}
