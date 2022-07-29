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
                int lb, rb;
                int miny = min(points[j].second, points[i].second);
                int maxy = max(points[j].second, points[i].second);
                int side_len = abs(points[j].second - points[i].second);
                for (lb = 0; lb <= i; lb++){
                    //left bound
                    if (points[j].first - side_len > points[lb].first){
                        continue;
                    }
                    if (!(miny <= points[lb].second && maxy >= points[lb].second)){
                        //point is outside range
                        continue;
                    }
                    rb = points[lb].first + side_len;
                    //optimization possible for following
                    auto it = lower_bound(points.begin(), points.end(), make_pair(rb, -1));
                    if (it != points.end() && it->first == rb){
                        if (miny <= it->second && maxy >= it->second){
                            rep++;
                        }
                    }
                    ans++;
//                    cout << 1 << " " << ans << "\n";
                }
                // also iterate from right to left
                for (rb = n-1; rb >= j; rb--){
                    if (points[i].first + side_len < points[rb].first){
                        continue;
                    }
                    if (!(miny <= points[rb].second && maxy >= points[rb].second)){
                        continue;
                    }
                    lb = points[rb].first - side_len;
                    //optimization possible for following
                    auto it = lower_bound(points.begin(), points.end(), make_pair(lb, -1));
                    while (true){
                        if (it == points.end()){
                            cerr << "hi\n";
                            break;
                        }
                        if (miny <= it->second && maxy >= it->second){
                            break;
                        }
                        if (it - points.begin() > i){
                            break;
                        }
                        it++;
                    }
                    auto it1 = lower_bound(points.begin(), points.end(), make_pair(it->first + side_len, -1));
                    if (it1 == points.end() || it1->first > it->first + side_len){
                        it1--;
                    }
                    bool flag = false;
                    for (int k = it1 - points.begin(); k > rb; k--){
                        if (miny <= points[k].second && maxy >= points[k].second){
                            flag = true;
                            break;
                        }
                    }
                    if (!flag){
                        continue;
                    }
                    if (it != points.end() && it->first == lb){
                        if (miny <= it->second && maxy >= it->second){
                            rep++;
                        }
                    }
                    ans++;
//                    cout << 2 << " " << ans << "\n";
                }
            }
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            pair<int,int> p1 = {points_y[i].second, points_y[i].first};
            pair<int,int> p2 = {points_y[j].second, points_y[j].first};
            if (abs(p1.first - p2.first) >= abs(p1.second - p2.second)){
                //this means that lines are oriented vertically
                int ub, lb;
                int minx = min(p1.first, p2.first);
                int maxx = max(p1.first, p2.first);
                int side_len = maxx - minx;
                for (lb = 0; lb <= i; lb++){
                    if (p2.second - side_len > points_y[lb].first){
                        continue;
                    }
                    if (!(minx <= points_y[lb].second && maxx >= points_y[lb].second)){
                        continue;
                    }
                    ub = points_y[lb].first + side_len;
                    auto it = lower_bound(points_y.begin(), points_y.end(), make_pair(ub, -1));
                    if (it != points_y.end() && it->first == ub){
                        if (minx <= it->second && maxx >= it->second){
                            rep++;
                        }
                    }
                    ans++;
//                    cout << 3 << " " << ans << "\n";
                }
                for (ub = n-1; ub >= j; ub--){
                    if (p1.second + side_len < points_y[ub].first){
                        continue;
                    }
                    if (!(minx <= points_y[ub].second && maxx >= points_y[ub].second)){
                        continue;
                    }
                    lb = points_y[ub].first - side_len;
                    auto it = lower_bound(points_y.begin(), points_y.end(), make_pair(lb, -1));
                    while (true){
                        if (it == points_y.end()){
                            cerr << "hi\n";
                            break;
                        }
                        if (minx <= it->second && maxx >= it->second){
                            break;
                        }
                        if (it - points_y.begin() > i){
                            break;
                        }
                        else{
                            it++;
                        }
                    }
                    auto it1 = lower_bound(points_y.begin(), points_y.end(), make_pair(it->first+side_len, -1));
                    if (it1 == points_y.end() || it1->first > it->first + side_len){
                        it1--;
                    }
                    bool flag = false;
                    for (int k = it1 - points_y.begin(); k > ub; k--){
                        if (minx <= points_y[k].second && maxx >= points_y[k].second){
                            flag = true;
                            break;
                        }
                    }
                    if (!flag){
                        continue;
                    }
                    if (it != points_y.end() && it->first == lb){
                        if (minx <= it->second && maxx >= it->second){
                            rep++;
                        }
                    }
                    ans++;
//                    cout << 4 << " " << ans << "\n";
                }
            }
        }
    }
//    cerr << "asdfijas" << ans << " " << rep << "\n";
    cout << ans - rep/2 << "\n";
}
