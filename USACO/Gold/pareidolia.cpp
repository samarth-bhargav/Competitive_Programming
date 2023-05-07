#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e9;

array<int, 2> minar(array<int, 2> a, array<int, 2> b){
    if (a[0] > b[0]) return a;
    else if (b[0] > a[0]) return b;
    return a[1] < b[1] ? a : b;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
    int n = s.size();
    vector<int> c(n);
    for (int i = 0; i < n; i++){
        cin >> c[i];
    }

    vector<vector<array<int, 2>>> dp(n, vector<array<int, 2>> (6)); // '', 'b', 'be', 'bes', 'bess', 'bessi'
    //initialization
    if (s[0] == 'b'){
        dp[0][0] = {0, 0};
        dp[0][1] = {0, 0};
        for (int i = 2; i < 6; i++){
            dp[0][i] = {0, INF};
        }
    }
    else{
        dp[0][0] = {0, 0};
        for (int i = 1; i < 6; i++){
            dp[0][i] = {0, INF};
        }
    }
    for (int i = 1; i < n; i++){
        if (s[i] == 'b'){
            dp[i][0] = dp[i-1][0]; //ignore b
            dp[i][1] = dp[i-1][0]; //just to get a b in existence, doesn't req any cost
            for (int j = 2; j < 6; j++){
                //need to remove the b to cont pattern
                dp[i][j] = {dp[i-1][j][0], dp[i-1][j][1] + c[i]};
            }
        }
        else if (s[i] == 'e'){
            if (dp[i-1][5][1] < INF){
                //start new
                dp[i][0] = minar(dp[i-1][0], {dp[i-1][5][0]+1, dp[i-1][5][1]});
            }
            else{
                dp[i][0] = dp[i-1][0]; //ignore e
            }
            dp[i][1] = {dp[i-1][1][0], dp[i-1][1][1] + c[i]};
            dp[i][2] = minar({dp[i-1][2][0], dp[i-1][2][1] + c[i]}, {dp[i-1][1][0], dp[i-1][1][1]});
            for (int j = 3; j < 6; j++){
                //need to remove the e to cont pattern
                dp[i][j] = {dp[i-1][j][0], dp[i-1][j][1] + c[i]};
            }
        }
        else if (s[i] == 's'){
            dp[i][0] = dp[i-1][0];
            dp[i][1] = {dp[i-1][1][0], dp[i-1][1][1] + c[i]};
            dp[i][2] = {dp[i-1][2][0], dp[i-1][2][1] + c[i]};
            dp[i][3] = minar({dp[i-1][3][0], dp[i-1][3][1] + c[i]}, {dp[i-1][2][0], dp[i-1][2][1]});
            dp[i][4] = minar({dp[i-1][4][0], dp[i-1][4][1] + c[i]}, {dp[i-1][3][0], dp[i-1][3][1]});
            dp[i][5] = {dp[i-1][5][0], dp[i-1][5][1] + c[i]};
        }
        else if (s[i] == 'i'){
            dp[i][0] = dp[i-1][0];
            dp[i][1] = {dp[i-1][1][0], dp[i-1][1][1] + c[i]};
            dp[i][2] = {dp[i-1][2][0], dp[i-1][2][1] + c[i]};
            dp[i][3] = {dp[i-1][3][0], dp[i-1][3][1] + c[i]};
            dp[i][4] =  {dp[i-1][4][0], dp[i-1][4][1] + c[i]};
            dp[i][5] = minar({dp[i-1][5][0], dp[i-1][5][1] + c[i]}, {dp[i-1][4][0], dp[i-1][4][1]});
        }
        else{
            dp[i][0] = dp[i-1][0];
            for (int j = 1; j < 6; j++){
                dp[i][j] = {dp[i-1][j][0], dp[i-1][j][1] + c[i]};
            }
        }
    }
    cout << dp[n-1][0][0] << "\n" << dp[n-1][0][1];
}
