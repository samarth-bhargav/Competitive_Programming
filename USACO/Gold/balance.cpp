#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e9;

struct node{
    int id;
    int parent;
    vector<int> children;
    int maxmin = -INF;
    int minmax = INF;
    int lb;
    int rb;
    node(){
        children = {};
    }
};

const int mxN = 1e5;
vector<node> nodes(mxN);
int ans = 0;
int maxL = -INF, minR = INF;

void dfs(int u){

    for (int child : nodes[u].children){
        dfs(child);
        ans = max(ans, nodes[u].lb - nodes[child].minmax);
        ans = max(ans, nodes[child].maxmin - nodes[u].rb);
    }
    if (nodes[u].children.empty()){
        nodes[u].maxmin = nodes[u].lb;
        nodes[u].minmax = nodes[u].rb;
    }
    else{
        nodes[u].maxmin = nodes[u].lb;
        nodes[u].minmax = nodes[u].rb;
        for (int child : nodes[u].children){
            nodes[u].maxmin = max(nodes[u].maxmin, nodes[child].maxmin);
            nodes[u].minmax = min(nodes[u].minmax, nodes[child].minmax);
        }
    }
    ans = max(ans, (nodes[u].maxmin - nodes[u].minmax + 1) / 2);
//    cerr << "id: " << nodes[u].id << " maxmin: " << nodes[u].maxmin << " minmax: " << nodes[u].minmax << "\n";
}

int32_t main(){
    ios_base::sync_with_stdio(false);

    int t; bool b;
    cin >> t >> b;
    while (t--){
        //input
        int n;
        cin >> n;
        for (int i = 1; i < n; i++){
            nodes[i].maxmin = -INF;
            nodes[i].minmax = INF;
            cin >> nodes[i].parent;
            nodes[i].parent--; //to zero-index
        }
        for (int i = 0; i < n; i++){
            cin >> nodes[i].lb >> nodes[i].rb;
            nodes[i].id = i;
            nodes[i].children.clear();
        }
        //populate children to make life easy
        for (int i = 1; i < n; i++){
            int p = nodes[i].parent;
            nodes[p].children.push_back(i);
        }
        for (int u = 0; u < n; u++){
            maxL = max(maxL, nodes[u].lb);
            minR = min(minR, nodes[u].rb);
        }

        //dfs to find minimum val
        dfs(0);
        cout << ans << "\n";
        if (b){
            int mid = (maxL + minR) / 2;
            for (int i = 0; i < n; i++){
                cout << max(min(mid, nodes[i].rb), nodes[i].lb) << "\n "[i < n-1];
            }
        }
        ans = 0;
        maxL = -INF;
        minR = INF;
        nodes = vector<node>(mxN);
    }
/*
    1 0
    5
    0 0 2 2
    1 10
    2 14
    3 7
    7 12
    3 5
*/
}