#include <bits/stdc++.h>
using namespace std;

#define int long long
const int M = 998244353;
const int mxN = 1e5+1;
int fact[mxN];

long long binpow(long long a, long long b) {
    a %= M;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}
long long nCr(int a, int b){
    long long inter = (fact[a] * binpow(fact[b], M-2) % M);
    return ((inter * binpow(fact[a-b], M-2)) % M + M) % M;
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    fact[0] = 1;
    fact[1] = 1;
    for (int i = 2; i < mxN; i++){
        fact[i] = ((fact[i-1] * i) % M + M) % M;
    }
//    cerr << nCr(5, 2) << "\n";
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> num_zr(n, 0), num_zl(n, 0);
        //num_zr[i] = boundary between i-1 and i
        //num_zl[i] = boundary between i+1 and i
        for (int i = 0; i < n; ){
            if (a[i] == 0){
                //theres a chain of zeroes starting at that point
                int p = i;
                while (p < n && a[p] == 0){
                    num_zr[i]++;
                    p++;
                }
                i = p;
            }
            else{
                i++;
            }
        }
        for (int i = n-1; ~i; ){
            if (a[i] == 0){
                int p = i;
                while (~p && a[p] == 0){
                    num_zl[i]++;
                    p--;
                }
                i = p;
            }
            else{
                i--;
            }
        }
        //two ptrs
        int l = -1, r = n, suml = 0, sumr = 0;
        vector<int> blcks;
        while (l < r){
            if (suml == sumr){
                if (l + num_zr[l+1] >= r - num_zl[r-1]){
                    //continuous segment of 0s of sz num_zr[l+1]
                    //will have 2^(num_zr[l+1] - 1) options
                    blcks.push_back(binpow(2, num_zr[l+1]-1 + (l != -1) + (r != n)) - !(l == -1 && r == n));
                    break;
                }
                if (l == -1 && r == n){
                    blcks.push_back(nCr(num_zr[l+1] + num_zl[r-1], num_zr[l+1]));
                }
                else{
                    blcks.push_back(nCr(num_zr[l+1]+num_zl[r-1]+2, num_zr[l+1] + 1) - 1);
                }
                l += (num_zr[l+1]+1);
                suml += a[l];
                r -= (num_zl[r-1]+1);
                sumr += a[r];
                continue;
            }
            if (suml < sumr){
                l++; suml += a[l];
            }
            else{
                r--; sumr += a[r];
            }
        }
        int ans = blcks[0];
        for (int i = 1; i < blcks.size(); i++){
            ans = ((ans * blcks[i] + ans) % M + M) % M;
        }
        cout << ans << "\n";
    }
}
