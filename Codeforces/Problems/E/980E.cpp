#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e6;
set<int> adj[mxN];
set<int> children[mxN];

//the following code doesn't work due to a faulty greedy algo

int main(){
    int n,k;
    cin >> n >> k;
    for (int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b; a--; b--;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    set<int> removable, independent;
    for (int i = 0; i < n; i++){
        if (adj[i].size() == 1){
            removable.insert(i);
        }
    }
    //independent has last node removed from branch
    set<int> removed;
    for (int i = 0; i < k; i++){
        int r = *removable.begin();
        int c = *adj[r].begin();
        removed.insert(r);
        removable.erase(removable.begin());
        independent.insert(r);
        for (int child : children[r]){
            independent.erase(child);
        }
        adj[c].erase(r);
        adj[r].erase(c);
        children[c].insert(r);
        if (adj[c].size() == 1 || adj[c].empty()){
            removable.insert(c);
        }
    }
    for (int node : removed){
        cerr << node+1 << " ";
    }
    cerr << "\n";
    //now let's compare the independent ones with the ones that are in removable
    //if anything in removable is less than independent, then we remove node in removable
    //and then add back the one in independent
    while (!(removable.empty() || independent.empty()) && *removable.begin() < *prev(independent.end())){
        bool bad = true;
        int a = *removable.begin();
        auto ub = independent.upper_bound(*removable.begin());
        bool ubdone = false;
        for (auto it = prev(independent.end()); !ubdone; it--){
            if (it == ub){
                ubdone = true;
            }
            int b = *it;
            if (children[a].find(b) == children[a].end()){
                removed.erase(b);
                for (int child : children[b]){
                    independent.insert(child);
                }
                //erase the 'a' node
                for (int child : children[a]){
                    independent.erase(child);
                }
                independent.insert(a);
                removed.insert(a);
                removable.insert(*adj[a].begin());
                children[*adj[a].begin()].insert(a);
                adj[*adj[a].begin()].erase(a);
                independent.erase(b);
                if (adj[*adj[a].begin()].size() == 1 || adj[*adj[a].begin()].empty()){
                    removable.insert(*adj[a].begin());
                }
                bad = false;
                removable.erase(a);
                break;
            }
            else{
                continue;
            }
        }
        if (bad){
            break;
        }
    }
    for (int node : removed){
        cout << node+1 << " ";
    }
    cout << "\n";
}
