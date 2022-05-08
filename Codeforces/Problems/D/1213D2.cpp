#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    vector<int>a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    multiset<pair<int,int>>vals;
    map<int,int>mp;
    map<int,bool>done;
    for (auto & i : a){
        int iter = 1;
        vals.insert({i,0}); mp[i]++;
        while (i > 0){
            i >>= 1;
            vals.insert({i,iter});
            mp[i]++;
            iter++;
        }
    }
    int minimum = 1e9;
    for (auto it = vals.begin(); it != vals.end(); it++){
        if (mp[it->first] < k || done[it->first]){
            continue;
        }
        int curr = 0;
        auto iter = vals.lower_bound({it->first,0});
        for (int j = 0; j < k; j++){
            curr += iter->second;
            iter++;
        }
        done[it->first] = true;
        minimum = min(minimum,curr);
    }
    cout << minimum << "\n";
}

