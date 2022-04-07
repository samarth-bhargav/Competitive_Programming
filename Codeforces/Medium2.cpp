//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
map<int,int> factors(int n){
    map<int,int>ret;
    int k = sqrt(n);
    for (int i = 2; i <= k; i++){
        if (n%i == 0){
            ret[i]++;
            n /= i;
            i--;
        }
    }
    if (n != 1){
        ret[n]++;
    }
    return ret;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    map<int,int>mp = factors(n);
    for (auto & i : mp){
        cout << i.first << " " << i.second << "\n";
    }
}

