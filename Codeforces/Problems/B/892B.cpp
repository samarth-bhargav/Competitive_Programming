#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<vector<int>> a(n);
        vector<array<int, 2>> min_elems;
        vector<int> second_elems;
        for (int i = 0; i < n; i++){
            int m; cin >> m;
            a[i].resize(m, 0);
            for (int j = 0; j < m; j++){
                cin >> a[i][j];
            }
            sort(a[i].begin(), a[i].end());
            min_elems.push_back({a[i][0], a[i][1]});
            second_elems.push_back(a[i][1]);
        }
        sort(min_elems.begin(), min_elems.end());
        sort(second_elems.begin(), second_elems.end());
        cout << min_elems[0][0] + accumulate(second_elems.begin()+1, second_elems.end(), 0LL) << "\n";
    }
}