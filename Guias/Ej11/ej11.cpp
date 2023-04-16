#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

enum option {OP_ADD, OP_MUL, OP_POW, NOT};



vector<option> res;
vector<vector<vector<option>>> memo;

vector<option> ej11_backtracking(vector<int> &v, int i, int w){

    if(i == 0 && w == v[0]){
        return {};
    }
    if(i == 0 && w != v[0]){
        return {NOT};
    }
    if(w < 0){
        return {NOT};
    }

    res = ej11_backtracking(v, i-1, w - v[i-1]);
    if(res.size() == 0 || res[0] != NOT){
        res.push_back(OP_ADD);
        return res;
    }
    
    if(w % v[i-1] == 0){
        res = ej11_backtracking(v, i-1, w / v[i-1]);
        if(res.size() == 0 || res[0] != NOT){
            res.push_back(OP_MUL);
            return res;
        }
    }
    
    float x = pow(w, 1.0 / v[i]);
    if (fmod(x, 1.0) == 0) {
        res = ej11_backtracking(v, i-1, w / v[i-1]);
        if(res.size() == 0 || res[0] != NOT){
            res.push_back(OP_POW);
            return res;
        }
    }

}


vector<option> ej11_pd(vector<int> &v, int i, int w){
    if (v.size() == 0 && w == 0) return {};
    
    if(i == 0 && w == v[0]){
        return {};
    }
    if(i == 0 && w != v[0]){
        return {NOT};
    }
    
    if(w < 0){
        return {NOT};
    }


    //memorización
    if(memo[i][w].size() == 0){

        res = ej11_pd(v, i-1, w - v[i]);
        if(res.size() == 0 || res[0] != NOT){
            res.push_back(OP_ADD);
            memo[i][w] = res;
            return res;
        }

        if(w % v[i-1] == 0){
            res = ej11_pd(v, i-1, w / v[i]);
            if(res.size() == 0 || res[0] != NOT){
                res.push_back(OP_MUL);
                memo[i][w] = res;
                return res;
            }
        }

        float x = pow(w, 1.0 / v[i]);
        if (fmod(x, 1.0) == 0) {
            res = ej11_pd(v, i-1, x);
            if(res.size() == 0 || res[0] != NOT){
                res.push_back(OP_POW);
                memo[i][w] = res;
                return res;
            }
        }

        memo[i][w] = {NOT};
    }
    return memo[i][w];

}


int main(){
    int n,w;
    cin >> n;

    int e;
    vector<int> v;
    for(int i = 0; i < n; i++){
        cin >> e;
        v.push_back(e);
    }
    cin >> w;

    memo.resize(n, vector<vector<option>>(w+1));
    //memo = vector<vector<vector<option>>>(v.size(), vector<vector<option>>(w+1));
    vector<option> res = ej11_pd(v, v.size() - 1, w);

    // Print solution.
    if (res.size() == 1 && res[0] == NOT) {
        printf("no solution available\n");
    } else if (res.size() == 0) {
        printf("solution: no operations required\n");
    } else {
        printf("solution: ");
        for (int i = 0; i < res.size(); i++) printf("(");
        printf("%d", v[0]);
        for (int i = 0; i < res.size(); i++) {
            printf(" %d", res[i]);
            printf(" %d)", v[i + 1]);
        }
        printf("\n");
    }

    return 0;

}