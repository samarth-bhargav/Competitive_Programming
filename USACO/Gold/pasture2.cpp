#include <bits/stdc++.h>
using namespace std;

const int mxN = 200;

int main(){
    int n; cin >> n;
    vector<pair<int,int>> points, points_y;
    for (int i = 0; i < n; i++){
        int a,b;
        cin >> a >> b;
        points.emplace_back(a,b);
        points_y.emplace_back(b,a);
    }
    sort(points.begin(), points.end());
    sort(points_y.begin(), points_y.end());
    int ans = n+1; // each point in individual cell, empty cell
    int rep = 0;
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (points[j].first - points[i].first <= abs(points[j].second - points[i].second)){
                // this means that the lines are oriented horizontally
                int side_len = abs(points[j].second - points[i].second);
                int miny = min(points[i].second, points[j].second);
                int maxy = max(points[i].second, points[j].second);
                int lb = -1e9;
                int rb = -1e9 + side_len;
                while (lb <= points[i].first){
                    auto it1 = lower_bound(points.begin(), points.end(), make_pair(lb, -1));
                    auto it2 = lower_bound(points.begin(), points.end(), make_pair(rb, (int)(1e9+1)));
                    if (it2 == points.end() || it1->first + 1 - lb < it2->first - rb){
                        //this means the lower bound is closer
                        lb = it1->first;
                        rb = it1->first + side_len;
                        if (!(miny <= it1->second && maxy >= it1->second)){
                            lb++;
                            rb++;
                            continue;
                        }
                        if (rb < points[j].first){
                            lb++;
                            rb++;
                            continue;
                        }
                        if (lb + 1 > points[i].first){
                            break;
                        }
                        lb++;
                        rb++;
                        ans++;
                    }
                    else if (it1->first + 1 - lb == it2->first - rb){
                        //this means both the distances are equal, so it hits both at same time
                        bool valid_lb = true, valid_rb = true;
                        lb = it1->first;
                        rb = it2->first;
                        if (!(miny <= it1->second && maxy >= it1->second)){
                            valid_lb = false;
                        }
                        if (!(miny <= it2->second && maxy >= it2->second)){
                            valid_rb = false;
                        }
                        if (rb <= points[j].first){
                            if (rb == points[j].first){
                                ans++;
                                auto it = lower_bound(points.begin(), points.end(), make_pair(rb - side_len, -1));
                                if (it -> first == rb - side_len){
                                    if (miny <= it->second && maxy >= it->second){
                                        rep++;
                                    }
                                }
                            }
                            lb++;
                            continue;
                        }
                        if (lb + 1 > points[i].first){
                            lb++;
                            break;
                        }
                        if (!valid_lb && !valid_rb){

                        }
                        else {
                            auto it = lower_bound(points.begin(), points.end(), make_pair(rb - side_len, -1));
                            if (it != points.end() && it -> first == rb - side_len){
                                if (miny <= it->second && maxy >= it->second){
                                    rep++;
                                }
                            }
                            ans++;
                        }
                        lb++;
                    }
                    else{
                        lb = it2->first - side_len;
                        rb = it2->first;
                        if (!(miny <= it2->second && maxy >= it2->second)){
                            continue;
                        }
                        if (rb < points[j].first){
                            continue;
                        }
                        if (lb > points[i].first){
                            break;
                        }
                        if (it1->first == lb){
                            if (miny <= it1->second && maxy >= it1->second){
                                rep++;
                            }
                        }
                        ans++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (abs(points_y[i].first - points_y[j].first) <= abs(points_y[i].second - points_y[j].second)){
                //lines going vertically
                int side_len = abs(points_y[i].second - points_y[j].second);
                int minx = min(points_y[i].second, points_y[j].second);
                int maxx = max(points_y[i].second, points_y[j].second);
                int lb = -1e9;
                int ub = -1e9 + side_len;
                while (lb <= points_y[i].first) {
                    auto it1 = lower_bound(points_y.begin(), points_y.end(), make_pair(lb, -1));
                    auto it2 = lower_bound(points_y.begin(), points_y.end(), make_pair(ub, (int)(1e9 + 1)));
                    if (it2 == points_y.end() || it1->first + 1 - lb < it2->first - ub) {
                        //this means the lower bound is closer
                        lb = it1->first;
                        ub = it1->first + side_len;
                        if (!(minx <= it1->second && maxx >= it1->second)) {
                            lb++;
                            ub++;
                            continue;
                        }
                        if (ub < points_y[j].first) {
                            lb++;
                            ub++;
                            continue;
                        }
                        if (lb + 1 > points_y[i].first) {
                            break;
                        }
                        ans++;
                        lb++;
                        ub++;
                    }
                    else if (it1->first + 1 - lb == it2->first - ub){
                        bool valid_lb = true, valid_ub = true;
                        lb = it1->first;
                        ub = it2->first;
                        if (!(minx <= it1->second && maxx >= it1->second)){
                            valid_lb = false;
                        }
                        if (!(minx <= it2->second && maxx >= it2->second)){
                            valid_ub = false;
                        }
                        if (ub <= points_y[j].first){
                            if (ub == points_y[j].first){
                                ans++;
                                auto it = lower_bound(points_y.begin(), points_y.end(), make_pair(ub - side_len, -1));
                                if (it -> first == ub - side_len){
                                    if (minx <= it->second && maxx >= it->second){
                                        rep++;
                                    }
                                }
                            }
                            lb++;
                            continue;
                        }
                        if (lb + 1 > points_y[i].first){
                            lb++;
                            break;
                        }
                        if (!valid_lb && !valid_ub){

                        }
                        else{
                            auto it = lower_bound(points_y.begin(), points_y.end(), make_pair(ub - side_len, -1));
                            if (it != points_y.end() && it -> first == ub - side_len){
                                if (minx <= it->second && maxx >= it->second){
                                    rep++;
                                }
                            }
                            ans++;
                        }
                        lb++;
                    }
                    else{
                        lb = it2->first - side_len;
                        ub = it2->first;
                        if (!(minx <= it2->second && maxx >= it2->second)) {
                            continue;
                        }
                        if (ub < points_y[j].first) {
                            continue;
                        }
                        if (lb > points_y[i].first) {
                            break;
                        }
                        if (it1->first == lb){
                            if (minx <= it1->second && maxx >= it1->second){
                                rep++;
                            }
                        }
                        ans++;
                    }
                }
            }
        }
    }
    cerr << ans << " " << rep << "\n";
    cout << ans - rep/2 << "\n";
}
