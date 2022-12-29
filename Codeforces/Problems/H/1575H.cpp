#include <bits/stdc++.h>
using namespace std;

const int mxN = 501, INF = 1e9;
vector<vector<vector<int>>> dp;
int prefix_alt[mxN];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    dp = vector<vector<vector<int>>> (n+1, vector<vector<int>> (n-m+2, vector<int>(m+1)));
    string a_str, b_str; cin >> a_str >> b_str;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++){
        a[i] = (a_str[i] == '1' ? 1 : 0);
    }
    for (int i = 0; i < m; i++){
        b[i] = (b_str[i] == '1' ? 1 : 0);
    }

    int os = 0;
    for (int i = 1; i < m; i++){
        if (vector<int>(b.begin(), b.begin()+i) == vector<int>(b.end()-i, b.end())){
            os = i;
        }
    }
    for (int i = 0; i < m-1; i++){
        //given first i characters, add alternate character, and find prefix length
        int best_len = 0;
        for (int p_strt = 0; p_strt < i+2; p_strt++){
            //would consider [p_strt, i+1]
            bool bad = false;
            //we want [p_strt, i+1] to equal [0, i+1-p_strt]
            for (int j = p_strt; j <= i; j++){
                if (b[j-p_strt] != b[j]){
                    bad = true;
                    break;
                }
            }
            if ((~b[i+1] & 1) != b[i-p_strt+1]){
                bad = true;
            }
            if (!bad){
                best_len = max(best_len, i - p_strt + 2);
            }
        }
        prefix_alt[i] = best_len;
    }
    map<int, vector<int>> gen_len;
    for (int i = 0; i < m-1; i++){
        gen_len[prefix_alt[i]].push_back(i+1);
    }
    gen_len[0].push_back(0);

    //initialize dp array
    for (int i = 0; i < n; i++){
        for (int k = 0; k <= n-m+1; k++){
            for (int p = 0; p <= m; p++){
                dp[i][k][p] = INF;
            }
        }
    }

    if (b.size() == 1){
        dp[0][1][0] = (a[0] ^ b[0] ? 1 : 0);
        dp[0][0][0] = (a[0] ^ b[0] ? 0 : 1);
    }
    else{
        dp[0][0][0] = (a[0] ^ b[0] ? 0 : 1);
        dp[0][0][1] = (a[0] ^ b[0] ? 1 : 0);
    }

    for (int i = 1; i < n; i++){
        for (int k = 0; k <= n-m+1; k++){
            if (k > 0){
                dp[i][k][os] = min(dp[i][k][os], dp[i-1][k-1][m-1] + (b[m-1] ^ a[i]));
            }
            for (int p = 0; p <= m; p++){
                //add same prefix
                if (p > 0){
                    dp[i][k][p] = min(dp[i][k][p], dp[i-1][k][p-1] + (b[p-1] ^ a[i]));
                }
                //add opposite number
                //you have prefix (b[0], b[1], . . . b[elem-1]). add opposite of b[elem] to get prefix of length p
                for (int elem : gen_len[p]){
                    dp[i][k][p] = min(dp[i][k][p], dp[i-1][k][elem] + (b[elem] == a[i]));
                }
//                cout << "i : " << i << " k: " << k << " p: " << p << " dp[i][k][p]: " << dp[i][k][p] << "\n";
            }
        }
    }
    for (int k = 0; k <= n-m+1; k++){
        int ans = INF;
        for (int p = 0; p < m; p++){
            ans = min(ans, dp[n-1][k][p]);
        }
        cout << (ans == INF ? -1 : ans) << " ";
    }
    cout << "\n";
}