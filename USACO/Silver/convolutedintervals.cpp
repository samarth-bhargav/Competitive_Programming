//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

const int mxSUM = 10001;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;
    pair<int,int> intervals[n];
    for (int i = 0; i < n; i++){
        cin >> intervals[i].first >> intervals[i].second;
    }
    map<int,int> aocc;
    map<int,int> bocc;
    for (int i = 0; i < n; i++){
        aocc[intervals[i].first]++;
        bocc[intervals[i].second]++;
    }
    ll dpA[mxSUM];
    ll dpB[mxSUM];
    memset(dpA,0,sizeof(dpA));
    memset(dpB,0,sizeof(dpB));
    for (auto &i : aocc){
        for (auto &j : aocc){
            dpA[i.first+j.first] += (i.second*j.second);
        }
    }
    for (auto &i : bocc){
        for (auto &j : bocc){
            dpB[i.first+j.first] += (i.second*j.second);
        }
    }
    ll ans = dpA[0];
    cout << ans << "\n";
    for (int k = 1; k <= 2*m; k++){
        ans = ans + dpA[k] - dpB[k-1];
        cout << ans << "\n";
    }
}

