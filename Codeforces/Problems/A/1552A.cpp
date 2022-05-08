//babybeluga
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
    while (t--){
        int n; cin >> n;
        string s; cin >> s;
        string ssort = s; sort(ssort.begin(),ssort.end());
        int cnt = 0;
        for (int i = 0; i < n; i++){
            if (s[i] != ssort[i]){
                cnt++;
            }
        }
        std::cout << cnt << "\n";
    }
}

