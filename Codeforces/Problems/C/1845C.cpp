#include <bits/stdc++.h>

using namespace std;

const int mxN = 3e5;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        string s; cin >> s;
        int n = s.size();
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            a[i] = s[i] - '0';
        }
        vector<int> occ[10];
        for (int i = 0; i < n; i++){
            occ[a[i]].push_back(i);
        }
        map<int,int> first_occ;
        for (int i = 0; i < n; i++){
            if (!first_occ.count(a[i])){
                first_occ[a[i]] = i;
            }
        }
        int m; cin >> m;
        string ls; cin >> ls;
        string rs; cin >> rs;
        vector<int> l(m), r(m);
        for (int i = 0; i < m; i++){
            l[i] = ls[i] - '0';
            r[i] = rs[i] - '0';
        }
        bool good = false;
        int idx = -1;
        for (int i = l[0]; i <= r[0]; i++){
            if (first_occ.count(i)){
                idx = max(idx, first_occ[i]);
            }
            else{
                good = true;
                break;
            }
        }
        if (good){
            cout << "YES\n";
        }
        for (int i = 1; i < m; i++){
            if (good) break;
            int tempidx = idx;
            for (int j = l[i]; j <= r[i]; j++){
                auto it = upper_bound(occ[j].begin(), occ[j].end(), idx);
                if (it == occ[j].end()){
                    good = true;
                    break;
                }
                tempidx = max(tempidx, *it);
            }
            idx = tempidx;
        }
        if (good){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
}