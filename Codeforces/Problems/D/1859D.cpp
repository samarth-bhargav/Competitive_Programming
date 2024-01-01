#include <bits/stdc++.h>

using namespace std;

struct rng{
    int id, l, r, a, b;
    rng(int id, int l, int r, int a, int b){
        this->id = id;
        this->l = l;
        this->r = r;
        this->a = a;
        this->b = b;
    }
    rng(){}
    bool operator <(const rng &o) const{
        return this->r < o.r;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<rng> ranges(n);
        for (int i = 0; i < n; i++){
            cin >> ranges[i].l >> ranges[i].r >> ranges[i].a >> ranges[i].b;
        }
        int q; cin >> q;
        vector<array<int, 2>> queries(q);
        for (int i = 0; i < q; i++){
            cin >> queries[i][0];
            queries[i][1] = i;
        }
        //sort in order of increasing r value
        sort(queries.begin(), queries.end());
        sort(ranges.begin(), ranges.end());
        set<array<int, 2>> inner_ranges; //stores active inner endpoints. {coord, id}
        set<array<int, 3>> active; // {coord, type, id}
        for (int i = 0; i < n; i++){
            active.insert({ranges[i].l, 0, i});
            active.insert({ranges[i].r, 1, i});
//            active.insert({ranges[i].a, 2, i});
//            active.insert({ranges[i].b, 3, i});
        }
        set<array<int,2>> range_to_ans;
        vector<int> ans(q);
        while (!active.empty()){
            array<int, 3> tp = *prev(active.end());
            active.erase(tp);
            if (inner_ranges.empty()){
                range_to_ans.insert({tp[0], tp[0]});
            }
            else{
                int greatest_ep = (*prev(inner_ranges.end()))[0];
                auto f_lower = range_to_ans.upper_bound({greatest_ep+1, -1});
                if (f_lower != range_to_ans.begin()){
                    f_lower--;
                    range_to_ans.insert({tp[0], max(greatest_ep, (*f_lower)[1])});
                }
                else{
                    range_to_ans.insert({tp[0], greatest_ep});
                }
            }
            while (!queries.empty() && tp[0] <= queries.back()[0]){
                if (inner_ranges.empty()){
                    ans[queries.back()[1]] = queries.back()[0];
                }
                else{
                    int greatest_ep = (*prev(inner_ranges.end()))[0];
                    ans[queries.back()[1]] = max(queries.back()[0], greatest_ep);
                    auto f_lower = range_to_ans.upper_bound({greatest_ep+1, -1});
                    if (f_lower != range_to_ans.begin()){
                        f_lower--;
                        ans[queries.back()[1]] = max(ans[queries.back()[1]], (*f_lower)[1]);
                    }
                }
                queries.pop_back();
            }
            if (tp[1] == 0){
                inner_ranges.erase({ranges[tp[2]].b, tp[2]});
            }
            else if (tp[1] == 1){
                inner_ranges.insert({ranges[tp[2]].b, tp[2]});
            }
        }
        for (int i = 0; i < q; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
}