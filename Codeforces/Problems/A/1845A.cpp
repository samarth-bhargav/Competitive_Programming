#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k, x;
        cin >> n >> k >> x;
        if (x != 1){
            cout << "YES\n";
            cout << n << "\n";
            for (int i = 0; i < n; i++){
                cout << 1 << " ";
            }
            cout << "\n";
        }
        else{
            if (k == 1){
                cout << "NO\n";
            }
            else{
                if (n % 2 == 1 && k == 2){
                    cout << "NO\n";
                }
                else{
                    cout << "YES\n";
                    if (n % 2 == 0){
                        cout << n / 2 << "\n";
                        for (int i = 0; i < n/2; i++){
                            cout << 2 << " ";
                        }
                        cout << "\n";
                    }
                    else{
                        cout << n / 2 << "\n";
                        for (int i = 0; i < n / 2; i++){
                            cout << (i == 0 ? 3 : 2) << " ";
                        }
                        cout << "\n";
                    }
                }
            }
        }
    }
}