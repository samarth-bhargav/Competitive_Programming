#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;
vector<int> adj[mxN];
set<int> mc;
bool vis[mxN];
int sz = 0;

bool dfs1(int u, int v, int s, int ct = 1){
    if (u == s && ct == sz){
        return true;
    }
    if (vis[u]){
        return false;
    }
    vis[u] = true;
    if (adj[u].size() != 2){
        return false;
    }
    for (int x : adj[u]){
        if (x != v){
            return dfs1(x, u, s, ct+1);
        }
    }
    return false;
}

bool dfs2(int u, int v, int s, int ct = 1){
    if (u == s && ct == sz){
        return true;
    }
    if (vis[u]){
        return false;
    }
    vis[u] = true;
    for (int x : adj[u]){
        if (x != v && adj[x].size() == 4){
            return dfs2(x, u, s, ct+1);
        }
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++){
            adj[i].clear();
        }
        mc.clear();
        for (int i = 0; i < m; i++){
            int a, b; cin >> a >> b; a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        bool notok = false;
        for (int i = 0; i < n; i++){
            if (notok){
                break;
            }
            if (adj[i].size() == 4){
                mc.insert(i);
            }
            else if (adj[i].size() != 2){
                cout << "NO\n";
                notok = true;
                continue;
            }
        }
        if (notok){
            continue;
        }
        if (mc.size() * (mc.size() + 1) != m){
            cout << "NO\n";
            continue;
        }
        for (int i = 0; i < n; i++){
            vis[i] = false;
        }
        sz = mc.size();
        bool bad = false;
        for (int s : mc){
            bool seen = false;
            int cnt = 0;
            for (int x : adj[s]){
                if (adj[x].size() == 2){
                    if (seen){
                        cnt++;
                        continue;
                    }
                    cnt++;
                    seen = true;
                    if (!dfs1(x, s, s)){
                        cout << "NO\n";
                        bad = true;
                        break;
                    }
                }
            }
            if (bad){
                break;
            }
            if (cnt != 2){
                cout << "NO\n";
                bad = true;
                break;
            }
        }
        if (!bad){
            for (int s : mc){
                vis[s] = false;
            }
            int s = *mc.begin();
            for (int x : adj[s]){
                if (adj[x].size() == 4){
                    if (!dfs2(x, s, s)){
                        cout << "NO\n";
                        bad = true;
                        break;
                    }
                    break;
                }
            }
        }
        if (!bad){
            cout << "YES\n";
        }
    }
}
