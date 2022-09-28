#include <bits/stdc++.h>
using namespace std;

const int mxN = 1000;
int g[mxN][mxN];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cin >> g[i][j];
            }
        }
        set<int> check;
        stack<int> to_remove;
        set<int> kswap;
        map<pair<int,int>, int> mp;
        for (int i = 1; i < n; i++){
            check.insert(i);
        }
        int bound = 0;
        while (bound != n && !check.empty()){
            bool in_bound = kswap.find(bound) != kswap.end();
            for (int x : check){
                //g[bound][x] is the top, g[x][bound] is the left
                int bound_t = bound, x_t = x;
                if (bound > x){
                    swap(bound_t, x_t);
                }
                if (g[bound_t][x_t] > g[x_t][bound_t]){
                    to_remove.push(x);
                    if (mp.find({x, bound}) != mp.end()){
                        if (mp[{x, bound}] > x){
                            kswap.erase(mp[{x, bound}]);
                            kswap.insert()
                        }
                    }
                }
                else if (g[bound_t][x_t] < g[x_t][bound_t]){
                    to_remove.push(x);
                    if (mp.find({x, bound}) != mp.end()){
                        if (mp[{x,bound}] > x){
                            kswap.erase(mp[{x,bound}]);
                            kswap.insert(x);
                        }
                    }
                    else{
                        mp[{bound, x}] = x;
                        kswap.insert(x);
                    }
                }
            }
            while (!to_remove.empty()){
                check.erase(to_remove.top());
                to_remove.pop();
            }
            bound++;
        }
        for (int i = 0; i < n; i++){
            for (int j = i+1; j < n; j++){
                bool one = kswap.find(i) != kswap.end();
                bool two = kswap.find(j) != kswap.end();
                if (one ^ two){
                    swap(g[i][j], g[j][i]);
                    cerr << i << " " << j << "\n";
                }
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cout << g[i][j] << " ";
            }
            cout << "\n";
        }
    }
}
