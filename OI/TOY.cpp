#include <bits/stdc++.h>

using namespace std;

vector<int> factors(int n){
    vector<int> ret;
    for (int i = 1; i * i <= n; i++){
        if (n % i == 0){
            ret.push_back(i);
            if (i * i != n){
                ret.push_back(n / i);
            }
        }
    }
    ret.erase(find(ret.begin(), ret.end(), 1));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    if (n == 1){
        cout << 1 << "\n";
        cout << 0 << "\n";
        return 0;
    }
    vector<int> f = factors(n);
    int m = f.size();
    sort(f.begin(), f.end());

    unordered_map<int,int> fac_to_idx;
    for (int i = 0; i < m; i++){
        fac_to_idx[f[i]] = i;
    }

    vector<vector<vector<int>>> dp(m, vector<vector<int>>(m, vector<int>()));
    vector<vector<int>> cum_dp(m, vector<int>());

    for (int i = 0; i < m; i++){
        dp[i][i] = {f[i]-1};
        cum_dp[i] = {f[i]-1};
    }

    for (int i = 1; i < m; i++){
        for (int j = 0; j < i; j++){
            //i is prod, j is last fac
            if (f[i] % f[j] != 0) continue;
            dp[i][j] = cum_dp[fac_to_idx[f[i] / f[j]]];
            for (int k = 0; k < (int)dp[i][j].size(); k++){
                dp[i][j][k] += f[j] - 1;
                cum_dp[i].push_back(dp[i][j][k]);
            }
        }
        sort(cum_dp[i].begin(), cum_dp[i].end());
        cum_dp[i].erase(unique(cum_dp[i].begin(), cum_dp[i].end()), cum_dp[i].end());
    }

//    for (int i = 0; i < m; i++){
//        cout << f[i] << "\n";
//        for (int j = 0; j < cum_dp[i].size(); j++){
//            cout << cum_dp[i][j] << " ";
//        }
//        cout << "\n";
//    }
    cout << cum_dp[m-1].size() << "\n";
    for (int i = 0; i < (int)cum_dp[m-1].size(); i++){
        cout << cum_dp[m-1][i] << " ";
    }
    cout << "\n";
}