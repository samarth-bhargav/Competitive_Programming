/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

/*
*/
#define int int64_t
const int M = 1e9+7;

int ans[200005];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    int ar[10]; memset(ar,0,sizeof(ar));
    ar[9] = 1; ans[0] = 1;
    for (int i = 1; i <= 200004; i++){
        int curr[10];
        for (int j = 0; j < 10; j++){
            curr[j] = ar[j];
        }
        ar[0] = ((ar[0] + curr[9])%M+M)%M;
        ar[1] = ((ar[1] + curr[9])%M+M)%M;
        ans[i] = ((ans[i-1] + curr[9])%M+M)%M;
        ar[9] = 0;
        for (int j = 1; j <= 9; j++){
            ar[j] = (((ar[j] + curr[j-1])%M)+M)%M;
            ar[j-1] = (((ar[j-1] - curr[j-1])%M)+M)%M;
        }
    }
    while (t--){
        int n,m;
        cin >> n >> m;
        int a[10]; memset(a,0,sizeof(a));
        while (n != 0){
            a[n%10] = (a[n%10] + 1)%M;
            n /= 10;
        }
        int answer = 0;
        for (int i = 0; i < 10; i++){
            int x = m-(9-i);
            if (x < 0){
                answer += a[i];
                continue;
            }
            answer = (answer + ans[x]*a[i])%M;
        }
        cout << answer << "\n";
    }
}

