#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n,m;
int max_distance = 0;
int first_furthest_node = 0;
const int mxN = 123457;

vector<int> adj[mxN];
vector<int> subtree[mxN];
int edges_in_subtree = 0;
set<int> danger_cities;

bool visited[mxN];

bool bld_subtree(int node, int parent){
    bool cont = (danger_cities.find(node) != danger_cities.end());
    for (int edge : adj[node]){
        if (edge != parent){
            if (bld_subtree(edge, node)){
                cont = true;
                subtree[node].push_back(edge);
                subtree[edge].push_back(node);
                edges_in_subtree++;
            }
        }
    }
    return cont;
}

void dfs(int node, int cnt){
    if (cnt >= max_distance){
        if (cnt == max_distance && (first_furthest_node != 0)){
            first_furthest_node = min(first_furthest_node, node);
        }
        else{
            first_furthest_node = node;
        }
        max_distance = cnt;
    }
    visited[node] = true;
    for (int edge : subtree[node]){
        if (!visited[edge]){
            dfs(edge, cnt+1);
        }
    }
}

int diameter(){
    dfs(*danger_cities.begin(), 0);
    int first_option = first_furthest_node;
    memset(visited, 0, sizeof(visited));
    dfs(first_furthest_node, 0);
    first_furthest_node = min(first_furthest_node, first_option);
    return max_distance;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n-1; i++){
        int e1, e2;
        cin >> e1 >> e2;
        adj[e1].push_back(e2);
        adj[e2].push_back(e1);
    }

    for (int i = 0; i < m; i++){
        int city; cin >> city;
        danger_cities.insert(city);
    }

    bld_subtree(*danger_cities.begin(), -1);
//    for (int i = 1; i <= n; i++){
//        for (int j = 0; j < subtree[i].size(); j++){
//            cerr << "(" <<  i << ", " << subtree[i][j] << ")\n";
//        }
//    }
    int max_d = diameter();

    cout << first_furthest_node << "\n";
    cout << 2 * edges_in_subtree - max_d << "\n";
}

