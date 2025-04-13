#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 7;
#endif

int rnd(int l, int r) {
    return l + (rand() * rand()) % (r - l + 1);
}

vector<array<int, 2>> gen_tree(int sz){
    vector<int> p(sz+1);
    for (int i = 2; i <= sz; i++){
        p[i] = rnd(1, i-1);
    }
    vector<array<int, 2>> ret;
    for (int i = 2; i <= sz; i++){
        ret.push_back({i, p[i]});
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    srand(time(0));

    int t; cin >> t;
    while (t--){
        int n; n = rnd(4, 4);
//        cin >> n;
        vector<int> a(2 * n);
        for (int i = 0; i < n; i++){
            a[2 * i] = i; a[2 * i + 1] = i;
        }
        random_shuffle(a.begin(), a.end());
        vector<int> orig_a = a;
//        for (int i = 0; i < 2 * n; i++){
//            cin >> a[i]; a[i]--;
//            a[i] = rnd(0, n-1);
//        }
        vector<vector<int>> adj(2 * n);
        auto tree = gen_tree(2*n);
        for (int i = 0; i < 2 * n - 1; i++){
//            int u, v; cin >> u >> v; u--; v--;
            int u, v; u = tree[i][0], v = tree[i][1]; u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> other_with_color(2 * n);
        vector<vector<int>> indices_with_color(n);
        for (int i = 0; i < 2 * n; i++){
            indices_with_color[a[i]].push_back(i);
        }

        for (int i = 0; i < n; i++){
            other_with_color[indices_with_color[i][0]] = indices_with_color[i][1];
            other_with_color[indices_with_color[i][1]] = indices_with_color[i][0];
        }

        vector<int> dp(2 * n, 0);
        vector<int> sum_dp(2 * n, 0); // sum of dp of children
        vector<int> favored_child(2 * n, -1);
        vector<vector<int>> children(2 * n);

        auto dfs = [&](auto self, int u, int p=-1) -> void{
            for (int child : adj[u]){
                if (child != p){
                    self(self, child, u);
                    children[u].push_back(child);
                }
            }
            int base_sol = 0;
            for (int child : children[u]){
                base_sol += dp[child];
            }
            sum_dp[u] = base_sol;
            for (int child : children[u]){
                if (base_sol - dp[child] + sum_dp[child] + 1 > dp[u]){
                    dp[u] = base_sol - dp[child] + sum_dp[child] + 1;
                    favored_child[u] = child;
                }
            }
        };

        dfs(dfs, 0);

        vector<array<int, 2>> pairs;

        auto extract_pairs = [&](auto self, int u) -> void{
            if (favored_child[u] != -1){
                pairs.push_back({u, favored_child[u]});
            }
            for (int child : children[u]){
                if (child != favored_child[u]){
                    self(self, child);
                }
            }
            if (favored_child[u] != -1){
                for (int child : children[favored_child[u]]){
                    self(self, child);
                }
            }
        };

        extract_pairs(extract_pairs, 0);

        dbg(pairs);

        vector<int> pair_nbr(2 * n, -1);
        vector<bool> in_pair(2 * n, false);

        for (array<int, 2> pair : pairs){
            pair_nbr[pair[0]] = pair[1];
            pair_nbr[pair[1]] = pair[0];
            in_pair[pair[0]] = true;
            in_pair[pair[1]] = true;
        }

        vector<array<int, 2>> swaps;
        vector<vector<int>> graph(2 * n);

        vector<bool> vis(2 * n, false);

        auto build_graph = [&](auto self, int u) -> void{
            if (vis[u]){
                return;
            }
            vis[u] = true;
            if (pair_nbr[u] == -1){
                return;
            }
            if (vis[pair_nbr[u]]){
                return;
            }
            graph[u].push_back(pair_nbr[u]);
            if (in_pair[other_with_color[pair_nbr[u]]]){
                graph[pair_nbr[u]].push_back(other_with_color[pair_nbr[u]]);
                self(self, other_with_color[pair_nbr[u]]);
            }
        };

        for (int i = 0; i < 2 * n; i++){
            if (in_pair[i]){
                build_graph(build_graph, i);
                vis[i] = false;
                vis[pair_nbr[i]] = false;
                build_graph(build_graph, pair_nbr[i]);
            }
        }

        for (int i = 0; i < 2 * n; i++){
            sort(graph[i].begin(), graph[i].end());
            auto lst = unique(graph[i].begin(), graph[i].end());
            graph[i].erase(lst, graph[i].end());
        }

        dbg(graph);

        vector<int> in_deg(2 * n, 0);
        for (int i = 0; i < 2 * n; i++){
            for (int x : graph[i]){
                in_deg[x]++;
            }
        }

        vector<bool> processed(2 * n, false);

        auto process = [&](int u){
            vector<int> chain;
            int vtx = u, lst = -1;
            bool path = false;
            while (true){
                processed[vtx] = true;
                chain.push_back(vtx);
                int vtx_cache = vtx;
                for (int x : graph[vtx]){
                    if (x != lst){
                        vtx = x;
                        break;
                    }
                }
                lst = vtx_cache;
                if (lst == vtx || vtx == u){
                    if (vtx == lst){
                        path = true;
                    }
                    break;
                }
            }
            dbg(chain);
            if (path){
                for (int i = 0, j = chain.size()-2; i < j; i++, j--){
                    swaps.push_back({chain[i], chain[j]});
                }
                if (chain.size() == 2 && a[chain[0]] == a[chain[1]]){
                    return;
                }
                swaps.push_back({chain.back(), other_with_color[chain[0]]});
            }
            else{
                if (chain.size() == 2){
                    return;
                }
                for (int i = chain.size()-1, j = 1; j < i; j++, i--){
                    swaps.push_back({chain[i], chain[j]});
                }
            }
        };

        for (int i = 0; i < 2 * n; i++){
            if (in_pair[i] && in_deg[i] == 1){
                if (!processed[i]){
                    process(i);
                }
            }
        }

        for (int i = 0; i < 2 * n; i++){
            if (vis[i] && !processed[i]){
                process(i);
            }
        }


        cout << swaps.size() << "\n";

        set<int> x;

        for (array<int, 2> pair : swaps){
            cout << pair[0] + 1 << " " << pair[1] + 1 << endl;
            x.insert(pair[0]);
            x.insert(pair[1]);
        }
        if(x.size() != swaps.size()*2){
            dbg(tree);
            dbg(orig_a);
            assert(false);
        }

        for (array<int, 2> pair : swaps){
            swap(orig_a[pair[0]], orig_a[pair[1]]);
        }
        for (auto pair : pairs){
            if (orig_a[pair[0]] != orig_a[pair[1]]){
                dbg(tree);
                dbg(a);
                assert(false);
            }
        }

    }
}