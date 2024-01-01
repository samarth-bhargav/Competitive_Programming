#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        vector<int> s(n);
        for (int i = 0; i < n; i++){
            char c; cin >> c;
            s[i] = c - '0';
        }
        vector<int> nxt1(n, -1), prev0(n, -1);
        stack<int> stk;
        for (int i = 0; i < n; i++){
            stk.push(i);
            if (s[i] == 1){
                while (!stk.empty()){
                    nxt1[stk.top()] = i;
                    stk.pop();
                }
            }
        }
        while (!stk.empty()) stk.pop();
        for (int i = n-1; ~i; i--){
            stk.push(i);
            if (s[i] == 0){
                while (!stk.empty()){
                    prev0[stk.top()] = i;
                    stk.pop();
                }
            }
        }
        set<pair<int,int>> rngs;
        for (int i = 0; i < m; i++){
            int l, r; cin >> l >> r;
            l--; r--;
            int tl = nxt1[l];
            int tr = prev0[r];
            if (tl == -1 || tr == -1){
                rngs.insert({-1, -1});
                continue;
            }
            if (tl > r || tr < l || tl > tr){
                //effective range is empty
                rngs.insert({-1, -1});
                continue;
            }
            rngs.insert({tl, tr});
            assert(tl < tr);
        }
        cout << rngs.size() << "\n";
    }
}