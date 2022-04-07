/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        int ans = 0;
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            if (x == 1 || x == 3){
                ans++;
            }
        }
        cout << ans << "\n";
    }
}

