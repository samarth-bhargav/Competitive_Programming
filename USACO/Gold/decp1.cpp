#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    std::random_device rd;
    std::mt19937 g(rd());

    srand(time(0));

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

//    auto rnd = [&](int l, int r) {
//        return l + rand() % (r - l + 1);
//    };
//
    int n; cin >> n;
    vector<vector<int>> indices(n);
    for (int i = 0; i < n; i++){
        int l; cin >> l; l--;
        indices[l].push_back(i);
    }

    auto numgroups = [&](int label, int x){
        int grps = 1;
        bool just_created = true;
        int bgn = indices[label][0];
        for (int i = 1; i < indices[label].size(); i++){
            just_created = false;
            if (indices[label][i] - bgn > x){
                //create new group
                grps++;
                bgn = indices[label][i];
                just_created = true;
            }
        }
        return grps;
    };

    vector<vector<array<int,2>>> changes(n);

    for (int i = 0; i < n; i++){
        if (indices[i].empty()){
            continue;
        }
        int lo = 1;

        while (true){
            int curr_groups = numgroups(i, lo);
            changes[i].push_back({lo, curr_groups});
            int hi = n;
            while (lo < hi){
                int mid = (lo + hi) / 2;
                if (numgroups(i, mid) != curr_groups){
                    hi = mid;
                }
                else{
                    lo = mid+1;
                }
            }
            if (numgroups(i, lo) == curr_groups){
                break;
            }
        }
    }

    vector<int> pref(n+2, 0);

    auto add = [&](int a, int b, int x){
        pref[a] += x;
        pref[b+1] -= x;
    };

    for (int i = 0; i < n; i++){
        for (int j = 1; j < changes[i].size(); j++){
            add(changes[i][j-1][0], changes[i][j][0]-1, changes[i][j-1][1]);
        }
        if (!changes[i].empty()){
            add(changes[i].back()[0], n, changes[i].back()[1]);
        }
    }

//    dbg(changes);

    for (int i = 1; i <= n; i++){
        pref[i] = pref[i-1] + pref[i];
    }

    for (int i = 1; i <= n; i++){
        cout << pref[i] << "\n";
    }

}