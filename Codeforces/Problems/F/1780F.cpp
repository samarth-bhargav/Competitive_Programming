#include <bits/stdc++.h>

using namespace std;

#define int long long
const int mxN = 3e5;
vector<bool> is_prime(mxN+1, true);
vector<int> primes;

void sieve(){
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= mxN; i++){
        if (is_prime[i] && (long long)i * i <= mxN){
            for (int j = i*i; j <= mxN; j += i){
                is_prime[j] = false;
            }
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    sieve();
    for (int i = 0; i <= mxN; i++){
        if (is_prime[i]) primes.push_back(i);
    }
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<vector<int>> divisor_idx(mxN+1);
    unordered_map<int,int> factor_sz;
    for (int i = 0; i < a.size(); i++){
        int mult = 1;
        int curr_val = a[i];
        vector<int> facs_used;
        for (int p = 0; p < primes.size() && primes[p] * primes[p] <= a[i]; p++){
            if (curr_val % primes[p] == 0){
                facs_used.push_back(primes[p]);
                mult *= primes[p];
                while (curr_val % primes[p] == 0){
                    curr_val /= primes[p];
                }
            }
        }
        if (curr_val != 1) facs_used.push_back(curr_val);
        for (int j = 1; j < (1 << (facs_used.size())); j++){
            int fac = 1;
            for (int b = 0; b < facs_used.size(); b++){
                if (j & (1 << b)) fac *= facs_used[b];
            }
            divisor_idx[fac].push_back(i);
            if (__builtin_popcount(j) & 1){
                factor_sz[fac] = 1;
            }
            else{
                factor_sz[fac] = -1;
            }
        }
    }
    int ans = 0;
    for (int i = 2; i <= mxN; i++){
        sort(divisor_idx[i].begin(), divisor_idx[i].end());
        int temp = -(divisor_idx[i].size() * ((int)(divisor_idx[i].size()) - 1) / 2);
        for (int j = 0; j < divisor_idx[i].size(); j++){
            temp -= divisor_idx[i][j] * (divisor_idx[i].size() - j - 1);
            temp += divisor_idx[i][j] * j;
        }
        ans += factor_sz[i] * temp;
    }
    cout << n * (n-1) * (n-2) / 6 - ans << "\n";
}