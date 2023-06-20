#include <vector>
#include <utility>
#include <cstdio>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <math.h>
#include<iostream>

using namespace std;
using std::cout;
using std::endl;


#define forn(i, n) for(int i = 0; i < (n); ++i)
#define INFINITY 9999999

using std::make_pair;
using std::min;
using std::pair;
using std::vector;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

typedef int cost_t;
typedef vector<cost_t> vcost_t;
typedef vector<vcost_t> vvcost_t;
typedef vvcost_t adjacency_matrix;
typedef vector<int> vint;
typedef pair<int, int> edge;
typedef vector<bool> vbool;
typedef vector<edge> vedge;
typedef pair<cost_t, edge> weighted_edge;

void initialize(const adjacency_matrix& A,
                vedge& dist) {
  int n = dist.size();
  forn(i, n) {
    forn(j, n) {
      if (A[i][j] < dist[i].first) {
        dist[i] = make_pair(A[i][j], j);
      }
    }
  }
}

weighted_edge lightest_edge(const adjacency_matrix& A,
                            const vedge& dist,
                            const vbool& rep) {
  int idx = 0, n = dist.size();
  while (!rep[idx]) ++idx;
  for (int i = idx + 1; i < n; ++i) {
    if (!rep[i]) continue;
    if (dist[i].first < dist[idx].first) idx = i;
  }
  return weighted_edge(dist[idx].first, edge(idx, dist[idx].second));
}

void contract(const weighted_edge& e,
              adjacency_matrix& A,
              vedge& dist,
              vbool& rep) {
  int n = dist.size(),
      u = e.second.first, // new parent
      v = e.second.second; // new child
  rep[v] = false;
  dist[u] = make_pair(INFINITY, -1);
  for (int i = 0; i < n; ++i) {
    if (!rep[i]) continue;
    if (i == u) continue;
    A[i][u] = A[u][i] = min(A[u][i], A[v][i]);
    if (A[u][i] < dist[u].first) {
      dist[u] = make_pair(A[u][i], i);
    }
  }
}

cost_t kruskal_warnes(adjacency_matrix& A,int w) {
  int n = A.size();
  cost_t total_cost = 0;
  vedge dist(n, make_pair(INFINITY, -1));
  vbool rep(n, true);

  initialize(A, dist);

  int remaining = n;
  while (remaining --> w) {
    weighted_edge e = lightest_edge(A, dist, rep);
    total_cost += e.first;
    contract(e, A, dist, rep);
  }

  return total_cost;
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
    
        kruskal_warnes(A,w);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double,milli> float_ms = end - start;
        
        myfile << n << "," << float_ms.count() <<endl;

    }

    myfile.close();
}
