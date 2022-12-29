#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    int dp[m+1];
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    bool visited[m+1];
    for (int i = 0; i < n; i++){
        long long t, xp, y;
        cin >> t >> xp >> y;
        vector<vector<int>> chains;
        memset(visited, false, sizeof(visited));
        for (int j = 0; j <= m; j++) {
            int cnt = 0;
            int max_poss = -1;
            long long c = j;
            while (c <= m){
                if (visited[c]){
                    break;
                }
                visited[c] = true;
                if (dp[c] == -1){
                    if (max_poss != -1 && cnt - y <= max_poss){
                        dp[c] = i + 1;
                    }
                }
                else{
                    max_poss = cnt;
                }
                if (t == 1){
                    if (xp % 100000 == 0){
                        c = c + (xp / 100000);
                    }
                    else{
                        c = ceil(c + (xp / 100000.0));
                    }
                }
                else{
                    c = (c * xp + 99999) / 100000;
                }
                cnt++;
            }
            if (visited[j]) {
                continue;
            }
        }
    }
    for (int i = 1; i <= m; i++){
        cout << dp[i] << " ";
    }
    cout << "\n";
}
