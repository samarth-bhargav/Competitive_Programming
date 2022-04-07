#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mxN = 5e3+1;
const int M = 1e9+7;
int dp[mxN], dp1[mxN];

int power(long long x, unsigned int y, int p){
    int res = 1;
    x = x % p;
    if (x == 0) return 0;
    while (y > 0){
        if (y & 1)
            res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res%p;
}

int main() {
    freopen("poetry.in","r",stdin);
    freopen("poetry.out","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    memset(dp,0,sizeof(dp)); dp[0] = 1;
    memset(dp1,0,sizeof(dp1));
    int n,m,k; cin >> n >> m >> k;
    vector<int>syl;
    map<int,vector<int>>rhyme;
    map<char,int>occ;
    for (int i = 0; i < n; i++){
        int s,c; cin >> s >> c;
        rhyme[c].push_back(s);
        syl.push_back(s);
    }
    sort(syl.begin(),syl.end());
    for (int i = 0; i < m; i++){
        char c; cin >> c;
        occ[c]++;
    }
    for (int i = 0; i <= k; i++){
        int j = 0;
        while (j < syl.size() && i-syl[j]>=0){
            dp[i] = (dp[i] + (long long)dp[i-syl[j]] + M)%M;
            j++;
        }
    }
    for (auto &j : rhyme){
        for (auto &val : j.second){
            if (k-val >= 0){
                dp1[j.first] = (dp1[j.first]+(long long)dp[k-val]+M)%M;
            }
        }
    }
    ll ans = 1;
    for (auto &i : occ){
        ll temp = 0;
        for (auto & j : rhyme){
            if (dp1[j.first] != 0){
                temp = (temp + power(dp1[j.first],i.second,M) + M)%M;
            }
        }
        ans = (ans * temp + M)%M;
    }
    cout << (ans+M)%M << "\n";
}

