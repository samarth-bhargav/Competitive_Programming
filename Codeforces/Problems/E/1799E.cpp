#include <bits/stdc++.h>

using namespace std;

const int mxN = 52;
const int INF = 1e9;

struct interval{
    int l, r, i, val, tprev, actual_l, actual_r;
    int lprev = -1, rprev = -1;
    interval(){}
    interval(int i, int l, int r, int val, int actual_l, int actual_r){
        this->l = l;
        this->r = r;
        this->i = i;
        this->val = val;
        this->actual_l = actual_l;
        this->actual_r = actual_r;
    }
    bool operator <(const interval &o) const{
        return this->val < o.val;
    }
    void setprev(interval &o, int t){
        this->lprev = o.actual_l;
        this->rprev = o.actual_r;
        this->tprev = t;
    }
    void setactual(int ll, int rr){
        this->actual_l = ll;
        this->actual_r = rr;
    }
};

interval dp0[mxN][mxN][mxN], dp0_s[mxN][mxN][mxN], dp1[mxN][mxN][mxN];
char g[mxN][mxN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++){
                cin >> g[i][j];
            }
        }
        //base case
        for (int i = 0; i <= n+1; i++){
            for (int j = 0; j <= m+1; j++){
                for (int k = 0; k <= m+1; k++){
                    dp0[i][j][k] = interval(0, 0, 0, INF, 0, 0);
                    dp1[i][j][k] = interval(0, 0, 0, INF, 0, 0);
                    dp0_s[i][j][k] = interval(0, 0, 0, INF, 0, 0);
                }
            }
        }
        int least_filled = INF, greatest_filled = -1;
        for (int i = 1; i <= m; i++){
            if (g[1][i] == '#'){
                least_filled = min(least_filled, i);
                greatest_filled = max(greatest_filled, i);
            }
        }
        for (int lb = 1; lb <= m; lb++){
            for (int ub = lb; ub <= m; ub++){
                if (lb <= least_filled && greatest_filled <= ub){
                    dp0[1][lb][ub] = interval(1, lb, ub, ub - lb + 1, lb, ub);
                    dp0_s[1][lb][ub] = interval(1, lb, ub, ub - lb + 1, lb, ub);
                }
            }
        }
