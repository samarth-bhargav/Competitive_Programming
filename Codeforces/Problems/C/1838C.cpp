#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        for (int i = 1; i < n; i += 2){
            for (int j = 0; j < m; j++){
                cout << i * m + j + 1 << " ";
            }
            cout << "\n";
        }
        for (int i = 0; i < n; i += 2){
            for (int j = 0; j < m; j++){
                cout << i * m + j + 1 << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}