#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

vector<vector<vector<int>>> todos;
int cont = 0;
vector<vector<int>> solucion;


int cuadrado_magico(vector<vector<int>> &c, vector<vector<int>> &sp, vector<int> &r, vector<bool> &d, int m, int i, int j, int h){
    int n = c.size();
    int contador=0;
    if(cont<h){
        if(i == n ){
            if (cont < h - 2) solucion = c;
            cont++;
            return 1;
        
        }

        for(int k=0; k<r.size(); k++){

            c[i][j] = r[k];

            if(d[k] != true) continue;

            if(sp[0][i]+ r[k] > m) continue;

            if(j == n-1 && sp[0][i]+ r[k] != m) continue;

            if(sp[1][j]+ r[k] > m) continue;

            if(i==n-1 && sp[1][j]+ r[k] != m) continue;

            if(i==j && sp[0][n]+ r[k] > m) continue;

            if(i==n-1 && j==i && sp[0][n]+r[k] != m) continue;

            if(n-1-i==j && sp[1][n]+ r[k] > m) continue;

            if(i==n-1 && n-1-i==j && sp[1][n]+ r[k] != m) continue;
            
            d[k] = false;
            sp[0][i] += r[k];//filas
            sp[1][j] += r[k];//columnas

            if(i==j){
                sp[0][n] += r[k];//diag 1
            }
            if(n-1-i==j){
                sp[1][n] += r[k];//diag 2

            }
           


            if (j == n-1) {
 
                contador += cuadrado_magico(c,sp,r,d,m, i+1,0,h);
            }else{
                 contador += cuadrado_magico(c,sp,r,d,m,i,j+1,h);
            }
               
        


            c[i][j]=0;
            d[k] = true;
            sp[0][i] -= r[k];
            sp[1][j] -= r[k];
            if(i==j){
                sp[0][n] -= r[k];
            }
            
            if(n-1-i==j){
                sp[1][n] -= r[k];
            }
            
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
    vector<bool> d(n*n,true);
    for(int i=1;i<=n*n;i++){
        r.push_back(i);
    }
    vector<vector<int>> c (n,vector<int>(n));

    vector<vector<int>> sp (2,vector<int>(n+1,0));
    int res = cuadrado_magico(c,sp,r,d, m, 0,0,k);

    if(res < k){
        cout << -1 << endl;

    }else{
        for(int k=0;k<solucion.size();k++){
           for(int i=0;i<solucion[k].size();i++){
               if (i > 0) cout<< " ";
               cout << solucion[k][i];
           }
            cout << endl;
        }
    }
    

}