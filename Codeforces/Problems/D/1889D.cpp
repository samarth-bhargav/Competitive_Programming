#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, c; cin >> n >> c;
        vector<int> a(n+1);
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }
        multiset<array<int, 2>> a1_constraints;
        for (int i = 2; i <= n; i++){
            a1_constraints.insert({i * c - a[i], i});
        }
        int a1 = a[1];
        while (!a1_constraints.empty()){
            array<int, 2> fs = *a1_constraints.begin();
            if (fs[0] > a1){
                break;
            }
            a1 += a[fs[1]];
            a1_constraints.erase(a1_constraints.begin());
        }
        if (!a1_constraints.empty()){
            cout << "No\n";
        }
        else{
            cout << "Yes\n";
        }
    }
}