#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

vector<vector<vector<int>>> todos;


bool esMagico(vector<vector<int>> c){

}

int sumaParcialF(vector<vector<int>> c, int i,int pos2){
    int s=0;
    int j=0;
    while(j<pos2){
        s += c[i][j];
        j++;
    }
    
    return s;
}

int sumaParcialC(vector<vector<int>> c,int j,int pos1){
    int s=0;
    int i=0;
    while(i<pos1){
        s += c[i][j];
        i++;
    }
    
    return s;
}

int sumaParcialD1(vector<vector<int>> c,int n, int pos1,int pos2){
    int s=0;
    int j = n;
    int i = 0;
    while(i<pos1 && j>pos2){
        s += c[i][j];
        j--;
        i++;
    }
    
    return s;
}

int sumaParcialD2(vector<vector<int>> c,int pos1,int pos2){
    int s=0;
    int j = 0;
    int i = 0;
    while(j<pos2 && i<pos1){
        s += c[i][j];
        j++;
        i++;
    }
    
    return s;
}

int cuadrado_magico(vector<vector<int>> &c, vector<int> &r, vector<int> &p, int m, int i, int j){
    int n = c.size();
    int contador=0;
    vector<int> r2={};
    if(r.size()==0){
        return 1;
        
    }
    
    for(int k=0; k<r.size(); k++){

        c[i][j] = r[k];

        if(p[i] + r[k] > m) continue;

        if(j == n - 1 && p[i] + r[k] != m) continue;

        if(p[n + j] +r[k] > m) continue;

        if(i == n - 1 && p[n + j] + r[k] != m) continue;

        bool is_diagonal1 = i == j;
        bool is_diagonal2 = i == n - j - 1;

        if(is_diagonal1 && p[2 * n] + r[k] > m) continue;

        if(is_diagonal1 && i == n - 1 && p[2 * n] + r[k] != m) continue;

        if(is_diagonal2 && p[2 * n + 1] + r[k] > m) continue;

        if(is_diagonal2 && i == n - 1 && p[2 * n + 1] + r[k] != m) continue;

        for(int e=0; e<r.size();e++){
            if(e != k){
                r2.push_back(r[e]);
            }
        }
        p[i] += r[k];
        p[n + j] += r[k];
        if (is_diagonal1) p[2 * n] += r[k];
        if (is_diagonal2) p[2 * n + 1] += r[k];
        
        if(j==n){
            contador += cuadrado_magico(c,r2,p,m, i+1,0);
        }else{
            contador += cuadrado_magico(c,r2,p,m,i,j+1);
        }

        r2={};

        c[i][j]=0;
        p[i] -= r[k];
        p[n + j] -= r[k];
        if (is_diagonal1) p[2 * n] -= r[k];
        if (is_diagonal2) p[2 * n + 1] -= r[k];
    }

    return contador;
}

int main(){
    int n,k;
    //cin >> n;

    n=3;
    int m = (n * n * n + n) / 2;

    vector<int> r;
    for(int i=1;i<=n*n;i++){
        r.push_back(i);
    }
    vector<vector<int>> c (n,vector<int>(n));
    vector<int> p(2 * n + 2);
    int res = cuadrado_magico(c,r,p, m, 0,0);

    printf("%dx%d magic squares (optimized): %d\n", n, n,res);
    for(int k=0;k<todos.size();k++){
        for(int i=0;i<todos[k].size();i++){
            for(int j=0;j<todos[k][i].size();j++){
                printf(", %d",todos[k][i][j]);
            }
            printf(";\n");
        }
        printf(";;\n");
        printf(";\n");
    }
    return 0;
}