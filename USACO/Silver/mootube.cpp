#include <bits/stdc++.h>
using namespace std;

const int mxN = 5001;
int n,q;
vector <int> adj[mxN];
map<pair<int,int>,int>relevance;
int cnt = 0;

void dfs(int e, int a, int r, int rqr){
    cnt++;
    if (e != a){
        r = min(r, relevance[{min(a,e),max(a,e)}]);
    }
    if (r < rqr) {
        cnt--;
        return;
    }
    for (auto & i : adj[e]){
        if (i != a){
            dfs(i,e,r,rqr);
        }
    }
}

int main(){
//    ifstream cin("mootube.in");
//    ofstream cout("mootube.out");
    auto start = chrono::steady_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 0; i < n-1; i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].push_back(b);
        adj[b].push_back(a);
        relevance[{min(a,b),max(a,b)}] = c;
    }
    for (int i = 0; i < q; i++){
        int a,b;
        cin >> a >> b;
        dfs(b,b,1e9,a);
        cout << cnt-1 << "\n";
        cnt = 0;
    }
    auto stop = chrono::steady_clock::now();
    auto diff = stop-start;
    cout << chrono::duration <double,milli> (diff).count() << "ms" << "\n";
}