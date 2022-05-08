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
        int n,k;
        cin >> n >> k;
        if ((n-1)/2 < k){
            cout << -1 << "\n";
            continue;
        }
        int a[n]; memset(a,0,sizeof(a));
        int pos = 1;
        for (int i = n-k+1; i <= n; i++){
            a[pos] = i;
            pos+=2;
        }
        pos = 0;
        for (int i = 1; i <= n-k; i++){
            a[pos] = i;
            pos++;
            while (a[pos] != 0){
                pos++;
            }
        }
        for (auto & i : a){
            cout << i << " ";
        }
        cout << "\n";
    }
}

