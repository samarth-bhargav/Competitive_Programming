#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mxN = 1e5;
vector<pair<int,int>> swaps;
int n, k;
long long reps, rem, m;
unordered_set<int> visited[mxN], visitedRem[mxN];
vector<int> adj(mxN), cnt(mxN);
bool vis[mxN];
unordered_map<int, int> freq;

void dfs(int head, int tail){
    vis[tail] = true;
    for (int loc : visitedRem[head]){
        freq[loc]++;
    }
    cnt[tail] = freq.size();
    for (int loc : visited[tail]){
        freq[loc]--;
        if (freq[loc] <= 0){
            freq.erase(loc);
        }
    }
    for (int loc : visitedRem[head]){
        freq[loc]--;
        if (freq[loc] <= 0){
            freq.erase(loc);
        }
    }
    if (head != tail){
        for (int loc : visited[head]){
            freq[loc]++;
        }
    }
    if (!vis[adj[tail]]){
        dfs(adj[head], adj[tail]);
    }
}


void process_if_all(int start){
    cnt[start] = freq.size();
    int curr = adj[start];
    while (curr != start){
        vis[curr] = true;
        cnt[curr] = freq.size();
        curr = adj[curr];
    }
}

void dfs_prep(int start){
    int curr = start, tail = start;
    for (int i = 0; i < reps; i++){
        for (int loc : visited[curr]){
            freq[loc]++;
        }
        if (adj[curr] == start){
            //we got all nodes
            process_if_all(start);
            freq.clear();
            return;
        }
        curr = adj[curr];
    }
    dfs(curr, start);
    freq.clear();
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k >> m;
    reps = m / k; rem = m%k;
    for (int i = 0; i < k; i++){
        int a, b;
        cin >> a >> b; a--; b--;
        swaps.emplace_back(a,b);
    }
    vector<int> line;
    for (int i = 0; i < n; i++){
        line.push_back(i);
        visited[i].insert(i);
        visitedRem[i].insert(i);
    }
    for (int i = 0; i < k; i++){
        visited[line[swaps[i].first]].insert(swaps[i].second);
        visited[line[swaps[i].second]].insert(swaps[i].first);
        if (rem > i){
            visitedRem[line[swaps[i].first]].insert(swaps[i].second);
            visitedRem[line[swaps[i].second]].insert(swaps[i].first);
        }
        swap(line[swaps[i].first], line[swaps[i].second]);
    }
    for (int i = 0; i < n; i++){
        adj[line[i]] = i;
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++){
        if (!vis[i]){
            dfs_prep(i);
        }
    }
    for (int i = 0; i < n; i++){
        cout << cnt[i] << "\n";
    }
}
