#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

const int mxN = 1<<17, M = 998244353;
int dp[mxN][18];
long long powers[18][1001];
int rqq[1000][1000];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (long long i = 1; i <= 17; i++){
        long long x = 1;
        for (int p = 0; p < 1001; p++){
            powers[i][p] = ((x % M) + M) % M;
            x = ((x * i) % M + M) % M;
        }
    }
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        char c; cin >> c;
        a[i] = (c == '?' ? -1 : c - 'a');
    }
    for (int i = 0; i < n; i++){
        if (a[i] == -1){
            rqq[i][i] = 1;
        }
        else{
            rqq[i][i] = 0;
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            rqq[i][j] = rqq[i][j-1]+rqq[j][j];
        }
    }
    for (int j = 0; j < n; j++){
        //going from [0,j]
        int q_mark = 0, req = 0;
        int p1 = j / 2, p2 = (j + 1) / 2;
        while (p1 != -1){
            if (a[p1] == -1 && a[p2] == -1){
                q_mark++;
            }
            else if ((a[p1] == -1) ^ (a[p2] == -1)){
                if (a[p1] == -1){
                    req |= (1 << a[p2]);
                }
                else{
                    req |= (1 << a[p1]);
                }
            }
            else if (a[p1] != a[p2]){
                break;
            }
            int q_outside = 0;
            if (p1 != 0){
                q_outside += rqq[0][p1-1];
            }
            if (p2 != n-1){
                q_outside += rqq[p2+1][n-1];
            }
            for (int k = 1; k <= 17; k++){
                dp[req][k] += powers[k][q_outside+q_mark];
                dp[req][k] = (dp[req][k] % M + M) % M;
            }
//            cerr << "[" << p1 << ", " << p2 << "]: " << req << " " << q_mark+q_outside << "\n";
            p1--; p2++;
        }
    }
    for (int j = n-1; j >= 1; j--){
        //going from [j,n-1]
        int q_mark = 0, req = 0;
        int p1 = (j + n - 1) / 2, p2 = (j + n) / 2;
        while (p2 != n){
            if (a[p1] == -1 && a[p2] == -1){
                q_mark++;
            }
            else if ((a[p1] == -1) ^ (a[p2] == -1)){
                if (a[p1] == -1){
                    req |= (1 << a[p2]);
                }
                else{
                    req |= (1 << a[p1]);
                }
            }
            else if (a[p1] != a[p2]){
                break;
            }
            int q_outside = 0;
            if (p1 != 0){
                q_outside += rqq[0][p1-1];
            }
            if (p2 != n-1){
                q_outside += rqq[p2+1][n-1];
            }
            for (int k = 1; k <= 17; k++){
                dp[req][k] += powers[k][q_outside+q_mark];
                dp[req][k] = (dp[req][k] % M + M) % M;
            }
//            cerr << "[" << p1 << ", " << p2 << "]: " << req << " " << q_mark+q_outside << "\n";
            p1--; p2++;
        }
    }

    //essentially, u[req] represents the number of question marks/freedom we have
    //to manipulate given we have all the elements in the bits of req
    //now we can do sos dp to determine how much freedom we have with only
    //SOME of the elements in req
    for (int i = 0; i < 17; i++){
        for (int mask = 0; mask < mxN; mask++){
            if (mask & (1 << i)){
                for (int j = 1; j <= 17; j++){
                    dp[mask][j] += dp[mask ^ (1 << i)][j];
                    dp[mask][j] = (dp[mask][j] % M + M) % M;
                }
            }
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        string s; cin >> s; int x = 0;
        for (int j = 0; j < s.length(); j++){
            x |= (1 << (s[j] - 'a'));
        }
        cout << dp[x][s.length()] << "\n";
    }
//    cerr << powers[3][256] << "\n";
}
