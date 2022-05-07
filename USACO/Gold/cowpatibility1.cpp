#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e4;
map<set<int>, int> cows_containing;
set<int> flavors_liked[mxN];

int main(){
//    ifstream cin("cowpatibility.in");
//    ofstream cout("cowpatibility.out");

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> flavors(5);
    for (int i = 0; i < n; i++){
        for (auto & f : flavors){
            cin >> f;
        }
        set<int> temp;
        for (int mask = 1; mask < 32; mask++){
            for (int pos = 0; pos < 5; pos++){
                if ((mask >> pos) & 1){
                    temp.insert(flavors[pos]);
                }
            }
            cows_containing[temp]++;
            flavors_liked[i] = temp;
            temp.clear();
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++){
        vector<int> fs;
        for (int f : flavors_liked[i]){
            fs.push_back(f);
        }
        int compatible = 0;
        set<int> temp;
        for (int mask = 1; mask < 32; mask++){
            for (int pos = 0; pos < 5; pos++){
                if ((mask >> pos) & 1){
                    temp.insert(fs[pos]);
                }
            }
            if (__builtin_popcount(mask) % 2 == 1){
                compatible += (cows_containing[temp] - 1);
            }
            else{
                compatible -= (cows_containing[temp] - 1);
            }
            temp.clear();
        }
        ans += (n-1-compatible);
    }
    cout << ans/2 << "\n";
}
