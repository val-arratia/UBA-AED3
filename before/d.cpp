//
// Created by vale on 20/09/22.
//
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <math.h>
#include <limits>

using namespace std;

long long inf = std::numeric_limits<long long>::max() /2;

struct aspersor{
    double empieza;
    double termina;
    int costo;
};

double cubreHasta(double posicion, double radio,double ancho){
    if(radio != 0){
        double largoCubre=sqrt(pow((2*radio),2) - pow(ancho,2));
        double pos=posicion;
        return pos + (largoCubre/2.0);
    }else{
        return 0;
    }
}

double cubreDesde(double posicion, double radio,double ancho, double largo){
    if(radio != 0){
        double largoCubre=sqrt(pow((2*radio),2) - pow(ancho,2));
        double pos=posicion;
        return pos - (largoCubre/2.0);
    }else{
        return largo;
    }

}

bool cubreMejor(aspersor mejor,aspersor aspersor,double ancho,double inicio){
    if(aspersor.empieza <= inicio && aspersor.termina > mejor.termina){
        return true;
    }else{
        return false;
    }
}

//Quien cubra el inicio obligatoriamente y que no se pase del largo?

bool algunoCubre(vector<aspersor>& aspersores,double largo, double inicio){ //el valor largo no lo estamos usando
    bool existe=false;
    for(int i=0; i<aspersores.size();i++){
        if(aspersores[i].empieza <= inicio && aspersores[i].empieza <= largo ){
            existe= true;
        }
    }
    return existe;
}

int menor(vector<aspersor>& aspersores, int inicio, int fin,int i,double largo, vector<int>& costos){
    if(i==aspersores.size() || aspersores[i-1].termina>=largo){
        return 0;
    }else if(!algunoCubre(aspersores,fin,inicio)){
        return inf;
    }
    costos[i]=10000;
    for(int j=i; j<aspersores.size() && aspersores[j].empieza<=fin;j++){
        if(aspersores[j].termina>fin){
            int a =menor(aspersores,inicio,fin,j+1,largo,costos);
        }
        int a = menor(aspersores,aspersores[j].empieza,aspersores[j].termina,j+1,largo,costos);
        int b = menor(aspersores,inicio,fin,j+1,largo,costos);
        //costos[j]=min(min(a+aspersores[j].costo,b),costos[j]);
        costos[j]=min(a+aspersores[j].costo,b);
    }
    for(int k=i; k<aspersores.size() && aspersores[k].empieza<=fin;k++){
        costos[i]= min(costos[k],costos[i]);
    }

    return costos[i];
}



int menorCosto(vector<aspersor>& aspersores,double largo,double inicio,double final,int i, vector<int>& costos){

    if(!algunoCubre(aspersores,aspersores[i].termina,inicio)){// O(n) //ver funcion creo que hay errores
        return -1;
    }else{
        int j=i;
        if(costos[j]==-2){
            while(j<aspersores.size() && aspersores[j].empieza<=inicio){
                int a= menorCosto(aspersores,largo,aspersores[j].empieza,aspersores[j].termina,j+1,costos) + aspersores[j].costo;
                int b= menorCosto(aspersores,largo,inicio,final,j+1,costos);
                costos[i]=min(a,b);

                j++;
            }

        }

        return costos[i];

    }
}

void ordenar(vector<aspersor>& aspersores){
    for(int i=1; i<aspersores.size();i++){
        for(int j=0;j<aspersores.size();j++){
            if(aspersores[i].empieza<aspersores[j].empieza){
                swap(aspersores[i],aspersores[j]);
            }
        }
    }
}



int main() {

    int n=0; // cantidad de ASPERSORES
    int l=0; // largo
    int m=0; // ancho
    int c=0;
    double p=0.0; //posicion
    double r=0.0; //radio
    vector<int> soluciones;


    //while( cin >> n ) {
    cin >> n;
        cin >> l ;
        cin >> m;
        vector<aspersor> aspersores;
        int total=0;
        for(int i=0;i<n;i++){
            cin >> p ;
            cin >> r ;
            cin >> c ; // ahora agregamos COSTO
            total+=c;
            aspersor aspersor;
            aspersor.empieza = cubreDesde(p,r,m,l);
            aspersor.termina = cubreHasta(p,r,m);
            aspersor.costo=c;
            // aca ya descarto cualquier aspersor que no cubra minimamente el ancho
            if(r*2 > m){
                aspersores.push_back(aspersor);
            }
        }

        ordenar(aspersores);
        /*
        for(int i=0; i<aspersores.size();i++){
            cout << aspersores[i].empieza <<endl;
        }


        int h =menor(aspersores,l,0,0,l,costos);
        for(int i=0; i<costos.size();i++){
            cout << costos[i] <<endl;
        }
        */
        vector<int> costos(aspersores.size(),-2);
        soluciones.push_back(menor(aspersores,l,0,0,l,costos));


    //}

    for(int i=0; i<soluciones.size();i++){
        cout << soluciones[i] << endl;
    }


    return 0;
}