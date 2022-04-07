/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

ll dp[2001][2001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N; cin >> N;
    vector<int>A(N+1); A[0] = -1e9;
    for (int i = 1; i <= N; i++){
        cin >> A[i];
    }
    sort(A.begin(),A.end());
    for (int i = 1; i <= N; i++){
        dp[i][i] = 0;
    }
    for (int i = 1; i <= N; i++){
        for (int j = i+1; j <= N; j++){
            dp[i][j] = dp[i][j-1] + A[j] - A[i];
        }
    }
    int pos1 = 1, pos2 = N;
    ll ans = 0;
    while (pos1 < pos2){
        ans += A[pos2] - A[pos1];
        ll first = dp[pos1+1][pos2];
        ll second = dp[pos1][pos2-1];
        if (first < second){
            pos1++;
        }
        else{
            pos2--;
        }
    }
    cout << ans << "\n";
}

