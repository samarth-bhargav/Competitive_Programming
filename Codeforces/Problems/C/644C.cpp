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
        vector <int> vi;
        int k;
        cin >> k;
        int even = 0;
        int odd = 0;
        for (int i = 0; i < k; i++){
            int c;
            cin >> c;
            if (c%2 == 0){
                even ++;
            }
            else{
                odd ++;
            }
            vi.push_back(c);
        }
        int adj = 0;
        sort(vi.begin(), vi.end());
        for (int i = 1; i < vi.size(); i++){
            if (vi[i] - vi[i-1] == 1){
                adj ++;
            }
        }
        if (odd%2 == 1 && even%2 == 1 && adj > 0){
            cout << "YES" << "\n";
        }
        else if(odd%2 == 0 && even%2 == 0){
            cout << "YES" << "\n";
        }
        else{
            cout << "NO" << "\n";
        }
    }
}

