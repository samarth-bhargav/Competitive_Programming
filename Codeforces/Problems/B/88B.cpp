/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}


int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int n,m,x,y;
        cin >> n >> m >> x >> y;
        char space[n][m];
        for (int i = 0; i < n; i++){
            for (int k = 0; k < m; k++){
                cin >> space[i][k];
            }
        }
        if (x*2 <= y || m == 1){
            int count = 0;
            for (int i = 0; i < n; i++){
                for (int k = 0; k < m; k++){
                    if (space[i][k] == '.'){
                        count ++;
                    }
                }
            }
            cout << count*x << "\n";
        }
        else{
            int ans = 0;
            for (int i = 0; i < n; i++){
                for (int k = 0; k <= m - 1; k++){
                    if (k == m-1){
                        if(space[i][k] == '.'){
                            ans += x;
                        }
                        else{
                            continue;
                        }
                    }
                    else{
                        if (space[i][k] == '.' && space[i][k+1] == '.'){
                            ans += y;
                            k ++;
                        }
                        else if(space[i][k] == '.'){
                            ans += x;
                        }
                        else{
                            continue;
                        }
                    }
                }
            }
            cout << ans << "\n";
        }
    }
}

