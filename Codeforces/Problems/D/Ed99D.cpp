/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n,x;
        cin >> n >> x;
        int x2 = x;
        vector <int> ar(n);
        vector <int> arcpy;
        deque <int> ar2;
        ar2.push_back(x);
        for (int i = 0; i < n; i++){
            cin >> ar[i];
            ar2.push_back(ar[i]);
        }
        arcpy = ar;
        if (is_sorted(ar.begin(), ar.end())){
            cout << 0 << "\n";
            continue;
        }
        sort(ar2.begin(), ar2.end());
        bool bad = false;
        int ans = 1e9;
        int cnt = 0;
        int store;
            while (!is_sorted(ar.begin(),ar.end())) {
                auto place = find(ar2.begin(), ar2.end(), x);
                if (place == ar2.end()) {
                    bad = true;
                    break;
                }
                int pos = place - ar2.begin();
                if (ar[pos] <= x) {
                    bad = true;
                    break;
                }
                swap(ar[pos], x);
                cnt++;
                if (bad) {
                    cout << (ans == 1e9 ? -1 : ans) << "\n";
                }
            }
    }
}