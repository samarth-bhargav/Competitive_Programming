/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n; long long w;
        cin >> n >> w;
        multiset <pair<int,int>> vals;
        vector <int> vi;
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            vals.insert({x,i+1});
        }
        long long sum = 0;
        long long lo = (w+1)/2;
        while (true){
            if (lo <= sum && sum <= w){
                cout << vi.size() << "\n";
                for (int i : vi){
                    cout << i << " ";
                }
                cout << "\n";
                break;
            }
            if (vals.empty()){
                cout << -1 << "\n";
                break;
            }
            pair <long long,int> fi = {w-sum,1e9};
            auto it = vals.lower_bound(fi);
            it--;
            if (it == vals.end()){
                cout << -1 << "\n";
                break;
            }
            sum += it->first;
            vi.push_back(it->second);
            vals.erase(it);
        }
    }
}

