#include <bits/stdc++.h>

using namespace std;

#define int long long

int LOG = 62;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    const int M = 998244353;
    const int inv2 = 499122177;
    vector<int> pow2(2 * LOG);

    auto binpow = [&](int base, int exp){
        int curr = base;
        int res = 1LL;
        while (exp){
            if (exp & 1LL){
                res = (res * curr) % M;
            }
            curr = (curr * curr) % M;
            exp >>= 1;
        }
        return res;
    };
    int n, m;

    for (int i = 0; i < pow2.size(); i++){
        pow2[i] = binpow(2, i);
    }

    vector<vector<int>> dp(LOG);

    dp[0] = {1};
    for (int i = 1; i < LOG; i++){
        dp[i] = vector<int>(2 * i + 1);
        for (int j = 0; j < dp[i-1].size(); j++){
            dp[i][j] = 2 * dp[i-1][j];
            dp[i][j] = (dp[i][j] % M + M) % M;
        }
        //find all going through root node
        for (int l = 0; l <= 2 * i; l++){
            for (int k = 0; k <= l; k++){
                if (k > i || l-k > i) continue;
                //k edges in left branch, l - k edges in right branch
                dp[i][l] += (k == 0 ? 1 : pow2[k-1]) * (l-k == 0 ? 1 : pow2[l-k-1]);
                dp[i][l] = (dp[i][l] % M + M) % M;
            }
        }
    }

    int t; cin >> t;
    while (t--){
        cin >> n >> m;
        if (n == 1){
            cout << m * (m + 1) / 2 << "\n";
            continue;
        }
        int nodes = 1, height = 0;
        while (true){
            if (nodes * 2 - 1 >= n) break;
            nodes *= 2; height++;
        }
//        cerr << height << endl;
        vector<int> p(2 * LOG);
        for (int i = 0; i < dp[height-1].size(); i++){
            p[i] += dp[height-1][i];
            p[i] = (p[i] % M + M) % M;
        }
        int llayer_start = 1LL << height;
        int start = llayer_start;
        int bottom_nodes = n - start + 1;
//        cerr << "bottom: " << bottom_nodes << endl;
        for (int i = LOG-1; ~i; i--){
            if ((bottom_nodes >> i) & 1LL){
                //process start
                int curr_node = start;
                int length = 0;
                p[0] += pow2[i]; p[0] %= M;
                int last_node = curr_node;
                curr_node >>= 1; length++;

                while (curr_node){
                    //find height of subtree
                    int rt = curr_node;
                    if (rt * 2 == last_node)
                        rt = rt * 2 + 1;
                    else
                        rt = rt * 2;
                    p[length] += pow2[i]; p[length] %= M;
                    //find height of subtree at rt
                    int lb = rt, ub = rt;
                    int curr_branch = 1;
                    while (true){
                        if (lb > n) break;
                        if (ub <= n){
                            //check if it's in the last layer
                            if (lb >= llayer_start){
                                int addend = pow2[curr_branch-1] * pow2[i];
                                addend %= M;
                                addend = (addend * inv2) % M;
                                p[curr_branch + length] += addend;
                                p[curr_branch + length] %= M;
                                break;
                            }
                            else{
                                p[curr_branch + length] += (pow2[curr_branch-1] * pow2[i]) % M;
                                p[curr_branch + length] %= M;
                            }
                        }
                        else{
                            //incomplete
                            int num_nodes = max(0LL, n - lb + 1);
                            int addend = ((num_nodes) % M) * pow2[i];
                            addend %= M;
                            addend = (addend * inv2) % M;
                            p[curr_branch + length] += addend;
                            p[curr_branch + length] %= M;
                            break;
                        }
                        lb = 2 * lb; ub = 2 * ub + 1;
                        curr_branch++;
                    }
                    last_node = curr_node;
                    curr_node >>= 1; length++;
                }
                start += (1LL << i);
            }
        }

//        int sum = 0;
//        for (int i = 0; i < p.size(); i++){
//            sum += p[i]; sum %= M;
//            cerr << p[i] << " ";
//        }
//        cerr << endl;
//
//        cerr << "SUM: " << (sum%M + M) % M << endl;

        int ans = 0;

        vector<int> mxpow(m+1, 1);

        for (int i = 0; i < min(n, (int)p.size()); i++){
            int mpow = binpow(m, n - (i+1));
            for (int j = 0; j <= m; j++){
                mxpow[j] = (mxpow[j] * j) % M;
            }
            for (int mx = 1; mx <= m; mx++){
                int addend = mpow * mxpow[mx];
                addend %= M;
                addend -= mpow * mxpow[mx-1];
                addend %= M;
                addend = (addend * p[i]) % M;
                addend = (addend * mx) % M;
                ans = (ans + addend) % M;
            }
        }

        cout << (ans % M + M) % M << "\n";
    }
}