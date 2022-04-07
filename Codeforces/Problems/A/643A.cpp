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
int method (vector <int > vi){
    return *(lower_bound(vi.begin(), vi.end(), 0));
}
int to_int(char c){
    return c;
}
int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int a,b;
        vector <int> k;
        cin >> a >> b;
        for (int i = 0; i < to_string(a).length(); i++){
            k.push_back(to_int(to_string(a)[i]));
        }
        for (int i = 0; i < b; i++){
            k = method(k);
        }
    }

}

