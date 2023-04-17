#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

enum option {OP_ADD, OP_SUB, OP_MUL, OP_POW, NOT};


long long w = 0;
vector<vector<long long>> memo;

/*
int pd(int i, int r, int m, vector<int> &v){
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
    if(memo[i][w % m].size() == 0){

        w += v[i];
        res = pd(i-1, r, m, v);
        //memo[i][w % m] = (w % m);
        return (w % m == r);


        w -= v[i];
        res = pd(v, i-1, w + v[i]);
        if(res.size() == 0 || res[0] != NOT){
            res.push_back(OP_SUB);
            memo[i][w] = res;
            return res;
        }

        if(w % v[i-1] == 0){
            res = pd(v, i-1, w / v[i]);
            if(res.size() == 0 || res[0] != NOT){
                res.push_back(OP_MUL);
                memo[i][w] = res;
                return res;
            }
        }

        float x = pow(w, 1.0 / v[i]);
        if (fmod(x, 1.0) == 0) {
            res = pd(v, i-1, x);
            if(res.size() == 0 || res[0] != NOT){
                res.push_back(OP_POW);
                memo[i][w] = res;
                return res;
            }
        }

        //memo[i][w] = {NOT};
    //}
    return memo[i][w];

}
*/

int pd(int i, int r, int m, vector<int> &v, vector<vector<long long>> &memo){


    int n = v.size();

    for(int i = 1; i < n; i++){
        for(int j = 0; j < m; j++){
            w = memo[i-1][j];
            if(w != -1){
                long long s;
                s = v[i] + w;
                s = s % m;
                memo[i][s] = s;

                s = w - v[i];
                if( s < 0 ) s += m;
                s = s % m;

                memo[i][s] = s;

                s = v[i] * w;
                s = s % m;
                memo[i][s] = s;

                s = pow( w, v[i]);
                s = s % m;
                memo[i][s] = s;

            }

        }
/*
        long long resto = v[0] % m;
        w = memo[i-1][resto];
        w = v[i] + memo[i-1][w % m];
        memo[i][w % m] = w;

        w = memo[i-1][w % m] - v[i];
        memo[i][w % m] = w;

        w = v[i] * memo[i-1][w % m];
        memo[i][w % m] = w;

        w = pow( memo[i-1][w % m], v[i]);
        memo[i][w % m] = w;
*/
    }


    return memo[n-1][r];
}

int main(){
    int t,n,r;
    long long m;
    cin >> t; //cant casos de tests

    for(int j = 0; j < t ; j++){
        cin >> n; //cant elementos del vector
        cin >> r; //resto
        cin >> m; //dividendo

        int e;
        vector<int> v;

        for(int i = 0; i < n; i++){
            cin >> e;
            v.push_back(e);
        }
        
        memo.resize(n, vector<long long>(m+1,-1));
        long long resto = v[0] % m;
        memo[0][resto] = v[0] % m;
        w = memo[0][resto];
            


        int res = pd(0, r, m, v, memo);
        cout << res;


    }
    
   

}