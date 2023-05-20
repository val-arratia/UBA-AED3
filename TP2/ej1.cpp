#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;

//RECURSIVO
void dfs(vector<vector<double>>& ady, double source, vector<bool>& visitado) {
    visitado[source] = true;
    for (double u : ady[source]) {
        if (!visitado[u]) {
            dfs(ady, u, visitado);
        }
    }
}

//RECURSIVO CON TIMER Y COLORES
void dfs_timer(const vector<vector<double>>& ady,const double source, double & current_time, vector<double>& time_in, vector<double>& color) {
    color[source] = 1;
    time_in[source] = current_time++;
    for (double u : ady[source]) {
        if (color[u]==0) {
            dfs_timer(ady, u, current_time, time_in, color);
        }
    }
    color[source]=2;
}

//RECURSIVO CON PARENT
void dfs_parent(vector<vector<double>>& ady, double source, vector<double>& parents) {
    for (double u : ady[source]) {
        if (parents[u]==-1) {
            parents[u]=source;
            dfs_parent(ady, u, parents);
        }
    }
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

/*
//contar componentes conexas
double componentes_conexas(double n){
    double componentes = 0;
    for (double i = 0;i < n;i++) {
        if (!visitado[i]) {
            componentes++;
            dfs(i);
        }
    }
    return componentes;
}
*/
double cant_jugadas(double n,double k){
    if(n == 0 && k == 0 ) return 1;
    if(k > n || k<0) return 0;
    return cant_jugadas(n-1,k) + cant_jugadas(n-1, k-1);

}



int main() {
    //vamos a resolver como si hubiera solo 1 comp. conexa
    //En este ejemplo, tomo por entrada n, m, y una raíz
    double n,m;  
    cin >> n >> m;
    
    double v,w;
    //Creo un vector de dimensión n+1 sólo para poder usar el índice 1 en el primer vértice, se ignora 
    //                                                                  la posición 0 en los resultados
    vector<vector<double>> grafo(n+1,vector<double>());
    for (double i=0;i<m;i++) {
        cin>>v>>w;
        grafo[v].push_back(w);
        grafo[w].push_back(v);
    }


/*
    //Versión con vector de visitados
    

    dfs(grafo, s, visitados);

    //dfs_iter(grafo, s, visitados);
*/
    double s = v;
    //Versión con vector de padres
    vector<double> padres(n+1,-1);
    //Establezco que el padre del vértice que va a ser la raíz es él mismo
    padres[s]=s;
    dfs_parent(grafo, s, padres);

    //Genero vector de tiempos
    double tiempo = 0;
    vector<double> tiempos(n+1,0);
    vector<double> colores(n+1,0);
    dfs_timer(grafo, s, tiempo, tiempos, colores);

    //Para detectar puentes
    vector<pair<double,double>> puentes;
    dp(grafo, s, tiempos, padres, puentes);

/*
    //Si busco encontrar los puentes en todas las componentes conexas
    for (double i = 0;i<n+1;i++) {
        if(padres[i]==-1) {
            padres[i]=i;
            dfs_parent(grafo, i, padres);
            dfs_timer(grafo, i, tiempo, tiempos, colores);
            dp(grafo, i, tiempos, padres, arista_puente);
        }
    }

    cout << "grafo: " << endl;
    for (double i=0;i<n+1;i++) {
        cout << i << ":";
        for (auto u : grafo[i]) {
            cout << u << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "visitados: ";
    for (double i=0;i<n+1;i++) {
        cout << i << ":" << visitados[i] << " ";
    }
    cout << endl;

    cout << "padres: ";
    for (double i=0;i<n+1;i++) {
        cout << i << ":" << padres[i] << " ";
    }
    cout << endl;

    cout << "timer: ";
    for (double i=0;i<n+1;i++) {
        cout << i << ":" << tiempos[i] << " ";
    }
    cout << endl;

    cout << "colores: ";
    for (double i=0;i<n+1;i++) {
        cout << i << ":" << colores[i] << " ";
    }
    cout << endl;
*/

    //si aumento la cant de comp.conexas quiero ver si las dos aristas
    //que saque quedaron en dist 

    //double cant_formas_perder=0;

    vector<pair<int,int>> cant_formas_ganar;
    vector<vector<double>> grafo_sin_puente = grafo;
    for(auto i : puentes){
        grafo_sin_puente[i.first] = {};
        grafo_sin_puente[i.second] = {};

        for( auto j : grafo[i.first]){

            if(j != i.second){
                grafo_sin_puente[i.first].push_back(j);
            }
        }
        for( auto j : grafo[i.second]){

            if(j != i.first){
                grafo_sin_puente[i.second].push_back(j);
            }
        }

        //vector de aristas ordenado numericamente sin repetidos
        pair<int,int> p;
        vector<pair<int,int>> aristas;
        for(auto t=0; t<n ; t++){
            for(auto j : grafo_sin_puente[t]){
                if(t > j){
                    p = make_pair(j,t);
                }else{
                    p = make_pair(t,j);                
                }
                for(auto k:aristas){
                    if(p.first != k.first || p.second != k.second){
                        aristas.push_back(p);
                    }
                }
            }        
        }

/*
        //cuento elementos en cada comp. conexa
        vector<bool> visitados(n+1,false);
        dfs(grafo_sin_puente,i.first,visitados);
        double c=0;
*/
        //ordeno numericamente i
        if(i.first > i.second){
            int k=i.first;
            i.first = i.second;
            i.second = k;
        }

        //para cada nodo agrego a la cantidad de formas de ganar
        for(auto a : aristas){

            //if(visitados[h]) c++;

            //si el nodo fue visitado, entonces pertenece a una componente conexa
            //agrego su arista a una posible solucion a ganar
        //si no es puente, no la agrego!!
            if(a.first != i.first || a.second != i.second){
                //me fijo que no la haya agregado antes
                int d = 0;
                for(auto e : cant_formas_ganar){
                    if(a.first != e.first || a.second != e.second){
                        d++;
                    }
                }
                if(d == cant_formas_ganar.size()){
                    cant_formas_ganar.push_back(a);
                }
                
            }
        
        }
        //cant_formas_perder += (n-c) * c;


        //al final saco otro arista puente
        grafo_sin_puente = grafo;
    }

    //double res = (cant_formas_perder.size()*1.0) / cant_jugadas(n,2);
    double res = 1 - (cant_formas_ganar.size()*1.0) / cant_jugadas(n,2);
    cout << cant_formas_ganar.size() << endl;
    cout<< showpoint<<setprecision(5) << res  << endl;
}

/*6 7
6 3
3 5
5 6
3 2
2 1
1 4
4 2*/