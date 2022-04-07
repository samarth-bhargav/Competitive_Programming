/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, l, r, s;
        cin >> n >> l >> r >> s;
        set<int> range;
        set<int>values;
        for (int i = 1; i <= n; i++){
            values.insert(i);
        }
        while (s > 0){
            auto it = values.lower_bound(s);

        }
    }
}

