#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int mxN = 1001;
vector<pair<int,int>> edges;
vector<int> profit(mxN);
long long dp[mxN][501];

int main(){
    ifstream cin("time.in");
    ofstream cout("time.out");
    int n, m, c;
    cin >> n >> m >> c;
    for (int i = 0; i < n; i++){
        cin >> profit[i];
    }
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b; a--; b--;
        edges.emplace_back(a,b);
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 501; j++){
            dp[i][j] = -INF;
        }
    }
    dp[0][0] = 0;
    int from, to;
    for (int d = 1; d < 501; d++){
        for (auto & i : edges){
            from = i.first;
            to = i.second;
            if (dp[from][d-1] == -INF){
                continue;
            }
            else{
                dp[to][d] = max(dp[to][d], dp[from][d-1] + (profit[to] - (c*d*d - c*(d-1)*(d-1))));
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < 501; i++){
        ans = max(ans, dp[0][i]);
    }
    cout << ans << "\n";
}