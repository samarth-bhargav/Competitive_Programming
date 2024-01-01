#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s; cin >> s;
    int n = s.size();
    int cnt01 = 0, cnt10 = 0;
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (s[i] == 0 && s[j] == 1){
                cnt01++;
            }
            else if (s[i] == 1 && s[j] == 0){
                cnt10++;
            }
        }
    }
    if (cnt01 == cnt10){
        cout << "0\n";
        return 0;
    }
    if (cnt01 > cnt10){
        for (int i = 0; i < n; i++){
            s[i] = (s[i] == '0' ? '1' : '0');
        }
        swap(cnt01, cnt10);
    }
    int diff = cnt10 - cnt01;
    vector<int> idx1, idx0;
    for (int i = 0; i < n; i++){
        if (s[i] == 1){
            idx1.push_back(i);
        }
        else{
            idx0.push_back(i);
        }
    }
    unordered_set<int> dp[idx0.size()];
    for (int i = 0; i < idx0.size(); i++){
        dp[i].insert(0);
    }
    for (int i = 0; i < idx1.size(); i++){
        unordered_set<int> ndp[idx0.size()];
        for (int j = 0; j < idx0.size(); j++){
            ndp[j] = dp[j];
        }
        for (int j = 0; j < idx0.size(); j++){
            if (j == 0){
                ndp[j].insert()
            }
        }
        for (int j = 1; j < idx0.size(); j++){
            for (int k : dp[j-1]){
                dp[j].insert(k);
            }
        }
    }
}