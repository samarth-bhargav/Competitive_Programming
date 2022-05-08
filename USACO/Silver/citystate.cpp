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

int main() {
    setIO("citystate");
    int t;
    cin >> t;
    vector <pair <int,int>> stuff;
    while (t--){
        string s;
        cin >> s;
        s = s.substr(0,2);
        string k;
        cin >> k;
        string kstr = "";
        string sstr = "";
        for (int i = 0; i < 2; i++){
            kstr = kstr + to_string((int) k[i]);
            sstr = sstr + to_string((int) s[i]);
        }
        stuff.push_back(make_pair(stoi(sstr), stoi(kstr)));
    }
    int ans = 0;
    for (auto k: stuff){
        for (auto l: stuff){
            if (k.first == l.second && l.first == k.second){
                ans ++;
            }
        }
    }
    cout << ans/2 << "\n";
}

