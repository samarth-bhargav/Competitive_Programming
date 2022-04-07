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
vector <int> times;
int n,m,c;
int ok(int y){
    int buses = 0;
    vector <int> copy{times};
    while (!copy.empty()){
        auto it = copy.begin();
        if (binary_search(copy.begin(), copy.end(), copy[0] + y)){
            it = lower_bound(copy.begin(), copy.end(), copy[0] + y) + 1;
        }
        else{
            it = lower_bound(copy.begin(), copy.end(), copy[0] + y);
        }
        copy.erase(copy.begin(), it);
        buses ++;
    }
    if (buses > m){
        return 1;
    }
    else if(buses == m){
        return 0;
    }
    else{
        return -1;
    }
}
int main() {
    //setIO();
    cin >> n >> m >> c;
    while (n--){
        int x;
        cin >> x;
        times.push_back(x);
    }
    sort(times.begin(), times.end());
    int lo = 0;
    int hi = 2000000000;
    while (hi - lo > 1){
        int mid = (lo + hi + 1)/2;
        if (ok(mid) == 1){
            lo = mid;
        }
        else if(ok(mid) == -1){
            hi = mid-1;
        }
        else{
            hi = mid;
        }
    }
    if (ok(lo)){
        cout << lo << "\n";
    }
    else{
        cout << hi << "\n";
    }
}

