#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;

int main(){
    int n,m;
    cin >> n >> m;
    vector<string>names(n);
    for (int i = 0; i < n; i++) {
        cin >> names[i];
    }
    vector<set<char>>vals(m);
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            vals[i].insert(names[j][i]);
        }
    }
    long long ans = 1;
    for (auto & i : vals){
        ans = (ans*i.size())%MOD;
    }
    cout << ans << "\n";
}