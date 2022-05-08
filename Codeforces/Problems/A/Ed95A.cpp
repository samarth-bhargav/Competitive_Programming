#include <bits/stdc++.h>
using namespace std;

int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        long long x,y,k;
        cin >> x >> y >> k;
        cout << ((y*k)+x-2)/(x-1) + k + (k - ((x-1) * ((y*k+x-2)/(x-1)) - y*k)-1+x-2)/(x-1) << "\n";
    }
}