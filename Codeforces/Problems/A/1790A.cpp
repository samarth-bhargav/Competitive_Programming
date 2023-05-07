#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string pi = "3141592653589793238462643383279502884197169399";
    int t;
    cin >> t;
    while (t--){
        string s; cin >> s;
        int ans = 0;
        for (int i = 0; i < s.size(); i++){
            if (s[i] == pi[i]){
                ans++;
            }
            else{
                break;
            }
        }
        cout << ans << "\n";
    }
}
