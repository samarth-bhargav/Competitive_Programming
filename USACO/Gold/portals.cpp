#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5+1, mxP = 4e5+1;
int divisor, rem;
vector<int> portals(mxP);
vector<array<int, 2>> cost;
vector<int> samePortal[2*mxN];

struct dsu{
    vector<int> p;
    int sz;
    void init(int n){
        this->sz = 4*n;
        p.resize(4*n);
        for (int i = 0; i < 4*n; i++){
            p[i] = i;
        }
    }
    int find(int x){
        return x^p[x] ? p[x] = find(p[x]) : x;
    }
    bool join(int a, int b){
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        p[a] = b;
        return true;
    }
} d;

int matching_portal(int p){
    divisor = p / 4;
    rem = p%4;
    rem += (rem%2 == 0 ? 1 : -1);
    return divisor * 4 + rem;
}

vector<bool> visited(mxP, false);
void dfs(int curr, int prev){
    d.join(curr, prev);
    visited[curr] = true;
    int mp = matching_portal(curr);
//    cerr << curr << " " << mp << endl;
    d.join(curr, mp);
    if (visited[mp]){
        return;
    }
    visited[mp] = true;
    int next_portal = (samePortal[portals[mp]][0] == mp ? samePortal[portals[mp]][1] : samePortal[portals[mp]][0]);
    dfs(next_portal, curr);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    d.init(n); cost.resize(n);
    for (int i = 0; i < n; i++){
        cin >> cost[i][0]; cost[i][1] = i;
        cin >> portals[4*i] >> portals[4*i+1] >> portals[4*i+2] >> portals[4*i+3];
        for (int p = 0; p < 4; p++){
            portals[4*i+p]--;
            samePortal[portals[4*i+p]].push_back(4*i+p);
        }
    }
    //initial dfs to do connected components
    for (int i = 0; i < 4*n; i++){
        if (!visited[i]){
            dfs(i, i);
        }
    }
//    for (int i = 0; i < 4*n; i++){
//        cerr << d.find(i) << " ";
//    }
//    cerr << endl;
    //now we can do kruskals
    sort(cost.begin(), cost.end());
    int ans = 0;
    for (int i = 0; i < n; i++){
        if (d.join(4*cost[i][1], 4*cost[i][1]+2)){
            ans += cost[i][0];
        }
    }
    cout << ans << "\n";
}