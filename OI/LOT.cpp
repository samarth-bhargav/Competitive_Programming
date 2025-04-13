#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, l; cin >> n >> l;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int q; cin >> q;
    vector<pair<int,int>> queries_with_idx;
    for (int i = 0; i < q; i++){
        int k; cin >> k;
        queries_with_idx.emplace_back(k, i);
    }
    sort(queries_with_idx.begin(), queries_with_idx.end());
    vector<int> queries, idx_to_real;
    for (int i = 0; i < q; i++){
        queries.push_back(queries_with_idx[i].first);
        idx_to_real.push_back(queries_with_idx[i].second);
    }
    //precompute first greater so no std::lower_bound
    int query_threshold = queries.back()+1;
    vector<int> first_greater(query_threshold);
    for (int i = 0; i < query_threshold; i++){
        first_greater[i] = lower_bound(queries.begin(), queries.end(), i) - queries.begin();
    }
    vector<vector<int>> pref(n-l+1, vector<int> (q, 0));
    for (int offset = 1; offset < n; offset++){
        //out of bounds
        if (l-1 + offset >= n){
            break;
        }
        //initialize
        int last = 0;
        for (int i = 0; i < l; i++){
            last += (a[i] != a[i + offset]);
        }
        int idx;
        if (last < query_threshold){
            idx = first_greater[last];
            pref[0][idx]++;
            pref[offset][idx]++;
        }
        for (int j = 1; j+l-1+offset < n; j++){
            last -= (a[j-1] != a[j-1+offset]);
            last += (a[j+l-1] != a[j+l-1+offset]);
            if (last < query_threshold){
                idx = first_greater[last];
                pref[j][idx]++;
                pref[j+offset][idx]++;
            }
        }
    }
    for (int i = 0; i < n-l+1; i++){
        for (int j = 1; j < q; j++){
            pref[i][j] += pref[i][j-1];
        }
    }
    vector<vector<int>> ans(n-l+1, vector<int>(q, 0));
    for (int i = 0; i < n-l+1; i++){
        for (int j = 0; j < q; j++){
            ans[i][idx_to_real[j]] = pref[i][j];
        }
    }
    for (int i = 0; i < q; i++){
        for (int j = 0; j < n-l+1; j++){
            cout << ans[j][i] << " ";
        }
        cout << "\n";
    }
}