#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> heights;
double slope(int i, int j){
    return double(heights[i] - heights[j]) / double(i - j);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    heights.resize(n);
    for (int i = 0; i < n; i++){
        cin >> heights[i];
    }
    int q;
    cin >> q;
    vector<set<pair<double, int>>> sequence(n);
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (sequence[i].empty()){
                sequence[i].insert({slope(i, j), j});
            }
            else if (prev(sequence[i].end())->first <= slope(i, j)){
                sequence[i].insert({slope(i, j), j});
            }
        }
    }
    for (int query = 0; query < q; query++){
        int x, y;
        cin >> x >> y; x--;
        heights[x] += y;
        for (int i = 0; i < x; i++){
            auto it = sequence[i].lower_bound({slope(i, x), 0});
            if (it == sequence[i].end()){
                //everything is less
                set<pair<double, int>> new_set;
                for (auto it1 = sequence[i].begin(); it1 != sequence[i].end() && it1->second < x; it1++){
                    new_set.insert(*it1);
                }
                new_set.insert({slope(i, x), x});
                sequence[i] = new_set;
            }
            else{
                if (it->second < x && it->first > slope(i, x)){
                    continue;
                }
                else{
                    set<pair<double, int>> new_set;
                    for (auto it1 = sequence[i].begin(); it1 != sequence[i].end() && it1->second < x; it1++){
                        new_set.insert(*it1);
                    }
                    new_set.insert({slope(i, x), x});
                    for (auto it1 = it; it1 != sequence[i].end(); it1++){
                        new_set.insert(*it1);
                    }
                    sequence[i] = new_set;
                }
            }
        }
        //update actual mountain now
        sequence[x] = {};
        for (int i = x+1; i < n; i++){
            if (sequence[x].empty()){
                sequence[x].insert({slope(x, i), i});
            }
            else if (prev(sequence[x].end())->first <= slope(x, i)){
                sequence[x].insert({slope(x, i), i});
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++){
            ans += sequence[i].size();
        }
        cout << ans << "\n";
    }
}