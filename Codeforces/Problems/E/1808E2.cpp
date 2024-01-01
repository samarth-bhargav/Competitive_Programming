#include <bits/stdc++.h>

using namespace std;

#define int long long

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

int n, k, M;

vector<int> binpow(vector<int> &a, int pow){
    vector<int> res = {};
    vector<int> curr = a;
    while (pow){
        if (pow & 1){
            //convolute curr and res
            if (res.empty()){
                res = curr;
            }
            else{
                res = multiply(res, curr);
            }
        }
        //update curr
        vector<int> temp(k, 0);
        for (int i = 0; i < k; i++){
            for (int j = 0; j < k; j++){
                temp[(i + j) % k] += curr[i] * curr[j];
                temp[(i + j) % k] %= M;
            }
        }
        swap(temp, curr);
        pow >>= 1;
    }
    for (int i = 0; i < k; i++){
        res[i] = (res[i] + M) % M;
    }
    return res;
}

int binpow(int x, int pow){
    int curr = x, res = 1;
    while (pow){
        if (pow & 1){
            res *= curr; res %= M;
        }
        curr = (curr * curr) % M;
        pow >>= 1;
    }
    return (res + M) % M;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k >> M;
    int complement = 0;
    for (int s = 0; s < k; s++){
        //s is sum a_i mod k
        vector<int> dp(k, 0);
        for (int i = 0; i < k; i++){
            if ((2 * i % k) != s){
                dp[i] = 1;
            }
        }
        vector<int> res = binpow(dp, n);
        complement += res[s];
        complement %= M;
    }
    cout << ((binpow(k, n) - complement) % M + M) % M << "\n";
}
