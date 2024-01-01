#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<int> a(n);
        map<int,vector<int>> mp;
        for (int i = 0; i < n; i++){
            cin >> a[i];
            a[i] %= k;
            if (a[i] == 0) a[i] += k;
            mp[a[i]].push_back(i+1);
        }
        for (auto it = prev(mp.end()); ; it--){
            for (int x : it->second){
                cout << x << " ";
            }
            if (it == mp.begin()) break;
        }
        cout << "\n";
    }
}