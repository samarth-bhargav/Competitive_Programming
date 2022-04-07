/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}
int n,b,ar[250], depths[250], steps[250];
bool vis[250][250];
int ans = 1e5;
bool valid(int currboot, int location){
    if (depths[currboot] >= ar[location]){
        if (!vis[currboot][location]){
            return true;
        }
        return false;
    }
    return false;
}
void dfs(int currboot, int location){
    vis[currboot][location] = true;
    if (location == n-1){
        ans = min(ans, currboot);
    }
    for (int i = location; i <= n && i - location <= steps[currboot]; i++){
        if (valid(currboot, i)){
            dfs(currboot, i);
        }
    }
    for (int i = currboot+1; i < b; i++){
        if (valid(i, location)){
            dfs(i, location);
        }
    }
}

int main() {
    setIO("snowboots");
    cin >> n >> b;
    for (int i = 0; i < n; i++){
        cin >> ar[i];
    }
    for (int i = 0; i < b; i++){
        cin >> depths[i] >> steps[i];
    }
    dfs(0,0);
    cout << ans << "\n";
}
