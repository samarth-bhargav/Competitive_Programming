#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000;
int segtree[4 * MAX_N];

void segtreeupd(int idx, int l, int r, int i, int v) {
    if(l == r) segtree[idx] = v;
    else {
        int m = (l+r)/2;
        if(i <= m) segtreeupd(2*idx, l, m, i, v);
        else segtreeupd(2*idx+1, m+1, r, i, v);
        segtree[idx] = segtree[2*idx] ^ segtree[2*idx+1];
    }
}
void segtreeupd(int i, int v) {
    segtreeupd(1, 0, MAX_N-1, i, v);
}

int segtreeqry(int idx, int l, int r, int lhs, int rhs) {
    if(l >= lhs && r <= rhs) return segtree[idx];
    int ret = 0;
    int m = (l+r)/2;
    if(m >= lhs) ret ^= segtreeqry(2*idx, l, m, lhs, rhs);
    if(m+1 <= rhs) ret ^= segtreeqry(2*idx+1, m+1, r, lhs, rhs);
    return ret;
}
int segtreeqry(int l, int r) {
    return segtreeqry(1, 0, MAX_N-1, l, r);
}

const int MAX_D = 17;
int lca[MAX_N][MAX_D];
int depth[MAX_N];

int getLCA(int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);
    for(int d = MAX_D-1; d >= 0; d--) {
        if(depth[a] - (1<<d) >= depth[b]) {
            a = lca[a][d];
        }
    }
    for(int d = MAX_D-1; d >= 0; d--) {
        if(lca[a][d] != lca[b][d]) {
            a = lca[a][d];
            b = lca[b][d];
        }
    }
    if(a != b) {
        a = lca[a][0];
        b = lca[b][0];
    }
    return a;
}

void initLCA() {
    for(int d = 1; d < MAX_D; d++) {
        for(int i = 0; i < MAX_N; i++) {
            lca[i][d] = lca[lca[i][d-1]][d-1];
        }
    }
}

vector<int> edges[MAX_N];
int treesz[MAX_N];
int vertextosegtree[MAX_N];
int topchain[MAX_N];
int vals[MAX_N];

void dfsForHLD(int curr, int topPtr, int par, int& internalsegtreeidx) {
    vertextosegtree[curr] = internalsegtreeidx++;
    segtreeupd(vertextosegtree[curr], vals[curr]);
    topchain[curr] = topPtr;
    int largestchild = -1;
    int largestsz = -1;
    for(int out: edges[curr]) {
        if(out == par) continue;
        if(treesz[out] > largestsz) {
            largestsz = treesz[out];
            largestchild = out;
        }
    }
    if(largestchild < 0) return;
    dfsForHLD(largestchild, topPtr, curr, internalsegtreeidx);
    for(int out: edges[curr]) {
        if(out == par || out == largestchild) continue;
        dfsForHLD(out, out, curr, internalsegtreeidx);
    }
}

void dfsForSize(int curr, int par) {
    treesz[curr]++;
    for(int out: edges[curr]) {
        if(out == par) continue;
        depth[out] = depth[curr] + 1;
        lca[out][0] = curr;
        dfsForSize(out, curr);
        treesz[curr] += treesz[out];
    }
}

void initHLD() {
    dfsForSize(0, -1);
    initLCA();
    int internalsegtreeidx = 0;
    dfsForHLD(0, 0, -1, internalsegtreeidx);
}

int pathQuery(int child, int par) {
    int ret = 0;
    while(child != par) {
        if(topchain[child] == child) {
            // light edge
            ret ^= vals[child];
            child = lca[child][0];
        }
        else if(depth[topchain[child]] > depth[par]) {
            ret ^= segtreeqry(vertextosegtree[topchain[child]], vertextosegtree[child]);
            child = lca[topchain[child]][0];
        }
        else {
            ret ^= segtreeqry(vertextosegtree[par]+1, vertextosegtree[child]);
            break;
        }
    }
    return ret;
}

int query(int a, int b) {
    int r = getLCA(a, b);
    return pathQuery(a, r) ^ pathQuery(b, r) ^ vals[r];
}

int main() {
//    freopen("cowland.in", "r", stdin);
//    freopen("cowland.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> vals[i];
    }
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    initHLD();
    while(q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int i, v;
            cin >> i >> v;
            vals[--i] = v;
            segtreeupd(vertextosegtree[i], v);
        }
        else {
            int a, b;
            cin >> a >> b;
            cout << query(--a, --b) << "\n";
        }
    }
}
