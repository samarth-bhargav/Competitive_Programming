#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int mxN = 3e5;
const ll INF = 1e18;

vector<int> add(mxN), sub(mxN);
int rmqA[mxN][20], rmqS[mxN][20];
int dp_pref[mxN], dp_suf[mxN];
int add_pref[mxN+1], sub_pref[mxN+1];

int minQry(int a, int b, bool x){
    if (a > b) return INF;
    int d = (b - a + 1);
    int ans = INF;
    for (int l = 0; l < 20; l++){
        if ((d >> l) & 1){
            if (x){ans = min(ans, rmqA[a][l]);}
            else{ans = min(ans, rmqS[a][l]);}
            a += (1 << l);
        }
    }
    return ans;
}


int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        add_pref[0] = 0;
        sub_pref[0] = 0;
        for (int i = 0; i < n; i++){
            add[i] = a[i] + i;
            sub[i] = a[i] - i;
            add_pref[i+1] = add_pref[i] + add[i];
            sub_pref[i+1] = sub_pref[i] + sub[i];
            rmqA[i][0] = add[i];
            rmqS[i][0] = sub[i];
        }
        for (int l = 1; l < 20; l++){
            for (int i = 0; i < n; i++){
                if (i + (1 << l) - 1 >= n){
                    rmqA[i][l] = INF;
                    rmqS[i][l] = INF;
                    continue;
                }
                rmqA[i][l] = min(rmqA[i][l-1], rmqA[i+(1 << (l-1))][l-1]);
                rmqS[i][l] = min(rmqS[i][l-1], rmqS[i+(1 << (l-1))][l-1]);
            }
        }
        dp_pref[0] = 0;
        dp_suf[n-1] = 0;
        for (int i = 1; i < n; i++){
            //binary search until a[j] - j <= a[i] - i
            if (a[i] > a[i-1]){
                dp_pref[i] = dp_pref[i-1];
                continue;
            }
            int lo = 0, hi = i-1;
            while (lo < hi){
                int mid = (lo + hi) / 2;
                if (minQry(mid, i-1, false) >= sub[i]){
                    hi = mid;
                }
                else{
                    lo = mid+1;
                }
            }
            dp_pref[i] = (sub_pref[i] - sub_pref[hi]) - (sub[i] * (i - hi)) + dp_pref[hi];
            if (hi + sub[i] < 0){
                int diff = ((i - a[i]) - hi);
                dp_pref[i] -= (diff * (diff+1)) / 2;
            }
        }
        for (int i = n-2; ~i; i--){
            //binary search until a[j] - j <= a[i] - i
            if (a[i] > a[i+1]){
                dp_suf[i] = dp_suf[i+1];
                continue;
            }
            int lo = i+1, hi = n-1;
            while (lo < hi){
                int mid = (lo + hi + 1) / 2;
                if (minQry(i+1, mid, true) >= add[i]){
                    lo = mid;
                }
                else{
                    hi = mid-1;
                }
            }
            dp_suf[i] = (add_pref[hi+1] - add_pref[i+1]) - (add[i] * (hi - i)) + dp_suf[hi];
            if (-hi + add[i] < 0){
                int diff = hi - add[i];
                dp_suf[i] -= (diff * (diff + 1)) / 2;
            }
        }
        int ans = INF;
        for (int i = 0; i < n; i++){
            ans = min(ans, dp_pref[i] + dp_suf[i] + a[i]);
        }
        cout << ans << "\n";
    }
}
