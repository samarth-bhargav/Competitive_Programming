/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--) {
        bool alg = false;
        long long a, b, x, y, n;
        vector<long long> possans;
        cin >> a >> b >> x >> y >> n;
        if (n > b - y) {
            if (n-(b-y) > a - x) {
                possans.push_back(x * y);
            } else {
                possans.push_back((a-(n-(b-y))) * y);
            }
        }
        else {
            possans.push_back((b-n) * a);
        }
        if (n > a-x){
            if (n-(a-x) > b-y){
                possans.push_back(x * y);
            }
            else{
                possans.push_back((x)*(b-(n-(a-x))));
            }
        }
        else{
            possans.push_back((a-n) * b);
        }
        long long minx = 1e18;
        for (long long i : possans){
            minx = min(minx, i);
        }
        cout << minx << "\n";
    }
}

