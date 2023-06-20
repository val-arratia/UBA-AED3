#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

long long w;
vector<vector<long long>> memo;

long long mod_bin_exp(long long x, int y, int n) {
	long long res;
	if (y == 0) {
		return 1;
	}
	if (y % 2 == 0) {
		res = mod_bin_exp(x, y/2, n);
		return (res * res) % n;
	} else {
		res = mod_bin_exp(x, y/2, n);
		return (((res * res) % n) * x) % n;
	}
}

int pd(int i, int r, int m, vector<int> &v,vector<vector<long long>> &memo){

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
                while(s<0){
                    s += m;
                }
                s = s % m;
                memo[i][s] = s;

                s = v[i] * w;
                s = s % m;
                memo[i][s] = s;

                s = mod_bin_exp(w, v[i], m);
                memo[i][s] = s;

            }

        }

    }


    return memo[n-1][r];
}

int main(){
    int t,n,r;
    long long m;
    cin >> t; //cant casos de tests

    vector<int> solucion = {};

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
        vector<vector<long long>> memo;
        memo.resize(n, vector<long long>(m+1,-1));
        long long resto = v[0] % m;
        memo[0][resto] = v[0] % m;

            
        int res = pd(0, r, m, v,memo);
        solucion.push_back(res);

    }
    for(int i = 0;i < solucion.size(); i++){
        if(solucion[i] == -1){
            cout << "No" <<endl;
        }else{
            cout << "Si" <<endl;
        }
    }
   
}