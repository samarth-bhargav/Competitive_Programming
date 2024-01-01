#include <bits/stdc++.h>

using namespace std;

const int M = 998244353;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
//        return x;
    }

    size_t operator()(array<int, 2> x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return (splitmix64(x[0] + FIXED_RANDOM) >> 1) + splitmix64(x[1] + FIXED_RANDOM);
//        return x[0] + x[1];
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> s(n);
        for (int i = 0; i < n; i++){
            cin >> s[i];
        }
        vector<int> prefix_sum(s.back()+1, 0);
        prefix_sum[0] = 0;
        int curr_elem = 0;
        for (int i = 1; i < prefix_sum.size(); i++){
            prefix_sum[i] = prefix_sum[i-1];
            if (s[curr_elem] == i){
                prefix_sum[i]++;
                curr_elem++;
            }
        }
        int sn = s.back();
        unordered_map<array<int,2>, int, custom_hash> dp;
        long long ans = 0;
        for (int x = 1; x <= s.back(); x++){
            int fl = sn / x, cl = (sn + x - 1) / x;
            if (dp.count({fl, cl})){
                ans += ((long long) x) * dp[{fl, cl}];
                ans %= M;
                continue;
            }
            if (sn / x == (sn + x - 1) / x){
                //x is a factor of sn
                int temp = 0;
                for (int i = fl; i <= s.back(); i += fl){
                    temp += prefix_sum[i] - prefix_sum[i-1];
                }
                dp[{fl, cl}] = temp;
                ans += ((long long) x) * temp;
                ans %= M;
            }
            else{
                int temp = 0;
                for (int lb = 0, res_ct = 0; lb <= s.back(); lb += fl, res_ct++){
                    if (res_ct == fl){
                        temp += prefix_sum[s.back()] - prefix_sum[lb-1];
                        break;
                    }
                    temp += prefix_sum[min(s.back(), lb + res_ct)] - prefix_sum[max(0, lb-1)];
                }
                dp[{fl, cl}] = temp;
                ans += ((long long) x) * temp;
                ans %= M;
            }
        }
        cout << ans << "\n";
    }
}