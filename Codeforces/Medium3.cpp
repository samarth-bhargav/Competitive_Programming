//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<pair<int,int>>a(n);
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        a[i] = {x,i};
    }
    sort(a.rbegin(),a.rend());
    int curr = 1e9, pastidx = 1e9;
    vector<int>ans(n);
    for (int i = 0; i < n; i++){
        if (a[i].first == curr){
            ans[a[i].second] = ans[pastidx];
        }
        else{
            ans[a[i].second] = i+1;
        }
        curr = a[i].first;
        pastidx = a[i].second;
    }
    for (auto & i : ans){
        cout << i << " ";
    }
    cout << "\n";
}