//        for (int i = 1; i <= m; i++){
//            for (int j = i; j <= m; j++){
//                cerr << "i: " << 1 << " j: " << i << " k: " << j << " dp0[i][j][k]: " << dp0[1][i][j].val << "\n";
//            }
//        }
        //suffix min (smallest ranges first)
        for (int width = 0; width < m; width++){
            for (int lb = 1; lb + width <= m; lb++){
                dp0[1][lb][lb+width] = min({dp0[1][lb][lb+width], dp0[1][lb+1][lb+width], dp0[1][lb][lb+width-1]});
                dp0[1][lb][lb+width].setactual(lb, lb+width);
//                dp0[1][lb][lb+width].l = lb; dp0[1][lb][lb+width].r = lb+width;
//                dp0[1][lb][lb+width].l = min(dp0[1][lb][lb+width].l, lb);
//                dp0[1][lb][lb+width].r = max(dp0[1][lb][lb+width].r, lb+width);
            }
        }
        //suffix min (largest ranges first)
        for (int width = m-1; width >= 0; width--){
            for (int lb = 1; lb + width <= m; lb++){
                dp0_s[1][lb][lb+width] = min({dp0[1][lb][lb+width], dp0[1][lb-1][lb+width], dp0[1][lb][lb+width+1]});
                dp0_s[1][lb][lb+width].setactual(lb, lb+width);
//                dp0_s[1][lb][lb+width].l = lb; dp0_s[1][lb][lb+width].r = lb+width;
            }
        }
        //suffix min (smallest ranges first)
        for (int width = 0; width < m; width++){
            for (int lb = 1; lb + width <= m; lb++){
                dp0_s[1][lb][lb+width] = min({dp0_s[1][lb][lb+width], dp0_s[1][lb+1][lb+width], dp0_s[1][lb][lb+width-1]});
                dp0_s[1][lb][lb+width].setactual(lb, lb+width);
//                dp0_s[1][lb][lb+width].l = lb; dp0_s[1][lb][lb+width].r = lb+width;
//                dp0_s[1][lb][lb+width].l = min(dp0_s[1][lb][lb+width].l, lb);
//                dp0_s[1][lb][lb+width].r = max(dp0_s[1][lb][lb+width].r, lb+width);
            }
        }
        for (int i = 2; i <= n; i++){
            least_filled = INF, greatest_filled = -1;
            for (int j = 1; j <= m; j++){
                if (g[i][j] == '#'){
                    least_filled = min(least_filled, j);
                    greatest_filled = max(greatest_filled, j);
                }
            }
            for (int j = 1; j <= m; j++){
                for (int k = j; k <= m; k++){
                    if (j <= least_filled && greatest_filled <= k){
                        dp0[i][j][k] = interval(i, j, k, dp0[i-1][j][k].val + k - j + 1, j, k);
                        dp0[i][j][k].setprev(dp0[i-1][j][k], 0);
                        if (dp1[i-1][j][k] < dp0_s[i-1][j][k]){
                            dp1[i][j][k] = interval(i, j, k, dp1[i-1][j][k].val + k - j + 1, j, k);
                            dp1[i][j][k].setprev(dp1[i-1][j][k], 1);
                        }
                        else{
                            dp1[i][j][k] = interval(i, j, k, dp0_s[i-1][j][k].val + k - j + 1, j, k);
                            dp1[i][j][k].setprev(dp0_s[i-1][j][k], 2);
                        }
                    }
                }
            }
//            for (int j = 1; j <= m; j++){
//                for (int k = j; k <= m; k++){
//                    cerr << "i: " << i << " j: " << j << " k: " << k << " dp0[i][j][k]: " << dp0[i][j][k].val << "\n";
//                }
//            }
            //suffix min (smallest ranges first)
            for (int width = 0; width < m; width++){
                for (int lb = 1; lb + width <= m; lb++){
                    dp0[i][lb][lb+width] = min({dp0[i][lb][lb+width], dp0[i][lb+1][lb+width], dp0[i][lb][lb+width-1]});
                    dp0[i][lb][lb+width].setactual(lb, lb+width);
//                    dp0[i][lb][lb+width].l = lb; dp0[i][lb][lb+width].r = lb+width;
                }
            }
            //suffix min (largest ranges first)
            for (int width = m-1; width >= 0; width--){
                for (int lb = 1; lb + width <= m; lb++){
                    dp0_s[i][lb][lb+width] = min({dp0[i][lb][lb+width], dp0[i][lb-1][lb+width], dp0[i][lb][lb+width+1]});
                    dp0_s[i][lb][lb+width].setactual(lb, lb+width);
//                    dp0_s[i][lb][lb+width].l = lb; dp0_s[i][lb][lb+width].r = lb+width;
                }
            }
            //suffix min (smallest ranges first)
            for (int width = 0; width < m; width++){
                for (int lb = 1; lb + width <= m; lb++){
                    dp0_s[i][lb][lb+width] = min({dp0_s[i][lb][lb+width], dp0_s[i][lb+1][lb+width], dp0_s[i][lb][lb+width-1]});
                    dp0_s[i][lb][lb+width].setactual(lb, lb+width);
//                    dp0_s[i][lb][lb+width].l = min(lb, dp0_s[i][lb][lb+width].l);
//                    dp0_s[i][lb][lb+width].r = max(lb+width, dp0_s[i][lb][lb+width].r);
                }
            }
            //suffix min (largest ranges first)
            for (int width = m-1; width >= 0; width--){
                for (int lb = 1; lb + width <= m; lb++){
                    dp1[i][lb][lb+width] = min({dp1[i][lb][lb+width], dp1[i][lb-1][lb+width], dp1[i][lb][lb+width+1]});
                    dp1[i][lb][lb+width].setactual(lb, lb+width);
//                    dp1[i][lb][lb+width].l = lb; dp1[i][lb][lb+width].r = lb+width;
                }
            }
//            for (int j = 1; j <= m; j++){
//                for (int k = j; k <= m; k++){
//                    cerr << "After i: " << i << " j: " << j << " k: " << k << " dp1[i][j][k]: " << dp1[i][j][k].val << "\n";
//                }
//            }
//            for (int j = 1; j <= m; j++){
//                for (int k = j; k <= m; k++){
//                    cerr << "Parent i: " << i << " j: " << j << " k: " << k << " dp1[i][j][k]: " << dp1[i][j][k].l << " " << dp1[i][j][k].r << "\n";
//                }
//            }
        }
        interval ans = interval(0, 0, 0, INF, 0, 0);
        for (int j = 1; j <= m; j++){
            for (int k = j; k <= m; k++){
                ans = min(ans, dp0[n][j][k]);
                ans = min(ans, dp1[n][j][k]);
            }
        }
        char answer[n+1][m+1];
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++){
                answer[i][j] = '.';
            }
        }
        for (int i = n; i >= 1; i--){
            for (int j = ans.l; j <= ans.r; j++){
                answer[i][j] = '#';
            }
            if (ans.tprev == 0){
                ans = dp0[i-1][ans.lprev][ans.rprev];
            }
            else if (ans.tprev == 1){
                ans = dp1[i-1][ans.lprev][ans.rprev];
            }
            else{
                ans = dp0_s[i-1][ans.lprev][ans.rprev];
            }
        }
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++){
                cout << answer[i][j];
            }
            cout << "\n";
        }
        cout << "\n";
    }
}