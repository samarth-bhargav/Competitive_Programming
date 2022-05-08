/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}

int main() {
    setIO("helpcross");
    int n,m;
    cin >> n >> m;
    multiset <int> chickens;
    for (int i = 0; i < n; i++){
        int c;
        cin >> c;
        chickens.insert(c);
    }
    vector <pair <int,int>> cows;
    for (int i = 0; i < m; i++){
        int x,y;
        cin >> x >> y;
        cows.emplace_back(y,x);
    }
    int ans = 0;
    sort(cows.begin(), cows.end());
    for (int i = 0; i < m; i++){
        auto it = chickens.lower_bound(cows[i].second);
        if (it != chickens.end() && cows[i].first >= *(it)){
            ans++;
            chickens.erase(it);
        }
    }
    cout << ans << "\n";
}

