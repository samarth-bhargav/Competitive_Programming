#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Pt {
    int x, y;
};

int orient(const Pt &a, const Pt &b, const Pt &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool isect(const Pt &p1, const Pt &p2, const Pt &p3, const Pt &p4) {
    int o1 = orient(p1, p2, p3);
    int o2 = orient(p1, p2, p4);
    int o3 = orient(p3, p4, p1);
    int o4 = orient(p3, p4, p2);

    if (o1 == 0 && o2 == 0 && o3 == 0 && o4 == 0) {
        return false;
    }
    bool diff1 = (o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0);
    bool diff2 = (o3 > 0 && o4 < 0) || (o3 < 0 && o4 > 0);
    return (diff1 && diff2);
}

struct Line {
    int s, x, y;
};

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, T, X, Y;
    cin >> n >> T >> X >> Y;

    vector<Line> lines(n);
    for (int i = 0; i < n; i++){
        cin >> lines[i].s >> lines[i].x >> lines[i].y;
    }

    long double directDist = sqrtl((long double)X * (long double)X
                                   + (long double)Y * (long double)Y);

    vector<long double> dt(T, sqrtl((long double)X * (long double)X
                                    + (long double)Y * (long double)Y));

    auto dijkstra = [&](const vector<Line> &active) {
        vector<Pt> pts;

        pts.push_back({X, 0});
        pts.push_back({0, Y});

        for (auto &ln : active) {
            pts.push_back({ln.x, 0});
            pts.push_back({0, ln.y});
        }

        int V = (int)pts.size();

        vector<vector<pair<int,long long>>> adj(V);

        auto blocked = [&](int i, int j) {
            const Pt &p1 = pts[i], &p2 = pts[j];
            for (auto &ln : active) {
                Pt c1{ln.x, 0}, c2{0, ln.y};

                auto same = [&](const Pt &a, const Pt &b) {
                    return (a.x == b.x && a.y == b.y);
                };
                if (same(p1, c1) || same(p1, c2) || same(p2, c1) || same(p2, c2)) {
                    continue;
                }
                if (isect(p1, p2, c1, c2)) {
                    return true;
                }
            }
            return false;
        };

        for (int i = 0; i < V; i++){
            for (int j = i+1; j < V; j++){
                if (!blocked(i, j)) {
                    long long dx = (long long)pts[i].x - (long long)pts[j].x;
                    long long dy = (long long)pts[i].y - (long long)pts[j].y;
                    long long sq = dx*dx + dy*dy;
                    adj[i].push_back({j, sq});
                    adj[j].push_back({i, sq});
                }

        }

        const long double INF = 1e18L;
        vector<long double> dist(V, INF);
        dist[0] = 0.0L;
        vector<bool> used(V,false);

        for (int step = 0; step < V; step++){
            int u = -1;
            long double best = INF;
            for (int v = 0; v < V; v++){
                if(!used[v] && dist[v] < best){
                    best = dist[v];
                    u = v;
                }
            }
            if (u < 0) break;
            used[u] = true;

            for (auto &ed : adj[u]) {
                int w = ed.first;
                long long sq = ed.second;
                if (!used[w]) {
                    long double cost = dist[u] + sqrtl((long double)sq);
                    if (cost < dist[w]) {
                        dist[w] = cost;
                    }
                }
            }
        }

        return dist[1];
    };

    for (int t = 0; t < T; t++){
        vector<Line> nowActive;
        for (auto &ln : lines){
            if (ln.s <= t) {
                nowActive.push_back(ln);
            }
        }
        long double ans = dijkstra(nowActive);
        dt[t] = ans;
    }

    for (int t = 0; t < T; t++){
        cout << (long long)floorl(dt[t]) << "\n";
    }

    return 0;
}
