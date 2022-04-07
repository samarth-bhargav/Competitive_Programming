#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    int t;
    cin >> t;
    while (t--){
        int n,k;
        cin >> n >> k;
        vector<int>a(n);
        for (auto & i : a){
            cin >> i;
        }
        for (int i = 0; i < n-1; i++){
            if (a[i] > k){
                a[i] -= k;
                a[n-1] += k;
                k = 0;
                break;
            }
            else{
                a[n-1] += a[i];
                a[i] = 0;
                k -= a[i];
            }
        }
        for (auto & i : a){
            cout << i << " ";
        }
        cout << "\n";
    }
}

