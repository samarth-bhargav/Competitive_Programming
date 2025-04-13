#include <bits/stdc++.h>

using namespace std;

#define int long long

int mxL = 1e6+1;
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    map<int,int> freq;
    for (int i = 0; i < n; i++){
        freq[a[i]]++;
    }

    int q; cin >> q;
    vector<array<int, 3>> queries(q);
    for (int i = 0; i < q; i++){
        cin >> queries[i][0] >> queries[i][1];
        queries[i][2] = i;
    }
    sort(queries.begin(), queries.end(), [&](array<int, 3> a, array<int, 3> b){
       return (a[0] * b[1] > a[1] * b[0]);
    });

    int sum_left = 0;
    int sum_right = accumulate(a.begin(), a.end(), 0LL);
    int num_left = 0;
    int num_right = n;

    vector<array<int, 2>> sums(mxL);
    sums[0] = {sum_left, sum_right};
    for (int i = 1; i < mxL; i++){
        num_left += freq[i-1];
        num_right -= freq[i-1];
        sum_left += num_left;
        sum_right -= num_right;
        sums[i] = {sum_left, sum_right};
    }

    int c = 0;
    vector<int> ans(q, INF);
    ans[queries[c][2]] = sums[0][1] * queries[c][1];

    for (int i = 1; i < mxL; i++){
        if (i == -1) continue;
        if (sums[i][0] * queries[c][0] + sums[i][1] * queries[c][1] > ans[queries[c][2]]){
            c++; i -= 2;
            if (c >= q) break;
            continue;
        }
        ans[queries[c][2]] = sums[i][0] * queries[c][0] + sums[i][1] * queries[c][1];
    }
    for (int i = 0; i < q; i++){
        cout << ans[i] << "\n";
    }
}