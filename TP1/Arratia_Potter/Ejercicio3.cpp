#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;



void bucketSort(vector<pair<pair<int, int>, int>> &v, int n) {
    vector<vector<pair<pair<int, int>, int>>> b(2*n+1);

    for(int i = 0; i < n; i++){
        int bi = v[i].first.second;
        b[bi].push_back(v[i]);
    }
    int index = 0;
    for (int i = 0; i < 2*n+1; i++){
        for (int j = 0; j < b[i].size(); j++){
            v[index++] = b[i][j];
        }            
    }
}


pair<int, vector<int>> f(vector<pair<pair<int, int>, int>> &v, int n) {
    vector<int> indexes;
    int count = 0;


    pair<int, int> prev = v[0].first;
    indexes.push_back(v[0].second);
    count ++;

    for (int i = 0; i < v.size(); i++) {

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
    int n, s, t;
    cin >> n;
    vector<pair<pair<int, int>, int>> v;

    for (int i = 0; i < n; i++) {
        cin >> s;
        cin >> t;
        v.push_back(make_pair(make_pair(s,t),i+1));
    }

    bucketSort(v,n);


    pair<int, vector<int>> res = f(v, n);
    cout << res.first << endl;

    for (int i = 0; i < res.second.size(); i++) {
        cout << res.second[i] << " ";
    }
}

