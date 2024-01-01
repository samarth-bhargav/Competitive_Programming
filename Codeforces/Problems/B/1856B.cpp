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
        int ret = 0;
        for (int i = 0; i < n; i++){
            cin >> a[i];
            ret += (a[i] - 1);
        }
        if (n == 1){
            cout << "NO\n";
            continue;
        }
        if (ret >= count(a.begin(), a.end(), 1)){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
}