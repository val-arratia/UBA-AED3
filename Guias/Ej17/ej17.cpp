#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <math.h>

using namespace std;
int NUM = 1e-9;
struct actividad{
    int inicio;
    int fin;
};

int cubreHasta(actividad actividad,int ancho,int inicio){
    int largoCubre=sqrt(pow((2*actividad.radio),2) - pow(ancho,2));
    int pos=actividad.posicion;
    return pos + (largoCubre/2.0);
}

bool cubreMejor(actividad mejor,actividad actividad,int ancho,int inicio){

    int largoCubre=sqrt(pow((2*actividad.radio),2) - pow(ancho,2));
    int pos=actividad.posicion;
    int inicio2=pos - (largoCubre/2.0);
//no estoy teniendo en cuenta que por ahi no me cambia el actividad pues el primero ya tiene una buena posicion
//cambio el actividad base por 0,0
    int h=cubreHasta(actividad,ancho,inicio);
    int d;
    if(mejor.radio==0){
        d=0;
    }else{
        d=cubreHasta(mejor,ancho,inicio);
    }
    if(inicio2 <= inicio /*&& actividad.posicion>= mejor.posicion*/ && h>d){
        return true;
    }else{
        return false;
    }
}



int fgolosa(vector<actividad> actividades, vector<actividad> solucion, int i){


    //ordena por ti mas temprano

    

    //Hacer una función que agarre el actividad que este más lejos posible del inicio
    //tal que cubra el inicio
    int c=0;
    int inicio=0.0;
    int j=0;
    if(largo==0.0){
        return 0;
    }
    
    //pair<int,int> mejor=make_pair(0,0);
    vector<actividad> soluciones={};
    actividad mejor;
    actividad mejorAnt=mejor;
    mejorAnt.posicion=0;
    mejorAnt.radio=0;




    if(actividades.size()==0){
        return -1;
    }else{

        
        mejor.posicion=-1;
        mejor.radio=0;
        while(inicio < largo && (mejor.posicion!=mejorAnt.posicion || mejor.radio!=mejorAnt.radio)){
            mejorAnt.posicion=mejor.posicion;
            mejorAnt.radio=mejor.radio;
            
            for(int i=0;i<actividades.size();i++){

                if(cubreMejor(mejor,actividades[i],ancho,inicio)){
                    mejor=actividades[i];
                }
            }
            if(mejor.posicion==-1 && mejor.radio==0){
                inicio=0.0;
            }else{
                inicio=cubreHasta(mejor,ancho,inicio);  
            }
            c++;
            j++;      
        }

        if((inicio - largo) < NUM && inicio !=largo){
            return -1;
        }else{
            return c;
        }


    }
    
}



int main() {
    
    int n; // cantidad de actividades
    int i=0; //inicio
    int f=0; //fin

    vector<actividad> actividades;
    for(int j=0;j<n;j++){
        cin >> i ;
        cin >> f ;
        actividad actividad;
        actividad.inicio = i;
        actividad.fin = f;
        actividades.push_back(actividad);
    
    }
    vector<actividad> solucion = {};
    vector<int> r=fgolosa(actividades,solucion,i);

    cout << r.size() << endl;
    for(int i = 0;i < r.size(); i++){
        cout << r[i];
    }
    

    

    return 0;
}