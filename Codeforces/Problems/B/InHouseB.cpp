#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t; cin >> n >> t;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int cnt = 0;
    int time = 0;
    int tot_time = 0;
    for (int i = 0; i < n; i++){
        if (time + a[i] <= t){
            time += a[i];
            tot_time += time;
            cnt++;
        }
        else{
            break;
        }
    }
    cout << cnt << " " << tot_time << "\n";
}