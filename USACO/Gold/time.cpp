//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

const int mxN = 1001; //max nodes
const int mxD = 1001; //max days

vector<int>adj[mxN];
vector<int>adj_reverse[mxN];
ll dp[mxD][mxN];
ll cost[mxN];

int n,m,c;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("time.in","r",stdin);
    freopen("time.out","w",stdout);
    cin >> n >> m >> c  ;
    for (int i = 0; i < n; i++){
        cin >> cost[i];
    }
    for (int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj_reverse[b].push_back(a);
    }
    memset(dp,-1,sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i < mxD; i++){
        for (int j = 0; j < mxN; j++){
            for (auto edge : adj_reverse[j]){
                if (dp[i-1][edge] != -1){
                    dp[i][j] = max(dp[i][j],dp[i-1][edge] + cost[j]);
                }
            }
        }
    }
    ll ans = -1;
    for (int i = 0; i <= 1000; i++){
        ans = max(ans,dp[i][0] - (ll)(c*pow(i,2)));
    }
    cout << ans << "\n";
}

