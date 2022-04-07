/*
ID:
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

struct cow{
    int id;
    int x,y;
    double brodlen;
};

bool vis[200];
vector <cow> adj[200];
cow ar[200];
long ans = 1;
int cowdist(cow a, cow b){
    return ((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int dfs(cow e){
    vis[e.id] = true;
    for (auto child:adj[e.id]){
        if (!vis[child.id]){
            dfs(child);
        }
    }
}

int main() {
    setIO("moocast");
    //determine which things are connected for dfs
    int t;
    cin >> t;
    for (int i = 0; i < t; i++){
        cin >> ar[i].x >> ar[i].y >> ar[i].brodlen;
        ar[i].id = i;
    }
    for (int i = 0; i < t; i++){
        for (int k = 0; k < t; k++){
            if (i!=k){
                if (cowdist(ar[i], ar[k]) <= ar[i].brodlen * ar[i].brodlen){
                    adj[i].push_back(ar[k]);
                }
            }
        }
    }
    for (int i = 0; i < t; i++){
        dfs(ar[i]);
        ans = max(ans, count(vis,vis+200,1));
        memset(vis, 0, sizeof(vis));
    }
    cout << ans << "\n";
}

