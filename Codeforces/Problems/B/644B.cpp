/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>
using namespace std;

/*
void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
*/

int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        vector <int> stren;
        int c;
        cin >> c;
        for (int i = 0; i < c; i++){
            int k;
            cin >> k;
            stren.push_back(k);
        }
        sort(stren.begin(), stren.end());
        int maxdiff = 1000000000;
        int curr;
        for (int i = 1; i < stren.size(); i++){
            maxdiff = min(maxdiff, stren[i] - stren[i-1]);
        }
        cout << maxdiff << "\n";
    }
}

