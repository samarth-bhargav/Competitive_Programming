#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt; cin >> tt;
    while (tt--){
        int n, m; cin >> n >> m;
        string s, t; cin >> s >> t;
        bool bad = false;
        for (int i = 1; i < m; i++){
            if (t[i] == t[i-1]){
                bad = true;
                break;
            }
        }
        if (bad){
            bool badbad = false;
            for (int i = 1; i < n; i++){
                if (s[i] == s[i-1]){
                    badbad = true; break;
                }
            }
            if (badbad){
                cout << "No\n";
            }
            else{
                cout << "Yes\n";
            }
        }
        else{
            bad = false;
            if (m % 2 == 1){
                for (int i = 0; i < n-1; i++){
                    if (s[i] == s[i+1] && s[i] == t[0]){
                        bad = true; break;
                    }
                }
                if (bad){
                    cout << "No\n";
                }
                else{
                    cout << "Yes\n";
                }
            }
            else{
                for (int i = 0; i < n-1; i++){
                    if (s[i] == s[i+1]){
                        bad = true; break;
                    }
                }
                if (bad){
                    cout << "No\n";
                }
                else{
                    cout << "Yes\n";
                }
            }
        }
    }
}