#include <iostream>
#include <vector>
#include <utility>
#include <functional>

using namespace std;

using aspersor = pair<int,int>; // distancia horzontal, radio


void swap(vector<aspersor>& aspersores, int i,int j){
    aspersor help = aspersores[i];
    aspersores[i] = aspersores[j];
    aspersores[j] = help;
}

int partition(vector<aspersor>& aspersores, int start, int end){
 
    int pivot = aspersores[start].first;
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (aspersores[i].first <= pivot)
            count++;
    }
 

    int pivotIndex = start + count;
    swap(aspersores,pivotIndex, start);

    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (aspersores[i].first <= pivot) {
            i++;
        }
 
        while (aspersores[j].first > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(aspersores,i++, j--);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(vector<aspersor>& aspersores, int start, int end){


    if (start >= end)
        return;

    int p = partition(aspersores, start, end);

    quickSort(aspersores, start, p - 1);
    quickSort(aspersores, p + 1, end);
}



int cubrimiento(aspersor aspersor,int inicio, int largo){

}

int cubreHasta(aspersor aspersor,int inicio, int largo){

}

int fgolosa(vector<aspersor> aspersores, int n, int largo, int ancho ){
    
    //deberiamos tener al radio mas grande y mas cerca del 0  primero

    // busqueda binaria desde el aspersor central

    //Hacer una función que agarre el aspersor que este más lejos posible del inicio
    //tal que cubra el inicio
    int c=0;
    int inicio=0;
    pair<int,int> mejor=make_pair(0,0);
    while(inicio >= largo){
        for(int i=0;i<aspersores.size();i++){
            if(cubrimiento(aspersores[i],inicio,largo)>=cubrimiento(mejor,inicio,largo) ){
                mejor=aspersores[i];
                inicio=cubreHasta(aspersores[i],inicio,largo);
            }
        }
        
    }

    return 0;
}



int main() {
    
    int n=0; // cantidad de SPERSORES
    int l=0; // largo
    int m=0; // ancho 
    int c=0;
    int r=0;
    cin >> n;
    //while(!(.eof())){          por ahora ingresemos solo un test
        cin >> l,m ;
        vector<aspersor> aspersores;
        for(int i=0;i<n;i++){
            cin >> c ;
            cin >> r ;
            // aca ya descarto cualquier aspersor que no cubra minimamente el ancho
            if(r*2 >= m){
                aspersores.push_back(make_pair(c,r));
            }
        }
         // ordenamos a los aspersores por su rpimero parametro (distancia horizontla)
         //ordeno por su radio
        quickSort(aspersores,0, aspersores.size());
        // ordenamos por segundo parametro  (? a lo mejor no hace falta)
        //ordenar(aspersores);

        cout << fgolosa(aspersores, n,l,m)<< endl;
        cin >> n;
    //}
    
   /* esto esta para probar si el algoritmo de ordenamiento anda bien
   vector<aspersor> lista{make_pair(3,5),make_pair(5,5),make_pair(1,5),make_pair(2,5)};

    heapSort(lista,lista.size());
    for(int i=0; i< lista.size();i++){
        cout << lista[i].first << ","<<lista[i].second << endl;
    }
    */
    return 0;
}
