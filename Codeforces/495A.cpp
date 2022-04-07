/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

vector<int> factors(int x){
    vector<int>ret;
    for (int i = 1; i <= sqrt(x); i++){
        if (x%i == 0){
            ret.push_back(i);
            if (i != sqrt(x)){
                ret.push_back(x/i);
            }
        }
    }
    sort(ret.begin(),ret.end());
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int a,b;
    cin >> a >> b;
    if (a == b){
        cout << "infinity" << "\n";
        return 0;
    }
    if (b > a){
        cout << 0 << "\n";
        return 0;
    }
    vector<int>fac = factors(a-b);
    for (auto & i : fac){
        cerr << i << " ";
    }
    cerr << endl;
    int higher = fac.end() - upper_bound(fac.begin(),fac.end(),b);
    cout << higher << "\n";
}

