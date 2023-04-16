#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;
const float inf = numeric_limits<float>::infinity();
//int INF = 1e9; otra opcion
vector<vector<pair<float,float>>> memo;

pair<float,float> cc(vector<int> B, int i, int c){
    
    if(i <= 0 && c>0){
        return {inf,inf};
    }else if(c <= 0){
        return {0,0};   
    }else{
        if(memo[i-1][c].first == -1){
                pair<float,float> r = cc(B , i - 1, c - B[i-1]);
                memo[i-1][c] = min({B[i-1] + r.first, 1.0 + r.second}, cc(B, i-1, c)); 
        }
        return memo[i-1][c];
        
    }
}



int main(){
    cout << "Ejercicio 6";
    cout << "Ingrese # de elementos del conjunto y elementos";
    int n;
    cin >> n;

    int e;
    vector<int> B(0);
    for(int i;i<n;i++){
        cin >> e;
        B.push_back(e);
    }
    int c;
    cin >>c;

    memo.resize (n+1,vector<pair<float,float>>(c+1,{-1,-1}));

    pair<float,float> res;
    res = cc(B,n,c);
    cout << res.first <<endl;
    cout << res.second;
}