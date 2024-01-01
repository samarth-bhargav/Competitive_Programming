#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> sol;
        while (n != 1){
            sol.push_back(n);
            if (1 << (__builtin_ctz(n)) == n){
                n -= (1 << (__builtin_ctz(n) - 1));
            }
            else{
                n -= (1 << (__builtin_ctz(n)));
            }
        }
        sol.push_back(1);
        cout << sol.size() << "\n";
        for (int i = 0; i < sol.size(); i++){
            cout << sol[i] << " ";
        }
        cout << "\n";
    }
}