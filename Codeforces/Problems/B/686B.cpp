
/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 2e5+5;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    int ar[mxN];
    while (t--){
        int n;
        cin >> n;
        map<int,int> pos;
        memset(ar,0,sizeof(ar));
        int numberones = 0;
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            pos[x] = i;
            if (ar[x] == 2){
                continue;
            }
            ar[x]++;
            if (ar[x] == 1){
                numberones++;
            }
            if (ar[x] == 2){
                numberones--;
            }
        }
        if (numberones == 0){
            cout << -1 << "\n";
            continue;
        }
        for (int i = 1; i <= n; i++){
            if (ar[i] == 1){
                cout << pos[i]+1 << "\n";
                break;
            }
        }
    }
}

