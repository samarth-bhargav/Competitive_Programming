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
vector <int> vi;
void sieve(int l){
    for (int i = 2; i <= sqrt(l); i++){
        if (l%i == 0){
            vi.push_back(i);
            vi.push_back(l/i);
            l /= i;
            sieve(l);
        }
        else{
            if (i == sqrt(l)){
                break;
            }
        }
    }
}
int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int n,k;
        cin >> n >> k;
        vi.push_back(1);
        vi.push_back(n);
        if (k >= n){
            cout << 1 << "\n";
        }
        else{
            sieve(n);
            sort(vi.begin(), vi.end());
            if (*lower_bound(vi.begin(), vi.end(), k) == n){
                cout << (n/(*(lower_bound(vi.begin(), vi.end(), k) - 1))) << "\n";
            }
            else{
                cout << n/(*lower_bound(vi.begin(), vi.end(), k)) << "\n";
            }
        }
        vi.clear();
    }
}

