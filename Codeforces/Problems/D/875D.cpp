#include <bits/stdc++.h>

typedef long long ll;
#define int ll
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n), b(n);
        unordered_map<ll, int, custom_hash> freq;
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < n; i++){
            cin >> b[i];
        }
        for (int i = 0; i < n; i++){
            freq[(ll)(a[i]) * ll((n+1)) + b[i]]++;
        }
        int SQRT = (int)sqrt(2*n);
        ll bl = 0, og = 0;
        for (int i = 0; i < n; i++){
            if (a[i] > SQRT){
                for (int j = 1; j <= 2 * n / a[i]; j++){
                    int bj = a[i] * j - b[i];
                    if (bj <= n && bj >= 1){
                        og += freq[(ll)(j) * ll((n+1)) + bj];
                        if (j == a[i] && bj == b[i]){
                            og--;
                        }
                    }
                }
            }
            else{
                for (int j = 1; j <= SQRT; j++){
                    int bj = a[i] * j - b[i];
                    if (bj <= n && bj >= 1){
                        bl += freq[(ll)(j) * (ll)(n+1) + bj];
                        if (j == a[i] && bj == b[i]){
                            bl--;
                        }
                    }
                }
            }
        }
        bl /= 2;
        cout << og + bl << "\n";
    }
}