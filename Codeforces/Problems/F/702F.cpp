/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
 * ternary search for optimal C?
*/
template<class T>void dbg(vector<T>p){
    cerr << '{';
    for (auto & i : p){
        cerr << i << ", ";
    }
    cerr << '}';
}
vector<int>a;
ll solve(int c){
    ll ans = 0;
    for (auto & i : a){
        if (i < c){
            ans += i;
        }
        else{
            ans += i-c;
        }
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<int>ar(n);
        for (auto & i : ar){
            cin >> i;
        }
        map<int,int>vals;
        for (auto & i : ar){
            if (vals.find(i) != vals.end()){
                vals[i]++;
            }
            else{
                vals[i] = 1;
            }
        }
        for (auto & i : vals){
            a.push_back(i.second);
        }
        dbg(a);
        for (int i = 0; i <= 5; i++){
            cout << solve(i) << " ";
        }
        cout << "\n";
        return 0;
        int lo = 0, hi = *max_element(a.begin(),a.end());
        while (hi-lo > 3){
            int m1 = lo+(hi-lo)/3;
            int m2 = hi-(hi-lo)/3;
            ll x = solve(m1);
            ll y = solve(m2);
            if (x > y){
                lo = m1;
                continue;
            }
            else if (x == y){
                lo = m1;
                hi = m2;
                continue;
            }
            else{
                hi = m2;
            }
        }
        ll ans = 1e9;
        for (int i = lo; i <= hi; i++){
            ans = min(ans,solve(i));
        }
        cout << ans << "\n";
        a.clear();
    }
}

