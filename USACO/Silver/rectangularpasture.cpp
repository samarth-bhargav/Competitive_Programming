#include <bits/stdc++.h>
using namespace std;

int dp[2500][2500]; //min
int dp1[2500][2500];

int main(){
    int n;
    cin >> n;
    vector<pair<int,int>>xsort(n);
    vector<pair<int,int>>ysort(n);
    for (int i = 0; i < n; i++){
        int a,b;
        cin >> a >> b;
        xsort[i] = {a,b};
        ysort[i] = {b,a};
    }
    sort(xsort.begin(),xsort.end());
    sort(ysort.begin(),ysort.end());
    map<pair<int,int>,int>mp;
    for (int i = 0; i < n; i++){
        mp[xsort[i]] = i+1;
    }
    vector<int>ot(n);
    for (int i = 0; i < n; i++){
        ot[i] = mp[{ysort[i].second,ysort[i].first}];
    }
    for (int i = 0; i < n; i++){
        dp[i][i] = ot[i];
        for (int j = i+1; j < n; j++){
            dp[i][j] = min(dp[i][j-1],ot[j]);
        }
    }
    for (int i = 0; i < n; i++){
        dp1[i][i] = ot[i];
        for (int j = i+1; j < n; j++){
            dp1[i][j] = max(dp1[i][j-1],ot[j]);
        }
    }
//    for (auto & i : ot){
//        cerr << i << " ";
//    }
//    cerr << "\n";
    int cmn = 0;
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            if (dp1[i][j]-dp[i][j]==j-i){
                cmn++;
            }
        }
    }
    cout << 1+(n*(n+1))-cmn << "\n";
}