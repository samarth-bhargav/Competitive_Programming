/*
ID: samarth10
LANG: C++11
TASK:
*/
#include <bits/stdc++.h>

using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}

int ans = 0;
vector <int> nums;

bool ok(int a){
    int sub = 0;
    vector <int> numss;
    numss = nums;
    for (int i = 0; i < numss.size(); i++){
        if (binary_search(numss.begin(), numss.end(), a - numss[i])){
            auto x = lower_bound(numss.begin(), numss.end(), a-numss[i]);
            numss.erase(numss.begin() + i - 1);
            numss.erase(x-1);
            sub++;
            i = 0;
        }
    }
    if (sub > ans){
        int k = ans;
        ans = sub;
        return true;
    }
    else{
        return false;
    }
    return false;
}
int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            nums.push_back(x);
        }
        int lo = 1;
        int hi = 14;
        int res = -1;
        sort(nums.begin(), nums.end());
        while (lo != hi){
            int mid = (lo + hi)/2;
            if (ok(mid)){
                cout << "hi" << "\n";
                cout << mid;
                res = mid;
                hi = mid-1;
            }
            else{
                lo = mid;
                cout << mid << endl;
            }
        }
        cout << ans << "\n";
        nums.clear();
    }
}