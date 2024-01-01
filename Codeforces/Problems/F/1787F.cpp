#include <bits/stdc++.h>

using namespace std;

int binpow(int base, int exp, int mod){
    int ret = 1;
    int curr = base;
    while (exp){
        if (exp & 1){
            ret *= curr;
            ret %= mod;
        }
        curr = curr * curr;
        curr %= mod;
        exp >>= 1;
    }
    return (ret % mod + mod) % mod;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    for (int tt = 0; tt < t; tt++){
        int n, k; cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i]; a[i]--;
        }
//        if (tt == 112){
//            cout << n << " " << k << "\n";
//            for (int i = 0; i < n; i++){
//                cout << a[i]+1 << " ";
//            }
//            cout << "\n";
//            return 0;
//        }
        vector<bool> vis(n, false);
        auto get_cycle = [&](int u, auto&& get_cycle) -> vector<int> {
            int curr_node = u;
            vector<int> cycle;
            do{
                vis[curr_node] = true;
                cycle.push_back(curr_node);
                curr_node = a[curr_node];
            } while (curr_node != u);
            return cycle;
        };
        vector<vector<vector<int>>> cycles(n+1);
        for (int i = 0; i < n; i++){
            if (!vis[i]){
                vector<int> cycle = get_cycle(i, get_cycle);
                cycles[cycle.size()].push_back(cycle);
            }
        }
        bool bad = false;
        vector<int> sol(n);
        for (int len = 1; len <= n; len++){
            int log_len = __builtin_ctz(len);
            int num_cycles = cycles[len].size();
            if (num_cycles == 0) continue;
            int min_allowed = (len % 2 == 0 ? log_len + k : 0);
            int max_allowed = min(log_len + k, 31 - __builtin_clz(num_cycles) + log_len);
            int raw_len = len >> log_len;
            int curr_idx = 0;
            for (int b = max_allowed; b >= min_allowed; b--){
                if ((len << (b - log_len)) <= num_cycles * len){
                    const int cs = len << (b - log_len);
                    vector<int> cyc(cs);
                    //push back starts of sequences
                    for (int i = 0; i < (1 << (b - log_len)); i++){
                        cyc[i] = cycles[len][curr_idx + i][0];
                    }
                    int offset = (binpow(2, k, cs) % cs + cs) % cs;
                    for (int start = 0; start < (1 << (b - log_len)); start++){
                        int curr_pos = start;
                        do{
                            cyc[(curr_pos + offset) % cs] = a[cyc[curr_pos]];
                            curr_pos += offset; curr_pos %= cs;
                        } while (curr_pos != start);
                    }
                    //construct solution
                    for (int i = 1; i < cs; i++){
                        sol[cyc[i-1]] = cyc[i];
                    }
                    sol[cyc.back()] = cyc[0];
                    int cycles_used = (len << (b - log_len)) / len;
                    curr_idx += cycles_used;
                    num_cycles -= cycles_used; b++;
                }
            }
            if (num_cycles != 0){
//                if (t != 10000){
                cout << "NO\n";
//                }
                bad = true;
                break;
            }
        }
        if (!bad){
//            if (t != 10000){
                cout << "YES\n";
                for (int i = 0; i < n; i++){
                    cout << sol[i] + 1 << " ";
                }
                cout << "\n";
//            }
        }
    }
}