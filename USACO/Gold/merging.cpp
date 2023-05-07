#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;
vector<int> children[mxN];
vector<vector<int>> lvl_subtree[mxN];
vector<int> max_val[mxN];
int par[mxN][mxN];
vector<vector<int>> lvl_subtree_f[mxN];
vector<int> children_f[mxN];

void dfs(int u, int d){
    vector<vector<int>> res; res.resize(1);
    for (int child : children[u]){
        dfs(child, d+1);
        res.resize(max(res.size(), lvl_subtree[child].size()+1));
        for (int lvl = 0; lvl < lvl_subtree[child].size(); lvl++){
            for (int node : lvl_subtree[child][lvl]){
                res[lvl+1].push_back(node);
            }
        }
    }
    res[0].push_back(u);
    lvl_subtree[u] = res;
    max_val[u].push_back(u);
    for (int lvl = 1; lvl < lvl_subtree[u].size(); lvl++){
        max_val[u].push_back(*max_element(lvl_subtree[u][lvl].begin(), lvl_subtree[u][lvl].end()));
    }
    for (int lvl = 0; lvl < lvl_subtree[u].size(); lvl++){
        for (int node : lvl_subtree[u][lvl]){
            par[node][d] = u;
        }
    }
}

void dfs2(int u){
    vector<vector<int>> res; res.resize(1);
    for (int child : children_f[u]){
        dfs2(child);
        res.resize(max(res.size(), lvl_subtree_f[child].size()+1));
        for (int lvl = 0; lvl < lvl_subtree_f[child].size(); lvl++){
            for (int node : lvl_subtree_f[child][lvl]){
                res[lvl+1].push_back(node);
            }
        }
    }
    res[0].push_back(u);
    lvl_subtree_f[u] = res;
}

//solve for the answer
set<array<int, 2>> operations_occurred;
vector<array<int, 2>> operations;

void dfs3(int u, int d){
    //compare lvl_subtree on graph rn to lvl_subtree_f on final graph
    //find out mandatory movements
    for (int child : children_f[u]){
        for (int lvl = 1; lvl < lvl_subtree_f[child].size(); lvl++){
            for (int node : lvl_subtree_f[child][lvl]){
                int parent = par[node][d+1];
                if (parent != child){
                    if (operations_occurred.count({parent, child})){
                        continue;
                    }
                    operations_occurred.insert({parent, child});
                    operations.push_back({parent, child});
                    for (int elem : children[parent]){
                        children[child].push_back(elem);
                    }
                    children[u].erase(find(children[u].begin(), children[u].end(), parent));
                    children[parent].clear();
                    children[parent].shrink_to_fit();
                    //merge all of lvl_subtree into it
                    lvl_subtree[child].resize(max(lvl_subtree[child].size(), lvl_subtree[parent].size()), vector<int>());
                    max_val[child].resize(max(max_val[child].size(), max_val[parent].size()), 0);
                    for (int lvl_m = 1; lvl_m < lvl_subtree[parent].size(); lvl_m++){
                        for (int nd : lvl_subtree[parent][lvl_m]){
                            assert(lvl_m < max_val[child].size());
                            assert(lvl_m < lvl_subtree[child].size());
                            lvl_subtree[child][lvl_m].push_back(nd);
                            max_val[child][lvl_m] = max(max_val[child][lvl_m], max_val[parent][lvl_m]);
                        }
                        lvl_subtree[parent][lvl_m].clear();
                        lvl_subtree[parent][lvl_m].shrink_to_fit();
                    }
                }
            }
        }
    }
    vector<int> to_remove;
    for (int child : children[u]){
        if (find(children_f[u].begin(), children_f[u].end(), child) == children_f[u].end()){
            to_remove.push_back(child);
            //child is not supposed to be there
            //figure out which one the child can go into
            for (int child1 : children_f[u]){
                //can the child be merged into it?
                bool bad = false;
                for (int lvl = 0; lvl < lvl_subtree[child].size(); lvl++){
                    if (max_val[child][lvl] > max_val[child1][lvl]){
                        bad = true;
                        break;
                    }
                }
                if (!bad){
                    operations_occurred.insert({child, child1});
                    operations.push_back({child, child1});
                    for (int elem : children[child]){
                        children[child1].push_back(elem);
                    }
                    children[child].clear();
                    children[child].shrink_to_fit();
                    max_val[child1].resize(max(max_val[child1].size(), max_val[child].size()), 0);
                    lvl_subtree[child1].resize(max(lvl_subtree[child1].size(), lvl_subtree[child].size()), vector<int>());
                    //merge all of lvl_subtree into it
                    for (int lvl_m = 1; lvl_m < lvl_subtree[child].size(); lvl_m++){
                        for (int nd : lvl_subtree[child][lvl_m]){
                            assert(lvl_m < max_val[child1].size());
                            assert(lvl_m < lvl_subtree[child1].size());
                            lvl_subtree[child1][lvl_m].push_back(nd);
                            max_val[child1][lvl_m] = max(max_val[child][lvl_m], max_val[child1][lvl_m]);
                        }
                        lvl_subtree[child][lvl_m].clear();
                        lvl_subtree[child][lvl_m].shrink_to_fit();
                    }
                    break;
                }
            }
        }
    }
    for (int child : to_remove){
        children[u].erase(find(children[u].begin(), children[u].end(), child));
    }
    for (int child : children[u]){
        dfs3(child, d+1);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        memset(par, -1, sizeof(par));
        for (int i = 0; i < n-1; i++){
            int a, b; cin >> a >> b; a--; b--;
            children[b].push_back(a);
        }
        dfs(0, 0);
        int n1; cin >> n1;
        for (int i = 0; i < n1-1; i++){
            int a, b; cin >> a >> b; a--; b--;
            children_f[b].push_back(a);
        }
        dfs2(0);
        dfs3(0, 0);
        cout << operations.size() << "\n";
        for (array<int, 2> op : operations){
            cout << op[0]+1 << " " << op[1]+1 << "\n";
        }
        for (int i = 0; i < n; i++){
            children[i].clear();
            lvl_subtree[i].clear();
            max_val[i].clear();
            children_f[i].clear();
            lvl_subtree_f[i].clear();
        }
        operations_occurred.clear();
        operations.clear();
    }
}
