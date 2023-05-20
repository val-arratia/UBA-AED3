#include <iostream>

using namespace std;

int main() {
    int t; cin >> t;

    while (t--) {
        int n; cin >> n;
        int a[n]; for (int i=0; i<n; i++) cin >> a[i];
        
        for (int i=0; i<n; i++) {
            if (a[i] < n) {
                if (a[a[i]] != a[i]) {
                    swap(a[a[i]], a[i]); i--;
                }
            }
        }

        for (int i=0; i<n; i++) cout << a[i] << " ";
        cout << endl;
    }

    return 0;
}
