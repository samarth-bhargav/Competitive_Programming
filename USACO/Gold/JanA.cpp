#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int ll

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; cin >> n >> q;
    set<int> x_set, y_set;
    vector<int> ys, xs;
    for (int i = 0; i < n; i++){
        char c; int x; cin >> c >> x;
        if (c == 'V') {
            x_set.insert(x);
        }
        else{
            y_set.insert(x);
        }
    }
    if (!x_set.empty()){
        int lst = *x_set.begin();
        xs.push_back(lst);
        for (auto it = next(x_set.begin()); it != x_set.end(); it++){
            if ((*it - lst) % 2 == 1){
                lst = *it;
                xs.push_back(lst);
            }
        }
    }

    if (!y_set.empty()){
        int lst = *y_set.begin();
        ys.push_back(lst);
        for (auto it = next(y_set.begin()); it != y_set.end(); it++){
            if ((*it - lst) % 2 == 1){
                lst = *it;
                ys.push_back(lst);
            }
        }
    }

    vector<int> all_x(x_set.begin(), x_set.end());
    vector<int> all_y(y_set.begin(), y_set.end());

    vector<pair<array<int, 2>, int>> cows(q);
    for (int i = 0; i < q; i++){
        int x, y, d; cin >> x >> y >> d;
        cows[i] = {{x, y}, d};
    }
    for (int i = 0; i < q; i++){
        int x = cows[i].first[0], y = cows[i].first[1];
        int d = cows[i].second;
        bool init_vert = false;
        if (x_set.count(x)){
            init_vert = true;
        }
        else{
            assert(y_set.count(y));
        }

        int init_x = x, init_y = y;
        bool solved = false;
        while (true){
            if (binary_search(xs.begin(), xs.end(), x) && binary_search(ys.begin(), ys.end(), y)){
                break;
            }
            if (init_vert){
                //transfer to next y
                int nxt_y = upper_bound(all_y.begin(), all_y.end(), y) - all_y.begin();
                if (nxt_y == all_y.size() || all_y[nxt_y] - y >= d){
                    cout << x << " " << y + d << "\n";
                    solved = true;
                    break;
                }
                d -= (all_y[nxt_y] - y);
                y = all_y[nxt_y];
                init_vert = (((x + y) - (init_x + init_y)) % 2 == 0);
            }
            else{
                //transfer to next x
                int nxt_x = upper_bound(all_x.begin(), all_x.end(), x) - all_x.begin();
                if (nxt_x == all_x.size() || all_x[nxt_x] - x >= d){
                    cout << x + d << " " << y << "\n";
                    solved = true; break;
                }
                d -= (all_x[nxt_x] - x);
                x = all_x[nxt_x];
                init_vert = (((x + y) - (init_x + init_y)) % 2 == 0);
            }
        }

        if (solved){
            continue;
        }

        int nxt_y = lower_bound(ys.begin(), ys.end(), y) - ys.begin();
        int nxt_x = lower_bound(xs.begin(), xs.end(), x) - xs.begin();

        if (nxt_x == xs.size() || nxt_y == ys.size()){
            //always going to be traveling in initial direction
            if (init_vert){
                cout << x << " " << y + d << "\n";
            }
            else{
                cout << x + d << " " << y << "\n";
            }
            continue;
        }

        int lo = 0, hi = (xs.size() - 1 - nxt_x) + (ys.size() - 1 - nxt_y) + 5;
        while (lo < hi){
            int mid = (lo + hi + 1) / 2;
            int x_trav = (init_vert ? mid / 2 : (mid + 1) / 2);
            int y_trav = mid - x_trav;

            if (nxt_x + x_trav >= xs.size() || nxt_y + y_trav >= ys.size()){
                hi = mid-1; continue;
            }

            if ((xs[nxt_x + x_trav] - x) + (ys[nxt_y + y_trav] - y) > d){
                hi = mid-1;
            } else{
                lo = mid;
            }
        }
        int x_trav = (init_vert ? lo / 2 : (lo + 1) / 2);
        int y_trav = lo - x_trav;
        array<int, 2> cc = {xs[nxt_x + x_trav], ys[nxt_y + y_trav]};
        if (lo % 2 == 1){
            //direction swap
            init_vert ^= true;
        }
        int residue = d - ((cc[0] - x) + (cc[1] - y));
        if (init_vert){
            cout << cc[0] << " " << cc[1] + residue << "\n";
        }
        else{
            cout << cc[0] + residue << " " << cc[1] << "\n";
        }
    }
}
