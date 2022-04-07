#include <bits/stdc++.h>
using namespace std;

/*
 Idea:
    * Take in input and auto-add t to every weight
    * Build adjacency lists with 3 apart (For the bottom right vertex add every near as adjacent and sub t from weight)
    * Run Dijkstra
    * Profit
*/

const int mxN = 100;
const long long INF = 1e18;
int a[mxN][mxN];
vector<pair<int,int>>adj[mxN*mxN];
vector<int>adj2[mxN*mxN];
int n,t;

int xc[] = {3,2,2,1,1,0,0,-1,-1,-2,-2,-3};
int yc[] = {0,1,-1,2,-2,3,-3,2,-2,1,-1,0};
int xc1[] = {0,0,-1,-1,-2};
int yc1[] = {-2,-1,-1,0,0};

int coord(int x, int y){
    return x*n + y;
}
array<int,2>revcoord(int x){
    return {x / n, x%n};
}
bool valid(vector<int>p, int x, int y){
    if (x >= n || y >= n || x < 0 || y < 0){
        return false;
    }
    //if found in array
    if (find(p.begin(),p.end(),coord(x,y)) != p.end()){
        return false;
    }
    return true;
}
void bld(int x, int y){
    for (int i = 0; i < 12; i++){
        if (valid(adj2[coord(x,y)],x+xc[i],y+yc[i])){
            int c1 = coord(x,y);
            int c2 = coord(x+xc[i],y+yc[i]);
            adj2[c1].push_back(c2);
            adj2[c2].push_back(c1);
            adj[c1].emplace_back(a[x+xc[i]][y+yc[i]],c2);
            adj[c2].emplace_back(a[x][y],c1);
            bld(x+xc[i],y+yc[i]);
        }
    }
}
void bldfinal(){
    for (int i = 0; i < 5; i++){
        if (valid(adj2[coord(n-1,n-1)],n-1+xc1[i],n-1+yc1[i])){
            int dist = abs(xc1[i]) + abs(yc1[i]);
            int c1 = coord(n-1,n-1);
            int c2 = coord(n-1+xc1[i],n-1+yc1[i]);
            adj2[c2].push_back(c1);
            adj[c2].emplace_back(dist*t,c1);
        }
    }
}
int main(){
//    freopen("visitfj.in","r",stdin);
//    freopen("visitfj.out","w",stdout);
    cin >> n >> t;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> a[i][j];
            a[i][j] += 3*t;
        }
    }
    bld(0,0);
    bldfinal();

    //now proceed with dijikstras
    set<pair<long long,int>>q;
    long long d[n*n]; d[0] = 0;
    q.insert({0,0});
    for (int i = 1; i < n*n; i++){
        q.insert({INF,i});
        d[i] = INF;
    }
    while (!q.empty()){
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto & e : adj[v]){
            int to = e.second;
            int len = e.first;
            if (d[to] > d[v]+len){
                q.erase({d[to],to});
                d[to] = d[v]+len;
                q.insert({d[to],to});
            }
        }
    }
    cout << d[n*n-1] << "\n";
}