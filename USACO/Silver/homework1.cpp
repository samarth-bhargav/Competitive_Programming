/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("homework.in", "r", stdin);
    freopen("homework.out", "w", stdout);
    int t;
    cin >> t;
    double ar[t];
    double arcpy[t];
    for (int i = 0; i < t; i++){
        cin >> ar[i];
        arcpy[i] = ar[i];
    }
//    cout << "hi";
    sort(arcpy, arcpy+t);
    int prefix[t+1]; prefix[0] = 0;
    for (int i = 1; i <= t; i++){
        prefix[i] = prefix[i-1] + ar[i-1];
    }
    int currmin = 0;
    vector <pair<int,double>> ans;
    ans.emplace_back(-1e9, -1e9);
    for (int k = 1; k <= t-2; k++){
        if (ar[k-1] == arcpy[currmin]){
            currmin++;
        }
        if ((prefix[t]-prefix[k]-arcpy[currmin])/(t-k-1) > ans[0].second){
            ans.clear();
            ans.emplace_back(k,((prefix[t]-prefix[k]-arcpy[currmin])/(t-k-1)));
        }
        else if ((prefix[t]-prefix[k]-arcpy[currmin])/(t-k-1) == ans[0].second){
            ans.emplace_back(k,((prefix[t]-prefix[k]-arcpy[currmin])/(t-k-1)));
        }
        else{
            continue;
        }
    }
    for (auto & i : ans) cout << i.first << "\n";
}