#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        string s; cin >> s;
        int n = s.size();
        bool type1 = true;
        bool seen = false;
        for (int i = 0; i < n; i++){
            if (s[i] == ')'){
                seen = true;
            }
            if (seen && s[i] == '('){
                type1 = false;
                break;
            }
        }
        if (s == "()"){
            cout << "NO\n";
            continue;
        }
        if (type1){
            cout << "YES\n";
            for (int i = 0; i < n; i++){
                cout << "()";
            }
            cout << "\n";
        }
        else{
            cout << "YES\n";
            for (int i = 0; i < n; i++){
                cout << "(";
            }
            for (int i = 0; i < n; i++){
                cout << ")";
            }
            cout << "\n";
        }
    }
}