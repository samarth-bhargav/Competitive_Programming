#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int> (m));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> a[i][j];
            }
        }
        vector<pair<vector<int>, int>> g;
        for (int i = 0; i < n; i++){
            g.emplace_back(a[i], i);
        }
        sort(g.begin(), g.end());
        int prmq[n][m], prMq[n][m], srmq[n][m], srMq[n][m];
        for (int r = 0; r < n; r++){
            prmq[r][0] = g[r].first[0];
            prMq[r][0] = g[r].first[0];
            for (int c = 1; c < m; c++){
                prmq[r][c] = min(prmq[r][c-1], g[r].first[c]);
                prMq[r][c] = max(prMq[r][c-1], g[r].first[c]);
            }
        }
        for (int r = 0; r < n; r++){
            srmq[r][m-1] = g[r].first.back();
            srMq[r][m-1] = g[r].first.back();
            for (int c = m-2; c >= 0; c--){
                srmq[r][c] = min(srmq[r][c+1], g[r].first[c]);
                srMq[r][c] = max(srMq[r][c+1], g[r].first[c]);
            }
        }
        int prpcMAX[n][m], prscMIN[n][m], srpcMIN[n][m], srscMAX[n][m];
        for (int c = 0; c < m; c++){
            prpcMAX[0][c] = prMq[0][c];
            for (int r = 1; r < n; r++){
                prpcMAX[r][c] = max(prpcMAX[r-1][c], prMq[r][c]);
            }
            srpcMIN[n-1][c] = prmq[n-1][c];
            for (int r = n-2; r >= 0; r--){
                srpcMIN[r][c] = min(srpcMIN[r+1][c], prmq[r][c]);
            }
        }
        for (int c = m-1; c >= 0; c--){
            prscMIN[0][c] = srmq[0][c];
            for (int r = 1; r < n; r++){
                prscMIN[r][c] = min(prscMIN[r-1][c], srmq[r][c]);
            }
            srscMAX[n-1][c] = srMq[n-1][c];
            for (int r = n-2; r >= 0; r--){
                srscMAX[r][c] = max(srscMAX[r+1][c], srMq[r][c]);
            }
        }
        bool solved = false;
        for (int k = 0; k < m-1; k++){
            if (solved){
                break;
            }
            for (int r = 0; r < n-1; r++){
                if (prpcMAX[r][k] < srpcMIN[r+1][k]){
                    if (srscMAX[r+1][k+1] < prscMIN[r][k+1]){
                        //this means [0,r] is blue, split is at k+1
                        cout << "YES\n";
                        string base = "";
                        for (int i = 0; i < n; i++){
                            base += 'R';
                        }
                        for (int i = 0; i <= r; i++){
                            base[g[i].second] = 'B';
                        }
                        cout << base << " " << k+1 << "\n";
                        solved = true;
                        break;
                    }
                }
            }
        }
        if (!solved){
            cout << "NO\n";
        }
    }
}
