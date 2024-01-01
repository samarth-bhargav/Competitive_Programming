#include <bits/stdc++.h>

using namespace std;

#define int long long

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
//        return x;
    }

    size_t compute_hash(int x){
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
} hash_gen;

const int mxN = 1e3;
int n, k;
int xor_hsh[mxN];
vector<vector<int>> orders;
vector<vector<int>> location_of_idx;
vector<int> parent(mxN);

void find_ceo(int reference_value, unordered_set<int> previous_parents, int p=-1){
    vector<array<int, 2>> relevant_intervals;
    int interval_size = -1;
    for (int i = 0; i < k; i++){
        int loc_of_ref = location_of_idx[i][reference_value];
        int lb, ub;
        for (ub = loc_of_ref; ub < n && previous_parents.find(orders[i][ub]) == previous_parents.end(); ub++){}
        for (lb = loc_of_ref; ~lb && previous_parents.find(orders[i][lb]) == previous_parents.end(); lb--){}
        relevant_intervals.push_back({lb+1, ub-1});
        if (interval_size == -1) interval_size = ub - lb;
        assert(interval_size == ub - lb);
        if (ub - lb == 2){
            //it is a leaf node
            parent[reference_value] = p;
            return;
        }
    }
    vector<int> xor_hash_back(k, 0), xor_hash_front(k, 0);
    int ceo = -1;
    for (int i = 0; i < interval_size-1; i++){
        //consider i+1, interval_size-i-2 as the ceo
        for (int j = 0; j < k; j++){
            xor_hash_front[j] ^= xor_hsh[orders[j][relevant_intervals[j][0] + i]];
            xor_hash_back[j] ^= xor_hsh[orders[j][relevant_intervals[j][1] - i]];
        }
        int fixed = xor_hash_front[0];
        bool bad = false;
        for (int j = 1; j < k; j++){
            if (xor_hash_front[j] == fixed || xor_hash_back[j] == fixed){
                continue;
            }
            else{
                bad = true;
                break;
            }
        }
        if (!bad){
            ceo = orders[0][relevant_intervals[0][0]+i+1];
            break;
        }
    }
    assert(ceo != -1);
    previous_parents.insert(ceo);
    find_ceo(orders[0][location_of_idx[0][ceo]+1], previous_parents, ceo);
    find_ceo(orders[0][location_of_idx[0][ceo]-1], previous_parents, ceo);
    parent[ceo] = p;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++){
        xor_hsh[i] = hash_gen.compute_hash(i);
    }
    orders.resize(k, vector<int>(n));
    location_of_idx.resize(k, vector<int>(n));
    for (int i = 0; i < k; i++){
        for (int j = 0; j < n; j++){
            cin >> orders[i][j];
            orders[i][j]--;
            location_of_idx[i][orders[i][j]] = j;
        }
    }
    find_ceo(0, {});
    for (int i = 0; i < n; i++){
        cout << (parent[i] == -1 ? parent[i] : parent[i]+1) << " ";
    }
    cout << "\n";
}