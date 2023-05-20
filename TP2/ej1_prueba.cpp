#include<iostream>
#include<vector>
#include<utility>
#include<iomanip>


using namespace std;

//RECURSIVO
void dfs(vector<vector<double>>& ady, double source, vector<int>& visitado,int componente) {
    visitado[source] = componente;
    for (double u : ady[source]) {
        if (visitado[u]==-1) {
            dfs(ady, u, visitado,componente);
        }
    }
}

//RECURSIVO CON TIMER Y COLORES
void dfs_timer(const vector<vector<double>>& ady,const double source, double & current_time, vector<double>& time_in, vector<double>& color,vector<double>& parents) {
    color[source] = 1;
    time_in[source] = current_time++;
    for (double u : ady[source]) {
        
        if (color[u]==0) {
            parents[u]=source;
            dfs_timer(ady, u, current_time, time_in, color, parents);
        }
    }
    color[source]=2;
}

//DETECCIÓN DE PUENTES
double dp(const vector<vector<double>>& ady, double source, const vector<double>& time_in, const vector<double>& parents, vector<pair<double,double>>& puente_con_parent) {
    double cantidad = 0;
    for (double u : ady[source]) {
        if (parents[u]==source) {
            cantidad +=dp(ady, u, time_in, parents, puente_con_parent);
        } else {
            if (time_in[source]>time_in[u] and parents[source]!=u) { //(source,u) es backedge que sube
                cantidad++;
            }
            if (time_in[source]<time_in[u]) { //(source,u) es backedge que viene de abajo 
                cantidad--;
            }
        }
    }
    if (cantidad==0 and parents[source]!=source) {
        puente_con_parent.push_back(make_pair(source,parents[source])); //cambiamos agregando la arista puente
    }
    return cantidad;
}


double combinatorio(double n,double k){
    if(n == 0 && k == 0 ) return 1;
    if(k > n || k<0) return 0;
    return combinatorio(n-1,k) + combinatorio(n-1, k-1);

}



int main() {
    //vamos a resolver como si hubiera solo 1 comp. conexa
    //En este ejemplo, tomo por entrada n, m, y una raíz
    double n,m;  
    cin >> n >> m;
    
    double v,w;
    //Creo un vector de dimensión n+1 sólo para poder usar el índice 1 en el primer vértice, se ignora 
    //                                                                  la posición 0 en los resultados
    vector<pair<double,double>> aristas;
    vector<vector<double>> grafo(n+1,vector<double>());
    for (double i=0;i<m;i++) {
        cin>>v>>w;
        grafo[v].push_back(w);
        grafo[w].push_back(v);
        
        if(v<w){
            aristas.push_back(make_pair(v,w));
        }else{
            aristas.push_back(make_pair(w,v));
        }
        
    }

    double s = v;    
    //Versión con vector de padres
    vector<double> padres(n+1,-1);
    //Establezco que el padre del vértice que va a ser la raíz es él mismo
    padres[s]=s;
    //dfs_parent(grafo, s, padres);

    //Genero vector de tiempos
    double tiempo = 0;
    vector<double> tiempos(n+1,0);
    vector<double> colores(n+1,0);
    dfs_timer(grafo, s, tiempo, tiempos, colores,padres);

    //Para detectar puentes
    vector<pair<double,double>> puentes;
    dp(grafo, s, tiempos, padres, puentes);


    vector<pair<double,double>> aristas_sin_puentes;
        /*
    for(auto a:aristas){
        bool eliminar=false;
        for(auto p:puentes){
            if(p.first>p.second){
                int k=p.first;
                p.first=p.second;
                p.second=k;
            }
            if(a == p){
                eliminar=true;
                break;
            }
        }
        if(!eliminar){
            aristas_sin_puentes.push_back(a);
        }
        
    }
    */
    vector<vector<double>> grafo_sin_puentes = grafo;
    for(auto a:aristas){
        for(auto p:puentes){
            if(p.first>p.second){
                int k=p.first;
                p.first=p.second;
                p.second=k;
            }
            if(a == p){
                grafo_sin_puentes[a.first]={};
                grafo_sin_puentes[a.second]={};
                break;
            }
        }        
    }
    for(auto p:puentes){
        if(p.first>p.second){
            int k=p.first;
            p.first=p.second;
            p.second=k;
        }
        for(auto a:grafo[p.first]){
            if(a != p.second){
                grafo_sin_puentes[p.first].push_back(a);
            } 
        }

    }



/*

//agrego aristas al nuevo grafo
    
    for (auto a : aristas_sin_puentes) {
        grafo_sin_puentes[a.first].push_back(a.second);
        grafo_sin_puentes[a.second].push_back(a.first);
    }

*/


    //cuento elementos en cada comp. conexa
    int componentes=0;
    vector<int> visitados(n+1,-1);
    for (double i = 1;i < n+1;i++) {
        if (visitados[i] == -1) {
            componentes++;
            dfs(grafo_sin_puentes,i,visitados,componentes);
        }
    }

    int cant_formas_ganar = 0;
    int cant_componente = 0;
    
    for(int comp = 1; comp <= componentes; comp++){
        for(auto v : visitados){
            if( v == comp){
                cant_componente++;
            }
        }
        cant_formas_ganar += combinatorio(cant_componente,2);
        cant_componente = 0;
        
    }

    double res = 1 - (cant_formas_ganar*1.0) / combinatorio(n,2);
    cout<< showpoint<<setprecision(5) << res  << endl;
    
}

/*6 7
6 3
3 5
5 6
3 2
2 1
1 4
4 2


8 9
1 7
7 6
6 2
6 8
6 5
2 3
2 4
3 5
4 8

*/