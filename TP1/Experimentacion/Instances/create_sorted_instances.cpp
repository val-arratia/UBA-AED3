#include <iostream>
#include <utility>
#include <math.h>
#include <vector>
#include <fstream>

using namespace std;

int main(){


    vector<pair<int,int>> v;
    ofstream myfile;
    myfile.open ("../inputs/input_sorted.txt");

    for(int power = 5; power < 15; power++){
        long long n = pow(2,power);


        myfile << n <<endl;
        v.push_back(make_pair(1,2));
        for(int i = 0; i < n-1 ; i++){

            v.push_back(make_pair(i+1,i+2));
        }
        for(int i = 0; i < n; i++){
            myfile << v[i].first <<" "<< v[i].second <<endl;
        }
        v={};
    }
    myfile.close();
    return 0;

}