#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mxN = 3e5, L = 20;
int anc[mxN][L], c[mxN], g[mxN]; //sum[i][j] = sum of i's 2^j ancestors excluding itself

int ancestor(int x, int d){
    for (int i = 0; i < L; i++){
        if ((d >> i) & 1){
            x = anc[x][i];
            if (x == -1){
                return -1;
            }
        }
    }
    return x;
}

int32_t main(){
    int q, a0, c0;
    cin >> q >> a0 >> c0;
    g[0] = a0;
    c[0] = c0;

    memset(anc, -1, sizeof(anc));
    for (int qq = 1; qq <= q; qq++){
        int t; cin >> t;
        if (t == 1){
            int pi, ai, ci;
            cin >> pi >> ai >> ci;
            g[qq] = ai; c[qq] = ci;
            anc[qq][0] = pi;
            for (int i = 1; i < L; i++){
                if (anc[qq][i-1] == -1){
                    anc[qq][i] = -1;
                    continue;
                }
                anc[qq][i] = anc[anc[qq][i-1]][i-1];
            }
        }
        else{
            int vi, wi;
            cin >> vi >> wi;
            //binary search to find last 'half full'
//            cout << "hi1\n";
            int lo = 0, hi = mxN;
            while (lo < hi){
                int mid = (lo + hi + 1) / 2;
                int node = ancestor(vi, mid);
                if (node == -1){
                    hi = mid-1;
                    continue;
                }
                if (g[node] == 0){
                    hi = mid-1;
                }
                else{
                    lo = mid;
                }
            }
            int ans = 0;
            int original_wi = wi;
//            cout << "hi2\n";
            while (wi > 0 && lo >= 0){
                int node = ancestor(vi, lo);
                if (g[node] > wi){
                    ans += (c[node] * wi);
                    g[node] -= wi;
                    wi = 0;
                    lo--;
                    continue;
                }
                else{
                    ans += (c[node] * g[node]);
                    wi -= g[node];
                    g[node] = 0;
                }
                lo--;
            }
            cout << original_wi - wi << " " << ans << "\n";
            fflush(stdout);
        }
    }
//    cout << ancestor(2, 0) << "\n";
}
