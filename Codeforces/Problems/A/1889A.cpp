#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        map<int, int> occ;
        for (int i = 0; i < n; i++){
            cin >> a[i];
            occ[a[i]]++;
        }
        if (occ.size() > 2){
            cout << "No\n";
            continue;
        }
        if (occ.size() == 1){
            cout << "Yes\n";
            continue;
        }
        if (occ.begin()->second == n / 2 || next(occ.begin())->second == n / 2){
            cout << "Yes\n";
        }
        else{
            cout << "No\n";
        }
    }
}