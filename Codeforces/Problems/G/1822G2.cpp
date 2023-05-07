#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<vector<int>> factors(n, vector<int>());
        for (int i = 0; i < n; i++){
            factors[i].reserve(85);
        }
        unordered_map<int, int> where;
        unordered_map<int, int> occ;
        for (int i = 0; i < n; i++){
            if (where.count(a[i])) continue;
            for (int j = 1; j <= sqrt(a[i]); j++){
                if (a[i] % j == 0 && (a[i] / j) % j == 0){
                    factors[i].push_back(a[i] / j);
                    occ[a[i] / j] = 0;
                    occ[a[i] / j / j] = 0;
                }
            }
            where[a[i]] = i;
        }
        unordered_map<int,int> aocc;
        for (int i = 0; i < n; i++){
            occ[a[i]]++;
            aocc[a[i]]++;
        }
        long long ans = 0;
        for (pair<int, int> kv : aocc){
            for (int f : factors[where[kv.first]]){
                int r = kv.first / f;
                if (f == kv.first){
                    continue;
                }
//                cerr << kv.first << " " << f << " " << r << endl;
                ans += (long long) (kv.second) * occ[f] * occ[f/r];
            }
        }
        for (pair<int, int> kv : occ){
            ans += (long long) (kv.second) * (kv.second - 1) * (kv.second - 2);
        }
        cout << ans << "\n";
    }
}