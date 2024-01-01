#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        vector<int> occ(n+1, 0), affected(n+1, 0);
        for (int i = 0; i < n; i++){
            cin >> a[i];
            occ[a[i]]++;
        }
        long long ans = 0;
        vector<int> par(n+1, 0);
        for (int i = 1; i <= n; i++){
            if (!occ[i] && !affected[i]) continue;
            int total_muls = 0;
            for (int x = i; x <= n; x += i){
                total_muls += occ[x];
                affected[x] = true;
            }
            ans += (((long long)total_muls * (total_muls - 1)) / 2) * (1 - par[i]);
            int addend = 1 - par[i];
            for (int x = i; x <= n; x += i){
                par[x] += addend;
            }
        }
        cout << ((long long)n * (n-1) / 2) - ans << "\n";
    }
}