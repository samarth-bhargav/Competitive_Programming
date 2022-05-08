/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>
using namespace std;


void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

int t,n;
vector <int> bales;
int ok(int x){
    vector <int> copy{bales};
    int cnt = 0;
    while (!copy.empty()){
        auto it = copy.begin();
        if (binary_search(copy.begin(), copy.end(), copy[0] + 2*x)){
            it = lower_bound(copy.begin(), copy.end(), copy[0] + 2*x) + 1;
        }
        else{
            it = lower_bound(copy.begin(), copy.end(), copy[0] + 2*x);
        }
        copy.erase(copy.begin(), it);
        cnt ++;
    }
    if (cnt > n){
        return 1;
    }
    else if(cnt == n){
        return 0;
    }
    else{
        return -1;
    }
}
int main() {
    setIO("angry");
    cin >> t >> n;
    while (t--){
        int c;
        cin >> c;
        bales.push_back(c);
    }
    sort(bales.begin(), bales.end());
    int lo = 0;
    int hi = 2000000000;
    while (hi - lo > 1){
        int mid = (lo + hi + 1)/2;
        if (ok(mid) == 1){
            lo = mid;
        }
        else if (ok(mid) == -1){
            hi = mid - 1;
        }
        else{
            hi = mid;
        }
    }
    if (ok(lo) == 0){
        cout << lo << "\n";
    }
    else{
        cout << hi << "\n";
    }
}

