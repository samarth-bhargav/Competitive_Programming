#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--){
        int n; cin >> n;
        string a, b; cin >> a >> b;
        int tether1[26][26];
        memset(tether1, 0, sizeof(tether1));
        for (int i = 0; i < n; i++){
            int c1 = a[i] - 97;
            int c2 = b[n-i-1] - 97;
            tether1[c1][c2]++;
        }
        bool bad = false;
        int odd_count = 0;
        for (int i = 0; i < 26; i++){
            if (bad){
                break;
            }
            for (int j = 0; j < 26; j++){
                if (i != j){
                    if ((tether1[i][j] + tether1[j][i]) & 1){
                        bad = true;
                        break;
                    }
                }
                else{
                    if (n%2 == 0 && (tether1[i][j] & 1)){
                        bad = true;
                        break;
                    }
                    else if (n%2 == 1 && (tether1[i][j] & 1)){
                        odd_count++;
                    }
                }
            }
        }
        if (bad || odd_count > 1){
            cout << "NO\n";
        }
        else{
            cout << "YES\n";
        }
    }
}
