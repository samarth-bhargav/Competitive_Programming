#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        int even = 0, odd = 0;
        set<int> diffs; diffs.insert(0);
        bool good = false;
        for (int i = 0; i < n; i++){
            if (i % 2 == 0){
                even += a[i];
            }
            else{
                odd += a[i];
            }
            if (diffs.count(even - odd)){
                cout << "YES\n";
                good = true;
                break;
            }
            diffs.insert(even - odd);
        }
        if (!good){
            cout << "NO\n";
        }
    }
}