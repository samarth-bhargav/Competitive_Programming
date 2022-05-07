#include <bits/stdc++.h>
using namespace std;

//for usaco grader
namespace std {
    template<>
    struct hash<__uint128_t> {
        size_t operator()(__uint128_t var) const {
            return std::hash<uint64_t>{}((uint64_t)var ^ (uint64_t)(var >> 64));
        }
    };
}

const int mxN = 5e4;
unordered_map<__uint128_t, int> cows_containing;
vector<int> flavors_liked[mxN];

int main(){
    ifstream cin("cowpatibility.in");
    ofstream cout("cowpatibility.out");

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> flavors(5);
    for (int i = 0; i < n; i++){
        for (auto & f : flavors){
            cin >> f;
        }
        sort(flavors.begin(), flavors.end());
        __uint128_t temp = 0;
        for (int mask = 1; mask < 32; mask++){
            for (int pos = 0; pos < 5; pos++){
                if ((mask >> pos) & 1){
                    temp *= 10000000;
                    temp += flavors[pos];
                }
            }
            cows_containing[temp]++;
            flavors_liked[i] = flavors;
            temp = 0;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++){
        vector<int> fs;
        for (int f : flavors_liked[i]){
            fs.push_back(f);
        }
        int compatible = 0;
        __uint128_t temp = 0;
        for (int mask = 1; mask < 32; mask++){
            for (int pos = 0; pos < 5; pos++){
                if ((mask >> pos) & 1){
                    temp *= 10000000;
                    temp += fs[pos];
                }
            }
            if (__builtin_popcount(mask) % 2 == 1){
                compatible += (cows_containing[temp] - 1);
            }
            else{
                compatible -= (cows_containing[temp] - 1);
            }
            temp = 0;
        }
        ans += (n-1-compatible);
    }
    cout << ans/2 << "\n";
}
