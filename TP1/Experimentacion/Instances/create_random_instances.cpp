#include <iostream>
#include <utility>
#include <math.h>
#include <vector>
#include <fstream>

using namespace std;

int main(){


    vector<pair<int,int>> v;
    ofstream myfile;
    myfile.open ("../inputs/input_random.txt");

    for(int power = 5; power < 15; power++){
        long long n = pow(2,power);

        
        myfile << n <<endl;
        for(int i = 0; i < n ; i++){
            long long randoms = 1 + (rand() % (2*n - 2));
            long long s = randoms;

            long long randomt = s + 1 + (rand() % (2*n-s));
            long long t = randomt;
            v.push_back(make_pair(s,t));
        }
        for(int i = 0; i < n; i++){
            myfile << v[i].first <<" "<< v[i].second <<endl;
        }
        
        
    }
    myfile.close();
    return 0;

}