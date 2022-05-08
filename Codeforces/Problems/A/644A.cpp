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
        int a,b;
        cin >> a >> b;
        cout << pow(max(min(a + a, b + b), max(a,b)), 2) << "\n";
    }
}

