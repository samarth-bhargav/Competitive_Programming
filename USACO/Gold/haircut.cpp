#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
 * Trying to find number of pairs (x,y) s.t.
    - x < y
    - A[x] > A[y]
 * Have BIT for 0 to N that initially has all 0s
 * Start from 0 and find first i s.t. A[i] = 0
 *
 * Find the number of elements to the left of that index and "remove" this index by
 * pushing back into BIT. All those elements to the left are 100% greater than A[i] since
 * we are still at 0 :)
 *
 * Now we go to the second (if it exists) i s.t. A[i] = 0 and since we just take number of elements to
 * left-1 since we don't count 0 (in the future, check this by looking at the query of i in the BIT)
 *
 * Add all the values cumulative from A[i] = 0 and store it in array: ans[0] = (the result)
 * Now we have the number of pairs (x,y) s.t. x < y and A[x] > A[y] for every A[y]
 *
 * When we change all the values above a certain j to j, we are actually just limiting A[y] to be less than j
 * since that's where all of our solutions arise (if A[y] >= j, both A[x] and A[y] are j after the change :D)
 *
 * So in order to find the solution to a particular j, just sum all ans[i] from i = 0 to i = j-1 and we're done :)
*/
#define int ll

struct ft{
    vector<int> bit;
    int n;
    ft(int x){
        n = x;
        bit = vector<int>(n,0);
    }
    void upd(int i, int d){
        for (; i < n; i = i | (i+1)){
            bit[i] += d;
        }
    }
    int qry(int r){
        int ret = 0;
        for (; r >= 0; r = (r & (r+1)) - 1){
            ret += bit[r];
        }
        return ret;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("haircut.in","r",stdin);
    freopen("haircut.out","w",stdout);
    int n; cin >> n;
    vector<int>a(n);
    for (auto & i : a){
        cin >> i;
    }
    ft b = ft(n+1);
    map<int,vector<int>>occ;
    for (int i = 0; i < n; i++){
        occ[a[i]].push_back(i);
    }
    vector<int>ans(n+1,0);
    for (int i = 0; i <= n; i++){
        for (auto & j : occ[i]){
            ans[i] += j - b.qry(j-1);
            b.upd(j,1);
        }
    }
    for (auto & i : ans){
        cerr << i << "\n";
    }
    long long c = 0;
    for (int i = 0; i < n; i++){
        cout << c << "\n";
        c += ans[i];
    }
}

