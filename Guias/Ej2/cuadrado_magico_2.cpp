#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

vector<vector<vector<int>>> todos;
int cont = 0;
vector<vector<int>> solucion;

int sumaParcialF(vector<vector<int>> c, int i,int pos2){
    int s=0;
    int j=0;
    while(j<=pos2){
        s += c[i][j];
        j++;
    }
    
    return s;
}

int sumaParcialC(vector<vector<int>> c,int j,int pos1){
    int s=0;
    int i=0;
    while(i<=pos1){
        s += c[i][j];
        i++;
    }
    
    return s;
}

int sumaParcialD1(vector<vector<int>> c,int n, int pos1){
    int s=0;
    int j = n-1;
    int i = 0;
    while(i<=pos1){
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
    while(j<=pos2 && i<=pos1){
        s += c[i][j];
        j++;
        i++;
    }
    
    return s;
}

int cuadrado_magico(vector<vector<int>> &c, vector<int> &r, int m, int i, int j, int h){
    int n = c.size();
    int contador=0;
    vector<int> r2={};
    if(cont<h){
        if(r.size()==0 ){
            solucion = c;
            cont++;
            return 1;
        
        }

    for(int k=0; k<r.size(); k++){

        c[i][j] = r[k];

        if(sumaParcialF(c,i,j) > m) continue;

        if(j == n-1 && sumaParcialF(c,i,j) != m) continue;

        if(sumaParcialC(c,j,i) > m) continue;

        if(i==n-1 && sumaParcialC(c,j,i) != m) continue;

        if(i==j && sumaParcialD1(c,n,i) > m) continue;

        if(i==n-1 && sumaParcialD1(c,n,i) != m) continue;

        if(sumaParcialD2(c,i,j) > m) continue;

        if(i==n-1 && j==n-1  && sumaParcialD2(c,i,j) != m) continue;

        for(int e=0; e<r.size();e++){
            if(e != k){
                r2.push_back(r[e]);
            }
        }
        
        if(j==n-1){
            contador += cuadrado_magico(c,r2,m, i+1,0,h);
        }else{
            contador += cuadrado_magico(c,r2,m,i,j+1,h);
        }

        r2={};

        c[i][j]=0;
    }

    }

    return contador;
    
}

int main(){
    int n,k;
    cin >> n;
    cin >> k;

    int m = (n * n * n + n) / 2;

    vector<int> r;
    for(int i=1;i<=n*n;i++){
        r.push_back(i);
    }
    vector<vector<int>> c (n,vector<int>(n));

    int res = cuadrado_magico(c,r, m, 0,0,k);

    printf("%dx%d magic squares (optimized): %d\n", n, n,res);
    for(int k=0;k<solucion.size();k++){
        for(int i=0;i<solucion[k].size();i++){
            
            printf(", %d",solucion[k][i]);

        }

        printf(";\n");
    }
    return 0;
}