#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream cin("hps.in");
    ofstream cout("hps.out");
    int n;
    cin >> n;
    char dp[n];
    for (int i = 0; i < n; i++){
        cin >> dp[i];
    }
    int ans = -1e9;
    int init;
    //count H & P
    init = count(dp,dp+n,'H');
    ans = max(ans,init);
    for (int i = 0; i < n; i++){
        if (dp[i] == 'S'){
            init++;
        }
        if (dp[i] == 'H'){
            init--;
        }
        ans = max(ans,init);
    }
    //count H & S
    init = count(dp,dp+n,'P');
    ans = max(ans,init);
    for (int i = 0; i < n; i++){
        if (dp[i] == 'P'){
            init--;
        }
        if (dp[i] == 'S'){
            init++;
        }
        ans = max(ans,init);
    }
    //count P & S
    init = count(dp,dp+n,'P');
    ans = max(ans,init);
    for (int i = 0; i < n; i++){
        if (dp[i] == 'H'){
            init++;
        }
        if (dp[i] == 'P'){
            init--;
        }
        ans = max(ans,init);
    }
    //count P & H
    init = count(dp,dp+n,'S');
    ans = max(ans,init);
    for (int i = 0; i < n; i++){
        if (dp[i] == 'S'){
            init--;
        }
        if (dp[i] == 'H'){
            init++;
        }
        ans = max(ans,init);
    }
    //count S & H
    init = count(dp,dp+n,'S');
    ans = max(ans,init);
    for (int i = 0; i < n; i++){
        if (dp[i] == 'S'){
            init--;
        }
        if (dp[i] == 'P'){
            init++;
        }
        ans = max(ans,init);
    }
    //count S & P
    init = count(dp,dp+n,'H');
    for (int i = 0; i < n; i++){
        if (dp[i] == 'H'){
            init--;
        }
        if (dp[i] == 'P'){
            init++;
        }
        ans = max(ans,init);
    }
    cout << ans << "\n";
}