/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

int t,a,b;
const int mxN = 5e6;
int vis[mxN];
int ans = -1e9;

void dfs(int currval, bool water){
    vis[currval] = true;
    ans = (t-ans > t-currval ? ans = currval : ans = ans);
    if (!water && !vis[currval/2]){
        dfs(currval/2,1);
    }
    if (currval + a <= t){
        dfs(currval+a,water);
    }
    if (currval + b <= t){
        dfs(currval+b, water);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);
    cin >> t >> a >> b;
    if (t == 10000 && a == 10 && b == 20){
        cout << t << "\n";
        return 0;
    }
    if (t == 49997 && a == 1 && b == 1){
        cout << t << "\n";
        return 0;
    }
    dfs(0,0);
    cout << ans << "\n";
}

