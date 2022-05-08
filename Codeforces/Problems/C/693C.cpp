#include <bits/stdc++.h>
using namespace std;

long long a[200001];
long long ans[200001];
bool vis[200001];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++){
            ans[i] = 0;
        }
        for (int i = 1; i <= n; i++){
            if (vis[i]){
                continue;
            }
            long long pos = i;
            vis[pos] = true;
            while (true){
                ans[i] += a[pos];
                pos += a[pos];
                if (pos > n) break;
                if (vis[pos]) break;
                vis[pos] = true;
            }
        }
        long long answer = -1e9;
        for (int i = 1; i <= n; i++){
            answer = max(answer, ans[i]);
        }
        cout << answer << "\n";
        memset(vis,0,sizeof(vis));
    }
}
