#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mxN = 1e5, M = 1e9+7;
int dp[mxN][4][4][4]; //dp[i][l][m][n]
//l is first letter of second to last substring
//m is first letter of last substring
//n ia the last letter of last substring

int32_t main(){
    string s;
    cin >> s;
    vector<int> a(s.length());
    for (int i = 0; i < s.length(); i++){
        if (s[i] == 'A') a[i] = 0;
        if (s[i] == 'G') a[i] = 1;
        if (s[i] == 'T') a[i] = 2;
        if (s[i] == 'C') a[i] = 3;
        if (s[i] == '?') a[i] = -1;
    }
    for (int l = 0; l < 4; l++){
        if (a[0] == -1){
            for (int m = 0; m < 4; m++){
                dp[0][l][m][m] = 1;
            }
        }
        else{
            dp[0][l][a[0]][a[0]] = 1;
        }
    }
    for (int i = 1; i < a.size(); i++){
        //adding on
        for (int l = 0; l < 4; l++){
            for (int m = 0; m < 4; m++){
                for (int n = 0; n < 4; n++){
                    for (int np = 0; np < 4; np++){
                        // make sure letter is valid
                        if (np != n && (a[i] == -1 || a[i] == n)){
                            dp[i][l][m][n] += dp[i-1][l][m][np];
                            dp[i][l][m][n] %= M;
                        }
                    }
                }
            }
        }
        //creating new
        for (int l = 0; l < 4; l++){
            for (int m = 0; m < 4; m++){
                if (a[i] == -1 || a[i] == m){
                    for (int lp = 0; lp < 4; lp++){
                        dp[i][l][m][m] += dp[i-1][lp][l][lp];
                        dp[i][l][m][m] %= M;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int l = 0; l < 4; l++){
        for (int m = 0; m < 4; m++){
            ans += dp[s.length()-1][m][l][m];
            ans %= M;
        }
    }
    cout << ans%M << "\n";
}