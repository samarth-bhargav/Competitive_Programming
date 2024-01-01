#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

const int INF = 1e9;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        s[i] = c - '0';
    }

    vector<array<int, 2>> ranges;
    for (int i = 0; i < m; i++) {
        int li, ri;
        cin >> li >> ri;
        li--;
        ri--;
        ranges.push_back({li, ri});
    }
    vector<int> ones;
    ordered_set active;
    for (int i = 0; i < n; i++) {
        active.insert(i);
    }
    int tot = count(s.begin(), s.end(), 1);
    for (int i = 0; i < m; i++) {
        int li = ranges[i][0], ri = ranges[i][1];
        auto it = active.lower_bound(li);
        vector<int> to_remove;
        for (; it != active.end() && *it <= ri; it++){
            ones.push_back(*it);
            to_remove.push_back(*it);
        }
        for (int idx: to_remove) {
            active.erase(idx);
        }
    }
    int num_switches = 0;
    vector<int> occ(n, INF);
    for (int i = 0; i < ones.size(); i++){
        occ[ones[i]] = i;
    }
    for (int i = 0; i < n; i++){
        if (s[i] == 0 && occ[i] < tot){
            num_switches++;
        }
    }
    for (int i = 0; i < q; i++){
        int x; cin >> x; x--;
        int old_tot = tot;
        if (s[x] == 0) tot++;
        else tot--;
        if (tot > ones.size()){
            if (occ[x] < ones.size()){
                if (s[x]){
                    cout << num_switches+1 << "\n";
                    num_switches++;
                }
                else{
                    cout << num_switches-1 << "\n";
                    num_switches--;
                }
            }
            else{
                cout << num_switches << "\n";
            }
            s[x] ^= 1;
            continue;
        }
        else if (old_tot > ones.size()){
            if (occ[x] < ones.size()){
                cout << num_switches+1 << "\n";
                num_switches++;
            }
            else{
                cout << num_switches << "\n";
            }
            s[x] ^= 1;
            continue;
        }
        if (tot == 0){
            num_switches = 0;
            cout << 0 << "\n";
            s[x] ^= 1;
            continue;
        }
        if (old_tot < tot){
            //adding an element
            if (occ[x] == tot-1){
                //we just added the last element ourselves
                cout << num_switches << "\n";
            }
            else if (occ[x] < tot-1){
                //the element we flipped was already there
                if (s[ones[tot-1]]){
                    cout << num_switches-1 << "\n";
                    num_switches--;
                }
                else{
                    cout << num_switches << "\n";
                }
            }
            else{
                //the element we flipped didn't ever play a role
                if (s[ones[tot-1]]){
                    cout << num_switches << "\n";
                }
                else{
                    cout << num_switches+1 << "\n";
                    num_switches++;
                }
            }
        }
        else{
            //removing an element
            if (occ[x] == old_tot-1){
                //we just removed the last element
                cout << num_switches << "\n";
            }
            else if (occ[x] < old_tot-1){
                //the element we flipped was already there
                if (!s[ones[old_tot-1]]){
                    cout << num_switches << "\n";
                }
                else{
                    cout << num_switches+1 << "\n";
                    num_switches++;
                }
            }
            else{
                //didn't play a role
                cout << num_switches << "\n";
            }
        }
        s[x] ^= 1;
    }
}