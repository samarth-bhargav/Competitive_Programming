#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n, q;
        cin >> n >> q;
        vector<int> factors;
        int old_n = n;
        for (int i = 2; i <= n; i++){
            if (n % i == 0){
                factors.push_back(old_n / i);
                while (n % i == 0){
                    n /= i;
                }
            }
        }
        n = old_n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(factors.begin(), factors.end());
        int num_f = (int) factors.size();
        vector<vector<long long>> sums(num_f);
        map<long long, int> occ;
        for (int k = 0; k < num_f; k++){
            int d = factors[k];
            for (int i = 0; i < d; i++){
                long long temp = 0;
                int j = i;
                do {
                    temp += a[j];
                    j = ((j + d) % n + n) % n;
                } while (j != i);
                sums[k].push_back(d*temp);
                occ[d*temp]++;
            }
        }
        cout << (--occ.end())->first << "\n";
//        if (n > 100000){
//            assert(false);
//        }
        for (int i = 0; i < q; i++){
            int x, y;
            cin >> x >> y; x--;
            int delta = y - a[x];
            for (int j = 0; j < num_f; j++){
                const int bg = ((x % factors[j]) + factors[j]) % factors[j];
                int curr = sums[j][bg];
                occ[curr]--;
                if (occ[curr] <= 0){
                    occ.erase(curr);
                }
                sums[j][bg] = curr + factors[j] * delta;
                occ[sums[j][bg]]++;
            }
            cout << (--occ.end())->first << "\n";
            a[x] = y;
        }
        //O(num_divisors * log(n) * q) = O(181 * log(2e5) * 2e5)
    }
}
