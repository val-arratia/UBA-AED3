#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using namespace std;


void bucketSort(vector<pair<pair<long long, long long>, long long>> &v, long long n) {
    vector<vector<pair<pair<long long, long long>, long long>>> b(2*n+1,vector<pair<pair<long long, long long>, long long>>(0));

    for(long long i = 0; i < n; i++){
        long long bi = v[i].first.second;
        b[bi].push_back(v[i]);
    }
    long long index = 0;
    for (long long i = 0; i < 2*n+1; i++)
        for (long long j = 0; j < b[i].size(); j++)

            v[index++] = b[i][j];


}


pair<long long, vector<long long>> f(vector<pair<pair<long long, long long>, long long>> &v, long long n) {
    vector<long long> indexes;
    long long count = 0;


    pair<long long, long long> prev = v[0].first;
    indexes.push_back(v[0].second);
    count ++;

    for (long long i = 0; i < v.size(); i++) {

        if (v[i].first.first < prev.second) {
            continue;

        } else {
            prev = v[i].first;
            indexes.push_back(v[i].second);
            count ++;
        }
    }

    return make_pair(count, indexes);
}


int main() {
    long long n, s, t,c;
    vector<pair<pair<long long, long long>, long long>> v;

    cin >> c;
    ofstream myfile;
    myfile.open ("./outputs/runtime_sorted.csv");
    myfile << "n" <<"," << "time" <<endl;
    for (long long j=0;j<c ;j++){
        cin >> n;
        for (long long i = 0; i < n; i++) {
            cin >> s;
            cin >> t;
            v.push_back(make_pair(make_pair(s,t),i+1));
        }
        auto start = chrono::high_resolution_clock::now();
        bucketSort(v,n);
        pair<long long, vector<long long>> res = f(v, n);
        auto end = chrono::high_resolution_clock::now();
    
        chrono::duration<double, milli> float_ms = end - start;
    
        myfile << n << "," << float_ms.count() <<endl;
    

    }
    

    
    myfile.close();
    return 0;
}

