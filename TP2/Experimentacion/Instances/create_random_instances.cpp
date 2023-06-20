#include <iostream>
#include <utility>
#include <math.h>
#include <vector>
#include <fstream>

using namespace std;

int main(){


    vector<pair<long long,long long>> posiciones;
    ofstream myfile;
    myfile.open ("../inputs/input_random.txt");
    myfile << 10 << endl;
    for(int power = 5; power < 15; power++){
        long long n = pow(2,power);
        long long r = (rand() % n);
        long long w = n;
        long long u = (rand() % n/10);
        long long v = (rand() % n/10);
        
        myfile<< n <<" "<< r <<" "<< w <<" " << u <<" "<< v <<endl;
        for(int i = 0; i < n ; i++){
            long long randomx = (rand() % (n/2));
            long long x = randomx;

            long long randomy = (rand() % (n/2));
            long long y = randomy;
            posiciones.push_back(make_pair(x,y));
        }
        for(int i = 0; i < n; i++){
            myfile << posiciones[i].first <<" "<< posiciones[i].second <<endl;
        }
        
        
    }
    myfile.close();
    return 0;

}