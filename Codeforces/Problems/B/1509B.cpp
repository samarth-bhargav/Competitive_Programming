#include <bits/stdc++.h>
using namespace std;

void solve(){
    int N; cin >> N;
    string s; cin >> s;
    int t = 0, m = 0;
    for (int i = 0; i < s.size(); i++){
        if (s[i] == 'T'){
            t++;
        }
        else{
            m++;
        }
    }
    if (m*2 != t){
        cout << "NO\n";
        return;
    }
    t = 0; m = 0;
    for (int i = 0; i < N; i++){
        if (s[i] == 'T'){
            t++;
        }
        else{
            m++;
        }
        if (m > t){
            cout << "NO\n";
            return;
        }
    }
    t = 0; m = 0;
    for (int i = N-1; i > 0; i--){
        if (s[i] == 'T'){
            t++;
        }
        else{
            m++;
        }
        if (m > t){
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--){
        solve();
    }
}

