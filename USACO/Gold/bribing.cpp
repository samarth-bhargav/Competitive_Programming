#include <bits/stdc++.h>
using namespace std;

const int mxN = 201, INF = 1e9;
vector<vector<vector<int>>> dp;

struct cow{
    int p, c, x;
    cow(int p, int c, int x){
        this->p = p;
        this->c = c;
        this->x = x;
    }
};

int main(){
    int n, a, b;
    cin >> n >> a >> b;
    dp = vector<vector<vector<int>>> (2, vector<vector<int>> (a+1, vector<int> (b+1)));
    vector<cow> cows;
    for (int i = 0; i < n; i++){
        int p, c, x;
        cin >> p >> c >> x;
        cows.push_back(cow(p, c, x));
    }
    for (int m = 0; m <= a; m++){
        for (int i = 0; i <= b; i++){
            dp[0][m][i] = (cows[0].c - i / cows[0].x - m <= 0 ? cows[0].p : 0);
        }
    }
    for (int cp = 1; cp < n; cp++){
        for (int m = 0; m <= a; m++){
            for (int i = 0; i <= b; i++){
                dp[1][m][i] = dp[0][m][i];
                //we want to buy last cow
                if (i == 0){
                    int mi = cows[cp].c;
                    if (cows[cp].c - i / cows[cp].x - mi <= 0 && m >= mi){
                        dp[1][m][i] = max(dp[1][m][i], dp[0][m-mi][i] + cows[cp].p);
                    }
                }
                else{
                    for (int mi = 0; mi <= m; mi++){
                        for (int ii = 0; ii <= i; ii++){
                            if (cows[cp].c - ii / cows[cp].x - mi <= 0){
                                dp[1][m][i] = max(dp[1][m][i], dp[0][m-mi][i-ii] + cows[cp].p);
                            }
                        }
                    }
                }
            }
        }
        dp[0] = dp[1];
    }
    cout << dp[0][a][b] << "\n";
}
