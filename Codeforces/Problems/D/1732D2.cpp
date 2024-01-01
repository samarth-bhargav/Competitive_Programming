#include <bits/stdc++.h>

#define int long long
typedef long long ll;
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q; cin >> q;
    int thresh = sqrt(q);
    vector<pair<char, ll>> queries;
    map<int, int> chains;
    vector<pair<int, set<int>>> important_chains;
    unordered_set<int, custom_hash> values_used;
    for (int i = 0; i < q; i++){
        char c; int x;
        cin >> c >> x;
        queries.push_back({c, x});
        values_used.insert(x);
    }
    map<int,int> val_to_idx;
    for (int val : values_used){
        int j = 2;
        while (true){
            if (values_used.find(j * val) == values_used.end()){
                break;
            }
            j++;
        }
        chains[val] = j;
        if (j > thresh){
            set<int> s;
            for (int i = 1; i < j; i++){
                s.insert(i * val);
            }
            important_chains.push_back({val, s});
            val_to_idx[val] = important_chains.size()-1;
        }
    }
    unordered_set<int, custom_hash> curr_values;
    curr_values.insert(0LL);
    for (pair<char, ll> query : queries){
        char type = query.first;
        ll val = query.second;
        if (type == '+'){
            for (int i = 0; i < important_chains.size(); i++){
                auto elem = &important_chains[i];
                if (val % elem->first == 0 && val < chains[elem->first] * elem->first){
                    elem->second.erase(val);
                }
            }
            curr_values.insert(val);
        }
        else if (type == '-'){
            for (int i = 0; i < important_chains.size(); i++){
                auto elem = &important_chains[i];
                if (val % elem->first == 0 && val < chains[elem->first] * elem->first){
                    elem->second.insert(val);
                }
            }
            curr_values.erase(val);
        }
        else{
            if (val_to_idx.count(val)){
                //some sorta bin search?
                int idx = val_to_idx[val];
                if (important_chains[idx].second.empty()){
                    cout << chains[val] * val << "\n";
                    continue;
                }
                cout << *(important_chains[idx].second.begin()) << "\n";
            }
            else{
                for (int lo = 0; ; lo++){
                    if (!curr_values.count(lo * val)){
                        cout << lo * val << "\n";
                        break;
                    }
                }
            }
        }
    }
}