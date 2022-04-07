#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

const int mxN = 5000;
int dp[mxN][mxN];
int num[mxN][mxN];
int a[mxN];

int main() {
    freopen("threesum.in","r",stdin);
    freopen("threesum.out","w",stdout);
    int n,q;
    cin >> n >> q;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    map<ll,int>occ;
    for (int i = 0; i < n-1; i++){
        occ[a[i]]++;
        //iterating starting point
        for (int j = i+1; j < n; j++){
            occ[a[j]]++;
            num[i][j] = occ[-(a[i]+a[j])];
            if (-(a[i]+a[j]) == a[j]){
                num[i][j]--;
            }
            if (-(a[i]+a[j]) == a[i]){
                num[i][j]--;
            }
        }
        occ.clear();
    }
    memset(dp,0,sizeof(dp));
    for (int i = n-1; i >= 0; i--){
        for (int j = i+1; j < n; j++){
            dp[i][j] = num[i][j]+dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1];
        }
    }
    for (int i = 0; i < q; i++){
        int x,y;
        cin >> x >> y; x--; y--;
        cout << dp[x][y] << "\n";
    }
}

