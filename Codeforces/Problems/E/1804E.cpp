#include <bits/stdc++.h>
using namespace std;

const int mxN = 20;
vector<int> adj(mxN, 0);
int dp[mxN][1 << mxN];

int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b; a--; b--;
        adj[a] |= (1 << b);
        adj[b] |= (1 << a);
    }
    for (int start = 0; start < n; start++){
        memset(dp, -1, sizeof(dp));
        dp[start][1 << start] = n;
        for (int aux_mask = 0; aux_mask < (1 << (n - start)); aux_mask++){
            int mask = aux_mask << start;
            for (int end = 0; end < n; end++){
                if (!(mask & (1 << start)) || !(mask & (1 << end))){
                    continue; //mask must contain start + end
                }
                if (start == end) continue;
                int origin = adj[end] & mask; //where it couldve come from
                for (int from = 0; from < n; from++){
                    if (origin & (1 << from)){
                        if (dp[from][mask ^ (1 << end)] != -1){
                            dp[end][mask] = from;
                            break;
                        }
                    }
                }
            }
        }
        for (int mask = 0; mask < (1 << n); mask++){
            int s = start, e = -1;
            for (int end = 0; end < n; end++){
                if (dp[end][mask] != -1 && (adj[end] & (1 << start))){
                    //we have a cycle with mask
                    s = start; e = end;
                    break;
                }
            }
            if (e == -1){
                continue;
            }
            //check if cycle matches structure
            int vis = mask;
            for (int b = 0; b < n; b++){
                if (mask & (1 << b)){
                    vis |= adj[b];
                }
            }
            if (vis == (1 << n) - 1){
                //extract answer
                cout << "YES\n";
                vector<int> answer(n);
                answer[e] = s;
                int mc = mask;
                while (e != s){
                    answer[dp[e][mc]] = e;
                    int old_e = e;
                    e = dp[e][mc];
                    mc ^= (1 << old_e);
                }
                int comp = ((1 << n) - 1) ^ mask; //all not in cycle
                for (int b = 0; b < n; b++){
                    if (comp & (1 << b)){
                        answer[b] = __builtin_ctz(adj[b] & mask);
                    }
                }
                for (int i = 0; i < n; i++){
                    cout << answer[i]+1 << " ";
                }
                cout << "\n";
                return 0;
            }
        }
    }
    cout << "NO\n";
}
