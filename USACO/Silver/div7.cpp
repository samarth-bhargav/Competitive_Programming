/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);
    int t;
    cin >> t;
    int ar[t];
    for (int i = 0; i < t; i++){
        int x;
        cin >> x;
        ar[i] = x%7;
    }
    int prefix[t+1]; prefix[0] = 0;
    for (int i = 1; i <= t; i++){
        prefix[i] = (prefix[i-1] + ar[i-1])%7;
    }
    map <int,int> start; map <int,int> finish;
    for (int i = 1; i <= t; i++){
        if (finish.find(prefix[i]) == finish.end()){
            finish.insert(make_pair(prefix[i],i));
        }
        if (start.find(prefix[i]) == start.end()){
            start.insert(make_pair(prefix[i],i));
        }
        finish[prefix[i]] = i;
    }
    int ans = 0;
    for (auto & i : start){
        ans = max(ans, finish[i.first] - i.second);
    }
    cout << ans << "\n";
}

