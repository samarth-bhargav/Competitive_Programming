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

int main(){
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> nxt(n), prv(n);
    vector<array<int, 2>> stk; stk.push_back({a[0], 0});
    vector<vector<int>> chains(n);
    for (int i = 1; i < 2 * n; i++){
        int j = i % n;
        while (!stk.empty() && stk.back()[0] >= a[j]){
            if (stk.back()[0] == a[j] && stk.back()[1] != j){
                chains[stk.back()[0]].push_back(i);
            }
            else{
                stk.pop_back();
            }
        }
        if (i < n){
            stk.push_back({a[j], j});
        }
    }
    assert(stk.empty());
    stk.push_back({a[n-1], n-1});
    for (int i = n-1; i >= -n; i--){
        int j = (i % n + n) % n;
        while (!stk.empty() && stk.back()[0] >= a[j]){
            if (stk.back()[1] == j){
                prv[stk.back()[1]] = stk.back()[1];
            }
            else{
                prv[stk.back()[1]] = i;
            }
            stk.pop_back();
        }
        if (i >= 0){
            stk.push_back({a[j], j});
        }
    }
    assert(stk.empty());
//    for (int i = 0; i < n; i++){
//        cout << prv[i] << " " << nxt[i] << "\n";
//    }
    vector<vector<int>> add(n+2);
    vector<vector<array<int, 2>>> rm(n+2);

    for (int i = 0; i < n; i++){
        int x = ((nxt[i] - i) % n + n) % n, y = (i - prv[i] % n + n) % n;
        x--; y--;
        if (x == -1 && y == -1){
            add[1].push_back(a[i]);
            continue;
        }
        if (x == 0 || y == 0){
            if (y == 0) swap(x, y);
            rm[1].push_back({a[i], 0});
            rm[y+2].push_back({-a[i], 0});
            continue;
        }
        add[1].push_back(a[i]); rm[x+y+2].push_back({(x+y+1) * -a[i], -a[i]});
//        dbg('+', x+2, -a[i]); dbg('-', x+y+1, (x+y+1 - (x+2)) * a[i]);
        add[x+2].push_back(-a[i]); rm[x+y+2].push_back({(x+y+2 - (x+2)) * a[i], a[i]});
//        dbg('+', x+2, -a[i]); dbg('-', x+y+1, (x+y+1 - (x+2)) * a[i]);
        add[y+2].push_back(-a[i]); rm[x+y+2].push_back({(x+y+2 - (y+2)) * a[i], a[i]});
    }

    int active_sum = 0;
    vector<int> final(n+2, 0);
    int c_sum = 0;

    for (int i = 0; i <= n+1; i++){
        for (int x : add[i]){
            active_sum += x;
        }
        for (array<int, 2> x : rm[i]){
            c_sum += x[0];
            active_sum += x[1];
        }
        c_sum += active_sum;
        final[i] = c_sum;
    }

    for (array<int, 2> x : equals){
        final[abs(x[1] - x[0] + 1)] += a[x[0]];
    }
    for (int i = 2; i <= n+1; i++){
        cout << final[i] << " ";
    }
    cout << "\n";
}