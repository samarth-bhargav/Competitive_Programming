#include <bits/stdc++.h>
using namespace std;

int n, xh, yh, h;

struct point{
    double x, y;
    point(){}
    point(int x, int y){
        this->x = x;
        this->y = y;
    }
    bool operator <(const point &o) const{
        return (double(xh - x + 0.0) / double(yh - y + 0.0)) < (double(xh - o.x + 0.0) / double(yh - o.y + 0.0));
    }
};

double slope(point a, point b){
    return double(a.y - b.y + 0.0) / double(a.x - b.x + 0.0);
}

double distance(point a, point b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int main(){
    cout << setprecision(15);
    cin >> n >> h;
    vector<point> points(n);
    for (int i = 0; i < n; i++){
        cin >> points[i].x >> points[i].y;
    }
    xh = points[n-1].x;
    yh = points[n-1].y + h;
    set<point> slopes;
    for (int i = 0; i < n-1; i++){
        slopes.insert(points[i]);
    }
    //near end will be bigger slope -> what we want
    double ans = 0;
    for (int i = 0; i < n-1; i++){
        slopes.erase(points[i]);
        if (slopes.empty()){
            ans += distance(points[i], points[i+1]);
            continue;
        }
        //points[i] to points[i+1]
        double sl1 = slope(points[i], points[i+1]);
        //equation is (y - points[i].y = sl1(x - points[i].x))
        double sl2 = slope(point(xh, yh), *prev(slopes.end()));
        //equation is (y - yh = sl2(x - xh))
        //somehow have to find intersection :DD
        double intersection_x = double(-sl1 * points[i].x + points[i].y + sl2 * xh - yh) / double(sl2 - sl1);
        double intersection_y = sl2 * (intersection_x - xh) + yh;
        point inter = point(intersection_x, intersection_y);
        if (points[i].y < points[i+1].y){
            //line goes up
7            if (points[i].y < inter.y){
                if (inter.y < points[i+1].y){
                    ans += distance(inter, points[i+1]);
                }
            }
            else{
                ans += distance(points[i], points[i+1]);
            }
        }
        else{
            //line goes down
                if (inter.y < points[i].y){
                if (inter.y > points[i+1].y){
                    ans += distance(inter, points[i]);
                }
                else{
                    ans += distance(points[i], points[i+1]);
                }
            }
        }
    }
    cout << ans << "\n";
}