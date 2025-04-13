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

#define int long long

int32_t main(){
    int n, k; cin >> n >> k;

    vector<int> a(n), b(n);

    vector<int> a_ith, b_ith;

    for (int i = 0; i < n; i++){
        char c; cin >> c;
        a[i] = c - '0';
        if (a[i] == 1){
            a_ith.push_back(i);
        }
    }
    for (int i = 0; i < n; i++){
        char c; cin >> c;
        b[i] = c - '0';
        if (b[i] == 1){
            b_ith.push_back(i);
        }
    }

    auto score = [&](int a, int b){
        return (abs(a - b) + k - 1) / k;
    };

    while (true){
        dbg(a_ith, b_ith);
        bool good = true;
        for (int i = 0; i < a_ith.size()-1; i++){
            if (score(a_ith[i], b_ith[i]) + score(a_ith[i+1], b_ith[i+1]) > score(a_ith[i], b_ith[i+1]) + score(a_ith[i+1], b_ith[i])){
                assert(k != 1);
                swap(b_ith[i], b_ith[i+1]);
                good = false;
                break;
            }
        }
        if (good){
            break;
        }
    }
    int ans = 0;
    for (int i = 0; i < a_ith.size(); i++){
        ans += score(a_ith[i], b_ith[i]);
    }
    cout << ans << "\n";
}