#include <iostream>
#include <vector>
#include <utility>
using namespace std;
int N;
vector<int> p;
vector<int> r(0);

bool sumSubSet(vector<int> c,int i, int j, vector<int>& r) {
    if(j<0){
        return false;
    }
    if (i ==0){
        if(j=0){
            return true;
        }
    }else{
        r.push_back(c[i]);
        
        return (sumSubSet(c,i-1,j,r)|| sumSubSet(c,i-1,j-c[i],r));
    }
}

int main() {

    cin >> N;

    p.resize(N, -1);
    for (int i=0; i<N; i++) cin >> p[i];
    
    cout << sumSubSet(p,N,12,r) << endl;
    for (int i=0; i<r.size(); i++){
        cout << r[i];
    }

    return 0;
}
