#include <bits/stdc++.h>
using namespace std;

const int mxN = 3e5;
const int mxL = 20;
const long long INF = 1e18;
long long RMQ[2][mxN][mxL];

long long qry(int l, int r, int p){
    long long ret = -INF;
    int diff = r - l + 1;
    for (int bit = 0; bit < mxL; bit++){
        if ((diff >> bit) & 1){
            ret = max(ret, RMQ[p][l][bit]);
            l += (1 << bit);
        }
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
//        if (n == 1 && a[0] == 0){
//            cout << 1 << "\n";
//            continue;
//        }
        long long pref_diff[2][n];
        pref_diff[0][0] = 0;
        pref_diff[1][0] = 0;
        for (int i = 0; i < n-1; i++){
            if (i % 2 == 0){
                pref_diff[0][i+1] = (i-1 == -1 ? 0 : pref_diff[0][i-1]) + (a[i] - a[i+1]);
                pref_diff[1][i+1] = -INF;
            }
            else{
                pref_diff[0][i+1] = -INF;
                pref_diff[1][i+1] = pref_diff[1][i-1] + (a[i] - a[i+1]);
            }
        }
        array<map<long long, vector<int>>, 2> mps;
        for (int i = 1; i < n; i++){
            mps[0][pref_diff[0][i]].push_back(i);
            mps[1][pref_diff[1][i]].push_back(i);
        }
        for (int i = 0; i < n; i++){
            RMQ[1][i][0] = pref_diff[1][i];
            RMQ[0][i][0] = pref_diff[0][i];
        }
        for (int L = 1; L < mxL; L++){
            for (int i = 0; i < n; i++){
                if (i + (1 << L) >= n){
                    RMQ[1][i][L] = -INF;
                    RMQ[0][i][L] = -INF;
                    continue;
                }
                RMQ[1][i][L] = max(RMQ[1][i][L-1], RMQ[1][i + (1 << (L-1))][L-1]);
                RMQ[0][i][L] = max(RMQ[0][i][L-1], RMQ[0][i + (1 << (L-1))][L-1]);
            }
        }
        long long ans = 0;
        for (int i = 0; i < n; i++){
            // a[i] - a[i+1] <= 0
            // a[i] - a[i+1] + a[i+2] - a[i+3] <= 0 etc.
            int b1, b2;
            int lo = i, hi = n-1;
            while (lo < hi){
                int mid = (lo + hi + 1) / 2;
                if (qry(i, mid, (i%2)) - (i - 1 < 0 ? 0 : pref_diff[(i%2)][i-1]) <= 0){
                    lo = mid;
                }
                else{
                    hi = mid-1;
                }
            }
            b1 = lo;
            //a[i] - a[i+1] + a[i+2] >= 0
            //a[i+1] - a[i+2] <= a[i]
            //a[i+1] - a[i+2] + a[i+3] - a[i-4] <= a[i] etc.
            lo = i+1; hi = n-1;
            while (lo < hi){
                int mid = (lo + hi + 1) / 2;
                if (qry(i, mid, ((i+1)%2)) - pref_diff[(i+1)%2][i < 0 ? 0 : i] <= a[i]){
                    lo = mid;
                }
                else{
                    hi = mid-1;
                }
            }
            b2 = lo;
            int final_boundary = min(b1, b2);
            //we want to count how many satisfy
            //a[i] - a[i+1] + a[i+2] - a[i+3] = 0
            //pref[smth] - pref[i-2] = 0
            //pref[smth] = pref[i-2]
            auto it1 = upper_bound(mps[i%2][pref_diff[i%2][(i - 1 < 0 ? 0 : i - 1)]].begin(),
                                   mps[i%2][pref_diff[i%2][(i - 1 < 0 ? 0 : i - 1)]].end(), final_boundary);
            auto it2 = lower_bound(mps[i%2][pref_diff[i%2][(i - 1 < 0 ? 0 : i - 1)]].begin(),
                                   mps[i%2][pref_diff[i%2][(i - 1 < 0 ? 0 : i - 1)]].end(), i+1);
            ans += (it1 - it2);
            //a[i] - a[i+1] + a[i+2] - a[i+3] + a[i+4] = 0
            //a[i+1] - a[i+2] + a[i-3] - a[i+4] = a[i]
            //pref[smth] - pref[i-1] = a[i]
            //pref[smth] = a[i] + pref[i-1]
            it1 = upper_bound(mps[(i+1)%2][pref_diff[(i+1)%2][i] + a[i]].begin(),
                              mps[(i+1)%2][pref_diff[(i+1)%2][i] + a[i]].end(), final_boundary);
            it2 = lower_bound(mps[(i+1)%2][pref_diff[(i+1)%2][i] + a[i]].begin(),
                              mps[(i+1)%2][pref_diff[(i+1)%2][i] + a[i]].end(), i-1);
            ans += (it1 - it2);
        }
        //consider entire array
        cout << ans + (a[0] == 0) << "\n";
    }
}

