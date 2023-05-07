#include <bits/stdc++.h>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        vector<vector<bool>> g(n, vector<bool> (m, false));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                char c; cin >> c;
                if (c == 'X') g[i][j] = true;
                else g[i][j] = false;
            }
        }
        auto og = g;
        //select first row
        for (int i = 0; i < m; i++){
            g[0][i] = true;
        }
        int start_col = (m % 3 == 1 ? 0 : 1);
        for (; start_col < m; start_col += 3){
            for (int i = 0; i < n; i++){
                g[i][start_col] = true;
            }
        }
        //check for validity
        start_col = (m % 3 == 1 ? 0 : 1);
        if (n >= 2){
            //number of rows is >= 2
            for (int i = 0; i < m; i++){
                if (og[1][i] && ((i - start_col) % 3 + 3) % 3 != 0){
                    if (i == 0 || i == 1){
                        //at the beginning
                        g[0][0] = false;
                    }
                    else if (i == m-2 || i == m-1){
                        //at the end
                        g[0][m-1] = false;
                    }
                    else{
                        //somewhere in middle
                        assert(og[1][i]);
                        if (((i - start_col) % 3 + 3) % 3 == 1){
                            //on right side
                            g[0][i] = false;
                            g[0][i+1] = false;
                            g[1][i+1] = true;
                        }
                        else{
                            g[0][i] = false;
                            g[0][i-1] = false;
                            g[1][i-1] = true;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cout << (g[i][j] ? 'X' : '.');
            }
            cout << "\n";
        }
    }
}
