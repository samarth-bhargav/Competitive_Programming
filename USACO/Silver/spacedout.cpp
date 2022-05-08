/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int n;
const int mxN = 1e3+5;
int ar[mxN][mxN], de[mxN*mxN][2], en[mxN][mxN];
bool vis[mxN][mxN];

bool disrupt(int x){
    pair<int,int>pr = {de[x][0],de[x][1]};
    int aboveright = 0, aboveleft = 0, bottomleft = 0, bottomright = 0;
    if (pr.first != n-1 && pr.second != 0){
        aboveright = vis[pr.first+1][pr.second]+vis[pr.first][pr.second-1]+vis[pr.first+1][pr.second-1];
    }
    if (pr.first != 0 && pr.second != 0){
        aboveleft = vis[pr.first-1][pr.second]+vis[pr.first][pr.second+1]+vis[pr.first-1][pr.second+1];
    }
    if (pr.first != 0 && pr.second != n-1){
        bottomleft = vis[pr.first-1][pr.second]+vis[pr.first][pr.second+1]+vis[pr.first-1][pr.second+1];
    }
    if (pr.first != n-1 && pr.second != n-1){
        bottomright = vis[pr.first+1][pr.second]+vis[pr.first][pr.second+1]+vis[pr.first+1][pr.second+1];
    }
    return (aboveright <= 1 && aboveleft <= 1 && bottomleft <= 1 && bottomright <= 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int cnt = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> ar[i][j];
            en[i][j] = cnt;
            de[cnt][0] = i;
            de[cnt][1] = j;
            cnt++;
        }
    }
    //fill as many as possible w/o going over in each 2x2
    vector<pair<ll,int>>vals(n*n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            vals.push_back({ar[i][j],en[i][j]});
        }
    }
    sort(vals.rbegin(),vals.rend());
    ll ans = 0;
    for (int i = 0; i < vals.size(); i++){
        //check if it will disrupt anything
        if (disrupt(vals[i].second)){
            ans += vals[i].first;
            vis[de[vals[i].second][0]][de[vals[i].second][1]] = true;
        }
    }
    cout << ans << "\n";
}

