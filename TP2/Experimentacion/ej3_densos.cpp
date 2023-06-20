#include <vector>
#include <utility>
#include <cstdio>
#include <algorithm>
#include<iostream>

#include<iomanip>
#include <set>
#include <math.h>

#include <chrono>
#include <fstream>
#include <string>
#include<numeric>
using std::cout;
using std::endl;

using namespace std;

#define forn(i, n) for(int i = 0; i < (n); ++i)

using std::accumulate;
using std::make_pair;
using std::min;
using std::pair;
using std::vector;

typedef double cost_t;
typedef vector<cost_t> vcost_t;
typedef vector<vcost_t> vvcost_t;
typedef vvcost_t adjacency_matrix;
typedef vector<long long> vint;
typedef pair<long long, long long> edge;
typedef vector<edge> vedge;
typedef vector<vedge> vvedge;
typedef pair<cost_t, edge> weighted_edge;
typedef vector<weighted_edge> vweighted_edge;

void initialize(const adjacency_matrix& A,
                vvedge& B,
                vcost_t& dist,
                vint& parent) {
  int n = dist.size();
  forn(i, n) {
    forn(j, n) {
      dist[i] = min(dist[i], A[i][j]);
      B[i][j] = edge(i, j);
    }
    parent[i] = i;
  }
}
weighted_edge lightest_edge(const adjacency_matrix& A,
                            const vcost_t& dist,
                            const vint& parent) {
  int idx = 0, n = dist.size();
  while (parent[idx] != idx) ++idx;
  for (int i = idx + 1; i < n; ++i) {
    if (parent[i] != i) continue;
    if (dist[i] < dist[idx]) idx = i;
  }
  cost_t weight = dist[idx];
  int target = 0;
  for (int i = 0; i < n; ++i) {
    if (parent[i] != i) continue;
    if (A[idx][i] == weight) {
      target = i;
      break;
    }
  }

  return weighted_edge(weight, edge(idx, target));
}

void contract(const weighted_edge& e,
              adjacency_matrix& A,
              vvedge& B,
              vcost_t& dist,
              vint& parent) {
  int n = dist.size(),
      u = e.second.first, // new parent
      v = e.second.second; // new child
  parent[v] = u;
  dist[u] = INFINITY;
  for (int i = 0; i < n; ++i) {
    if (parent[i] != i) continue;
    if (i == u) continue;
    if (A[v][i] < A[u][i]) {
      A[u][i] = A[v][i];
      B[u][i] = B[v][i];
    }
    A[i][u] = A[u][i];
    B[i][u] = edge(B[u][i].second, B[u][i].first);
    dist[u] = min(dist[u], A[u][i]);
  }
}

vweighted_edge kruskal_warnes(adjacency_matrix& A) {
  int n = A.size(), u, v;
  cost_t cost;
  vweighted_edge edges;
  vcost_t dist(n, INFINITY);
  vint parent(n);
  vvedge B(n, vedge(n, edge(0, 0)));

  initialize(A, B, dist, parent);

  int remaining = n - 1;
  while (remaining --> 0) {
    weighted_edge e = lightest_edge(A, dist, parent);
    cost = e.first;
    u = e.second.first;
    v = e.second.second;
    weighted_edge original_edge(cost, B[u][v]);
    edges.push_back(original_edge);
    contract(e, A, B, dist, parent);
  }

  return edges;
}




int main() {


    int c, n, r, w, u, v;
    
    cin >> c;

    ofstream myfile;

    myfile.open ("./outputs/runtime_Denso.csv");
    myfile << "n" <<"," << "time" <<endl;

    vector <pair <cost_t, pair<int, int>>> E;

    for (int test = 1; test <= c; test++) {

        E.clear();

        cin >> n >> r >> w >> u >> v;

        double cableUtp_costo = 0;
        double fibraOptica_costo = 0;
        int k = n;

        auto start = chrono::high_resolution_clock::now();

        vector<pair<int,int>> posiciones;
    
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            posiciones.push_back(make_pair(x, y));
        }
 
        for (int i = 0; i < n ; i++) {
            for (int j = i+1; j < n; j++ ){
                cost_t d = sqrt(pow((posiciones[i].first - posiciones[j].first),2)+pow((posiciones[i].second - posiciones[j].second),2));
                E.push_back(make_pair(d, make_pair(i+1, j+1))); 
            }
        
        }
        adjacency_matrix A(n+1, vcost_t(n+1, INFINITY));
        for(long long j=0;j<E.size();j++){
            A[E[j].second.first][E[j].second.second] = A[E[j].second.second][E[j].second.first] = E[j].first;
            
        }
        vweighted_edge edges = kruskal_warnes(A);


        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double,milli> float_ms = end - start;
        
        myfile << n << "," << float_ms.count() <<endl;


    }


}

