//babybeluga
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
        int ar[n][5];
        for (int i = 0; i < n; i++){
            for (int j = 0; j < 5; j++){
                cin >> ar[i][j];
            }
        }
        pair<int,int>best = {0,1e9};
        bool bad = false;
        for (int i = 0; i < n; i++){
            ll cur = 0;
            for (int j = 0; j < 5; j++){
                cur += ar[i][j];
            }
            if (cur < best.second){
                best = {i,cur};
                bad = false;
            }
            else if (cur == best.second){
                bad = true;
            }
        }
        if (bad){
            cout << -1 << "\n";
        }
        else{
            cout << best.first+1 << "\n";
        }
    }
}

