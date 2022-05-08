#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3+5;
multiset<int>berriesog;
int n,k,ans=-1e9;

void solve(int x){
    multiset<int>berries = berriesog;
    int bessie = 0;
    auto lo = berries.lower_bound(x);
    auto it1 = berries.begin();
    int cnt = 0,cnt2 = 0,ret,curr;
    for (auto it = lo; it != berries.end() && cnt != k/2; it++){
        curr = *(it);
        curr -= x;
        berries.erase(it);
        berries.insert(curr);
        it = prev(berries.lower_bound(x));
        it1 = it;
        cnt++;
    }
    if (cnt < k/2){
        return;
    }
    for (auto it = berries.lower_bound(x); it != berries.end() && cnt2 != k/2; it++){
        curr = *(it);
        curr -= x;
        berries.erase(it);
        berries.insert(curr);
        it = prev(berries.lower_bound(x));
        bessie += x;
        cnt2++;
    }
    for (auto it = --berries.upper_bound(x); it != berries.begin() && cnt2 != k/2; it--){
        bessie += *it;
        cnt2++;
    }
    if (bessie > ans) {
        ans = bessie;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("berries.in", "r", stdin);
    freopen("berries.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        berriesog.insert(x);
    }
    int lo = *berriesog.begin();
    int hi = *(prev(berriesog.end()));
    for (int i = lo; i <= hi; i++){
        solve(i);
    }
    cout << ans << "\n";
}
