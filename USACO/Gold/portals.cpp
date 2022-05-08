/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define all(x) x.begin(), x.end()
/*
*/
const int mxN = 1e5;
set<int>adj[mxN];
array<int,4>portals[mxN];
array<int,2>use[mxN];
vector<int>have[2*mxN];

struct cost{
    int c;
    int idx;
    bool operator <(const cost &o){
        return c < o.c;
    }
};
struct dsu{
    int parent[mxN];
    void init(){
        for (int i = 0; i < mxN; i++){
            parent[i] = i;
        }
    }
    int find(int x){
        return x^parent[x]?parent[x]=find(parent[x]):x;
    }
    bool join(int a, int b){
        a = find(a);
        b = find(b);
        if (a == b){
            return false;
        }
        parent[a] = b;
        return true;
    }
}d1,d2;

cost weights[mxN];
bool vis[mxN];

void dfs(int e, int u, int x, int currportal, bool dx){
    adj[e].insert(u);
    adj[u].insert(e);
    //if x == 0, take 1 and 2
    //else take 3 and 4
    vis[e] = true;
    if (dx == 0){
        d1.join(e,u);
    }
    else{
        d2.join(e,u);
    }
    if (x == 0){
        int first = portals[e][0];
        int second = portals[e][1];
        if (first != currportal){
            for (auto & i : have[first]){
                if (i != e && !vis[i]){
                    if (portals[i][0] == first || portals[i][1] == first){
                        dfs(i, e, 0, first,dx);
                    }
                    else{
                        dfs(i, e, 1, first,dx);
                    }
                }
            }
        }
        else{
            for (auto & i : have[second]){
                if (i != e && !vis[i]){
                    if (portals[i][0] == second || portals[i][1] == second){
                        dfs(i, e, 0, second,dx);
                    }
                    else{
                        dfs(i, e, 1, second,dx);
                    }
                }
            }
        }
    }
    else{
        int first = portals[e][2];
        int second = portals[e][3];
        if (first != currportal){
            for (auto & i : have[first]){
                if (i != e && !vis[i]){
                    if (portals[i][0] == first || portals[i][1] == first){
                        dfs(i, e, 0, first,dx);
                    }
                    else{
                        dfs(i, e, 1, first,dx);
                    }
                }
            }
        }
        else{
            for (auto & i : have[second]){
                if (i != e & !vis[i]){
                    if (portals[i][0] == second || portals[i][1] == second){
                        dfs(i, e, 0, second,dx);
                    }
                    else{
                        dfs(i, e, 1, second,dx);
                    }
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    d1.init();
    d2.init();
    for (int i = 0; i < n; i++) {
        int cost, w, x, y, z;
        cin >> cost >> w >> x >> y >> z;
        weights[i].c = cost;
        weights[i].idx = i;
        portals[i] = {w, x, y, z};
        have[w].push_back(i);
        have[x].push_back(i);
        have[y].push_back(i);
        have[z].push_back(i);
    }
    sort(weights,weights+n);
    dfs(0,0,0,portals[0][0],0);
    dfs(0,0,0,portals[0][1],0);
    dfs(0,0,1,portals[0][2],1);
    dfs(0,0,1,portals[0][3],1);
    int ans = 0, ans1 = 0;
    //do kruskells on d1
    for (int i = 0; i < n; i++){
        int index = weights[i].idx;
        int portal1 = portals[index][0];
        int portal2 = portals[index][1];
        int portal3 = portals[index][2];
        int portal4 = portals[index][3];
        if (d1.join(have[portal1][0],have[portal1][1])){
            ans += weights[i].c;
        }
        else if (d1.join(have[portal2][0],have[portal2][1])){
            ans += weights[i].c;
        }
        else if (d1.join(have[portal3][0],have[portal3][1])){
            ans += weights[i].c;
        }
        else if (d1.join(have[portal4][0],have[portal4][1])){
            ans += weights[i].c;
        }
    }
    //kruskells on d2
    for (int i = 0; i < n; i++){
        int index = weights[i].idx;
        int portal1 = portals[index][0];
        int portal2 = portals[index][1];
        int portal3 = portals[index][2];
        int portal4 = portals[index][3];
        if (d2.join(have[portal1][0],have[portal1][1])){
            ans1 += weights[i].c;
        }
        else if (d2.join(have[portal2][0],have[portal2][1])){
            ans1 += weights[i].c;
        }
        else if (d2.join(have[portal3][0],have[portal3][1])){
            ans1 += weights[i].c;
        }
        else if (d2.join(have[portal4][0],have[portal4][1])){
            ans1 += weights[i].c;
        }
    }
    cout << min(ans,ans1) << "\n";
}

