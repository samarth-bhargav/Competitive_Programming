#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const ll INF = 1e18;
const int mxN = 500;

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    ll pref[n+1]; pref[0] = 0;
    for (int i = 1; i <= n; i++){
        pref[i] = pref[i-1] + a[i-1];
    }
    for (int idx = 0; idx < n; idx++){
        vector<ll> cum;
        cum.reserve(2*n);
        ll ans = INF;
        ll sum = 0;
        for (int i = idx+1; i < n; i++){
            sum += a[i];
            cum.push_back(sum);
        }
        sum = 0;
        for (int i = idx-1; i >= 0; i--){
            sum += a[i];
            cum.push_back(sum);
        }
        sort(cum.begin(), cum.end());
        //iterate over all subarrays containing idx
        for (int i = 0; i <= idx; i++){
            for (int j = idx; j < n; j++){
                sum = pref[j+1] - pref[i];
                auto it = lower_bound(cum.begin(), cum.end(), sum);
                auto it2 = it;
                if (it2 != cum.begin()){
                    it2--;
                }
                if (it != cum.end()){
                    ans = min(ans, abs(*it - sum));
                }
                if (it2 != cum.end()){
                    ans = min(ans, abs(*it2 - sum));
                }
            }
        }
        cout << ans << "\n";
    }
}
