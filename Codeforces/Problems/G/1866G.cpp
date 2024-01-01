#include <bits/stdc++.h>

#define int long long
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n), d(n), r(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < n; i++){
        cin >> d[i]; r[i] = d[i] - i;
    }
    auto ok = [&](int z) -> bool{
        set<array<int, 2>> radii;
        vector<int> occ(a.begin(), a.end());
        for (int i = 0; i < n; i++){
            radii.insert({r[i], i});
        }
        for (int i = 0; i < n; i++){
            radii.erase({r[i], i});
            auto it = radii.lower_bound({-i});
            //put as much stuff as you can
            for (; it != radii.end(); it++){
                if (occ[i] + occ[(*it)[1]] >= z){
                    int offset = z - occ[i];
                    occ[i] = z;
                    occ[(*it)[1]] -= offset;
                    break;
                }
                else{
                    occ[i] += occ[(*it)[1]];
                    occ[(*it)[1]] = 0;
                }
            }
        }
        for (int i = 0; i < n; i++){
            if (occ[i] > z){
                return false;
            }
        }
        return true;
    };
    int lo = 0, hi = 1e18;
    while (lo < hi){
        int mid = (lo + hi) / 2;
        if (ok(mid)){
            hi = mid;
        }
        else{
            lo = mid+1;
        }
    }
    cout << lo << "\n";
}