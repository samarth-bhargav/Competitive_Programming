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
        vector<int>a(n);
        int zero = 0, one = 0, two = 0;
        for (int i = 0; i < n; i++){
            cin >> a[i];
            a[i] %= 3;
            if (a[i] == 0) zero++;
            if (a[i] == 1) one++;
            if (a[i] == 2) two++;
        }
        int goal = n/3;
        int ans = 0;
        while (!(zero == goal && one == goal && two == goal)){
            if (one < goal){
                zero--;
                one++;
                ans++;
            }
            if (two < goal){
                one--;
                two++;
                ans++;
            }
            if (zero < goal) {
                two--;
                zero++;
                ans++;
            }
        }
        cout << ans << "\n";
    }
}

