#include <bits/stdc++.h>
using namespace std;

struct Point{
    long long x;
    long long y;
    int id;
    bool left;
    bool operator <(const Point &o) const{
        return (o.x == x ? o.y > y : o.x > x);
    }
};
struct segment{
    Point a;
    Point b;
    int id;
    bool operator <(const segment &o) const{
        return (o.a.y == a.y ? o.a.x > a.x : o.a.y > a.y);
    }
};
bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;

    return false;
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    return false; // Doesn't fall in any of the above cases
}
int main(){
    freopen("cowjump.in", "r", stdin);
    freopen("cowjump.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    Point ar[2*n+5];
    segment arr[n+5];
    for (int i = 1; i <= n; i++){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        Point r,s;
        r.x = a; r.y = b; r.left = true; r.id = i;
        s.x = c; s.y = d; s.left = false; s.id = i;
        if (!(r < s)){
            swap(r,s);
            r.left = !r.left;
            s.left = !s.left;
        }
        ar[2*i-2] = r;
        ar[2*i-1] = s;
        segment ss; ss.id = i; ss.a = r; ss.b = s;
        arr[i] = ss;
    }
    sort(ar,ar+2*n);
    set <segment> active;
    int potentiala, potentialb;
    for (int i = 0; i < 2*n; i++){
        if (!ar[i].left){
            auto it = active.find(arr[ar[i].id]);
            auto it1 = it, it2 = next(it);
//            cout << it1->id << " " << it2->id << "\n";
            if (it2 != active.end() && it1 != active.begin()) {
                it1 = prev(it);
                if (doIntersect(it->a, it->b, it2->a, it2->b)){
                    potentiala = it->id;
                    potentialb = it2->id;
                    break;
                }
                if (doIntersect(it->a, it->b, it1->a, it1->b)){
                    potentiala = it->id;
                    potentialb = it1->id;
                    break;
                }
            }
            else{
                continue;
            }
            active.erase(it);
        }
        else{
            active.insert(arr[ar[i].id]);
            auto it = active.find(arr[ar[i].id]);
            if (it == active.begin()){
                continue;
            }
            auto it1 = prev(it);
            auto it2 = next(it);
            if (it2 == active.end()){
                continue;
            }
            else{
                if (doIntersect(it->a, it->b, it2->a, it2->b)){
                    potentiala = it->id;
                    potentialb = it2->id;
                    break;
                }
                if (doIntersect(it->a, it->b, it1->a, it1->b)){
                    potentiala = it->id;
                    potentialb = it1->id;
                    break;
                }
            }
        }
    }
//    cout << potentiala << " " << potentialb << "\n";
//    cout << active.size() << "\n";
//    for (auto & i : active){
//        cout << i.id << " ";
//    }
//    cout << "\n";
    int ans = -1e9;
    for (int i = 0; i < n && ((arr[i].id != potentialb && arr[i].id != potentiala)); i++){
        if (doIntersect(arr[potentiala].a, arr[potentiala].b, arr[i].a, arr[i].b)){
            ans = potentiala;
            break;
        }
    }
    if (ans != -1e9){
        cout << ans << "\n";
        return 0;
    }
    for (int i = 0; i < n && ((arr[i].id != potentialb && arr[i].id != potentiala)); i++){
        if (doIntersect(arr[potentialb].a, arr[potentialb].b, arr[i].a, arr[i].b)){
            ans = potentialb;
            break;
        }
    }
    if (ans != -1e9){
        cout << ans << "\n";
        return 0;
    }
    cout << min(potentiala, potentialb) << "\n";
}


