/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--){
        int n; string s;
        cin >> n >> s;
        deque<int>a;
        int curr = 1;
        for (int i = 1; i < n; i++){
            if (s[i] == s[i-1]){
                curr++;
            }
            else{
                a.push_back(curr);
                curr = 1;
            }
        }
        a.push_back(curr);
        int it = 0;
        map <int,int> mp;
        for (int i = 0; i < a.size(); i++){
            if (a[i] != 1){
                mp.insert(make_pair(i,a[i]));
            }
        }
        int pos = 0;
        if (n == 1){
            cout << 1 << "\n";
            continue;
        }
        while (true){
            if (pos >= n-1){
                break;
            }
            if (a[pos] != 1){
                a[pos] = 0;
                it++;
                mp.erase(pos);
                pos++;
            }
                a[pos] = 0;
                pos++;
            }
        }
        cout << it << "\n";
    }
}

