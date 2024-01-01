#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        int oidx, nidx, tidx;
        for (int i = 0; i < n; i++){
            cin >> a[i];
            if (a[i] == 1){
                oidx = i;
            }
            else if (a[i] == n){
                nidx = i;
            }
            else if (a[i] == 2){
                tidx = i;
            }
        }
        if ((tidx < oidx) ^ (nidx < oidx)){
            //different sides
            cout << oidx + 1 << " " << nidx + 1 << "\n";
        }
        else{
            //same side
            if (abs(tidx - oidx) > abs(nidx - oidx)){
                cout << 1 << " " << 1 << "\n";
            }
            else{
                cout << nidx + 1 << " " << tidx + 1 << "\n";
            }
        }
    }
}