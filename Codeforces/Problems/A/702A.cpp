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
        for (auto & i : a){
            cin >> i;
        }
        int ans = 0;
        for (int i = 1; i < n; i++){
            int one = min(a[i-1], a[i]);
            int two = max(a[i-1], a[i]);
            if (one*2 >= two){
                continue;
            }
            while (one < two){
                one *= 2;
                ans++;
            }
            ans--;
        }
        cout << ans << "\n";
    }
}

