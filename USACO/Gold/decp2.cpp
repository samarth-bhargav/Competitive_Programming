#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int MOD = 1e9+7;

template<const int MOD> struct Modular {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; }
    Modular():v(0) {}
    Modular(ll _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD); if (v < 0) v += MOD; }
    Modular& operator+=(const Modular& o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    Modular& operator-=(const Modular& o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    Modular& operator*=(const Modular& o) { v = int((ll)v*o.v%MOD); return *this; }
    Modular operator-() const { return Modular(-v); }
    Modular& operator++() { return *this += 1; }
    Modular& operator--() { return *this -= 1; }
    friend Modular operator+(Modular a, const Modular& b) { return a += b; }
    friend Modular operator-(Modular a, const Modular& b) { return a -= b; }
    friend Modular operator*(Modular a, const Modular& b) { return a *= b; }
    friend istream& operator>>(istream& inp, Modular& a) { ll x; inp >> x; a = Modular(x); return inp; }
    friend ostream& operator<<(ostream& out, const Modular& a) { out << a.v; return out; }
};
using Mint = Modular<MOD>;

typedef long long ll;

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    string s; cin >> s;
    s = "0" + s;
    vector<int> Rs, Bs;
    for (int i = 1; i <= n; i++){
        if (s[i] == 'B'){
            Rs.push_back(i);
            s[i] = 'R';
        }
        else if (s[i] == 'R'){
            Bs.push_back(i);
            s[i] = 'B';
        }
    }
    vector<int> prevR(n, 0), prevB(n, 0);
    for (int i = 1; i <= n; i++){
        {
            auto it = upper_bound(Rs.begin(), Rs.end(), i);
            if (it != Rs.begin()){
                prevR[i] = *(--it);
            }
        }
        {
            auto it = upper_bound(Bs.begin(), Bs.end(), i);
            if (it != Bs.begin()){
                prevB[i] = *(--it);
            }
        }
    }

    Mint dp[n+1]; dp[0] = 1;

    Mint pdp_odd[n+2], pdp_even[n+2];
    pdp_even[1] = 1;

    auto pdpo = [&](int l, int r){
        if (l > r){
            return Mint(0);
        }
        return pdp_odd[r+1] - pdp_odd[l];
    };

    auto pdpe = [&](int l, int r){
        if (l > r){
            return Mint(0);
        }
        return pdp_even[r+1] - pdp_even[l];
    };

    for (int i = 1; i <= n; i++){
        if (s[i] == 'B'){
            pdp_odd[i+1] = pdp_odd[i];
            pdp_even[i+1] = pdp_even[i];
            continue;
        }
        else{
            int pR = prevR[i-1];
            int pB = prevB[i-1];
            //everything is capped by pB: we never add a dp previous to dp[pB - (i - pB)]
            int thresh = pB - (i - pB);
            //add dp[i-2], dp[i-4], ...., dp[pR]
            if (((i - 2) % 2 + 2) % 2 == 0){
                dp[i] += pdpe(max(pR, thresh), i-2);
            }
            else{
                dp[i] += pdpo(max(pR, thresh), i-2);
            }
            //now, set pR to be the first R in the interval [pR - (i - pR + 1), pR - 1]
            while (true){
                if (pR < thresh){
                    break;
                }
                if (pR == 0){
                    break;
                }
                auto it1 = lower_bound(Rs.begin(), Rs.end(), pR - (i - pR + 1));
                if (*it1 <= pR - 1){
                    pR = *it1;
                    continue;
                }
                else{
                    //we add the dps from pr - (i - pr + 1) - 1, ...., nextR
                    auto ppRit = lower_bound(Rs.begin(), Rs.end(), pR - (i - pR + 1));
                    int ppR;
                    if (ppRit != Rs.begin()){
                        ppR = *(--ppRit);
                    }
                    else{
                        ppR = 0;
                    }
                    if (((pR - (i - pR + 1) - 1) % 2 + 2) % 2 == 0){
                        dp[i] += pdpe(max(ppR, thresh), pR - (i - pR + 1) - 1);
                    }
                    else{
                        dp[i] += pdpo(max(ppR, thresh), pR - (i - pR + 1) - 1);
                    }
                    pR = ppR;
                }
            }
        }
        if (s[i] == 'X'){
            dp[i] += dp[i-1];
        }
        pdp_odd[i+1] = pdp_odd[i];
        pdp_even[i+1] = pdp_even[i];
        if (i % 2 == 0){
            pdp_even[i+1] += dp[i];
        }
        else{
            pdp_odd[i+1] += dp[i];
        }
    }

    cout << dp[n] << "\n";

}
