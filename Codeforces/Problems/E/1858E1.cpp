#include <bits/stdc++.h>

using namespace std;

const int mxN = 1e6 + 1;
const int LOG = 21;

vector<int> adj[mxN];
int commit_anc[mxN];
int anc[mxN][LOG];

int arr[mxN]; //stores value at corresponding id
int id_at_commit[mxN]; // stores id of node at particular commit
vector<int> query_at_id[mxN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q; cin >> q;
    vector<pair<char, int>> queries(q);
    for (int i = 0; i < q; i++){
        char command; cin >> command;
        if (command == '+' || command == '-'){
            int x; cin >> x;
            queries[i] = {command, x};
        }
        else{
            queries[i] = {command, -1};
        }
    }
    memset(anc, 0, sizeof(anc));
    memset(commit_anc, 0, sizeof(commit_anc));

    int curr_id = 0;
    int max_used_id = 0;
    int curr_cmd = 0;
    int max_used_cmd = 0;

    int query_num = 0;

    for (int i = 0; i < q; i++){
        if (queries[i].first == '+'){
            adj[curr_id].push_back(max_used_id+1);
            max_used_id++;

            anc[max_used_id][0] = curr_id;
            for (int b = 1; b < LOG; b++){
                anc[max_used_id][b] = anc[anc[max_used_id][b-1]][b-1];
                if (anc[max_used_id][b] == 0){
                    break;
                }
            }

            curr_id = max_used_id;
            arr[curr_id] = queries[i].second;

            max_used_cmd++;
            commit_anc[max_used_cmd] = curr_cmd;
            curr_cmd = max_used_cmd;

            id_at_commit[curr_cmd] = curr_id;
        }
        else if (queries[i].first == '-'){
            int k = queries[i].second;
            int b = 0;
            while (k){
                if (k & 1){
                    curr_id = anc[curr_id][b];
                }
                k >>= 1; b++;
            }
            max_used_cmd++;
            commit_anc[max_used_cmd] = curr_cmd;
            curr_cmd = max_used_cmd;

            id_at_commit[curr_cmd] = curr_id;
        }
        else if (queries[i].first == '!'){
            curr_cmd = commit_anc[curr_cmd];
            curr_id = id_at_commit[curr_cmd];
        }
        else{
            query_at_id[curr_id].push_back(query_num);
            query_num++;
        }
    }
    vector<int> ans(query_num);

    unordered_map<int,int> occ;
    auto dfs = [&](auto self, int u, int v) -> void{
        occ[arr[u]]++;
        for (int x : query_at_id[u]){
            ans[x] = occ.size() - 1; //we cannot include arr[0]
        }
        for (int x : adj[u]){
            if (x != v){
                self(self, x, u);
            }
        }
        occ[arr[u]]--;
        if (occ[arr[u]] == 0){
            occ.erase(arr[u]);
        }
    };

    dfs(dfs, 0, -1);

    for (int i = 0; i < query_num; i++){
        cout << ans[i] << "\n";
    }
}