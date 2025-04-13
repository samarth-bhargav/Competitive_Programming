#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    struct node{
        int a, c, idx;
        node (int a, int c, int idx){
            this->a = a;
            this->c = c;
            this->idx = idx;
        }
        node (){}
    };
    vector<node> nodes(n+1);
    for (int i = 1; i <= n; i++){
        int a, c; cin >> a >> c;
        nodes[i] = node(a, c, i);
    }
    int q; cin >> q;

    struct query{
        int val, idx;
        query (int val, int idx){
            this->val = val;
            this->idx = idx;
        }
        query(){}
    };

    vector<query> queries(q);

    for (int i = 0; i < q; i++){
        int m; cin >> m;
        queries[i] = query(m, i);
    }

    sort(queries.begin(), queries.end(), [&](query &a, query &b){
        return a.val < b.val;
    });

    const int INF = 1e18;

    vector<vector<int>> dp(n+1, vector<int> (3, INF));

    vector<vector<array<int, 3>>> combo(3);

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                vector<int> x = {i, j, k};
                sort(x.begin(), x.end());
                combo[x[1]].push_back({i, j, k});
            }
        }
    }

    for (int i = n; i >= 1; i--){
        // leaf node
        if (i * 2 > n){
            for (int k = 0; k < 3; k++){
                dp[i][k] = nodes[i].c;
            }
            if (nodes[i].a < queries[0].val){
                dp[i][0] = 0;
            }
            else if (nodes[i].a == queries[0].val){
                dp[i][1] = 0;
            }
            else{
                dp[i][2] = 0;
            }
        }
        else{
            array<int, 3> costs = {nodes[i].c, nodes[i].c, nodes[i].c};
            if (nodes[i].a < queries[0].val){
                costs[0] = 0;
            }
            else if (nodes[i].a == queries[0].val){
                costs[1] = 0;
            }
            else{
                costs[2] = 0;
            }
            for (int k = 0; k < 3; k++){
                for (array<int, 3> way : combo[k]){
                    dp[i][k] = min(dp[i][k], costs[way[0]] + dp[i*2][way[1]] + dp[i*2+1][way[2]]);
                }
            }
        }
    }

    vector<int> answers(q);
    answers[queries[0].idx] = dp[1][1];

    int ptr = 0;
    vector<node> sorted_nodes(nodes.begin()+1, nodes.end());
    sort(sorted_nodes.begin(), sorted_nodes.end(), [&](node &a, node &b){
        return a.a < b.a;
    });

    for (int qq = 1; qq < q; qq++){
        // get all between qq-1 and qq

        vector<vector<int>> updates(20);

        while (ptr < n && sorted_nodes[ptr].a >= queries[qq-1].val && sorted_nodes[ptr].a <= queries[qq].val){
            updates[32 - (int32_t)(__builtin_clz(sorted_nodes[ptr].idx))].push_back(sorted_nodes[ptr].idx);
            ptr++;
        }

        while (ptr > 0 && sorted_nodes[ptr-1].a == queries[qq].val){
            ptr--;
        }

        //process dp

        for (int layer = 19; layer >= 0; layer--){
            sort(updates[layer].begin(), updates[layer].end());
            updates[layer].erase(unique(updates[layer].begin(), updates[layer].end()), updates[layer].end());

            for (int i : updates[layer]){
                //leaf node
                if (i * 2 > n){
                    for (int k = 0; k < 3; k++){
                        dp[i][k] = nodes[i].c;
                    }
                    if (nodes[i].a < queries[qq].val){
                        dp[i][0] = 0;
                    }
                    else if (nodes[i].a == queries[qq].val){
                        dp[i][1] = 0;
                    }
                    else{
                        dp[i][2] = 0;
                    }
                    if (i != 1){
                        updates[layer-1].push_back(i / 2);
                    }
                    continue;
                }
                //non-leaf node
                array<int, 3> costs = {nodes[i].c, nodes[i].c, nodes[i].c};
                if (nodes[i].a < queries[qq].val){
                    costs[0] = 0;
                }
                else if (nodes[i].a == queries[qq].val){
                    costs[1] = 0;
                }
                else{
                    costs[2] = 0;
                }
                for (int k = 0; k < 3; k++){
                    dp[i][k] = INF;

                    for (array<int, 3> way : combo[k]){
                        dp[i][k] = min(dp[i][k], costs[way[0]] + dp[i*2][way[1]] + dp[i*2+1][way[2]]);
                    }
                }
                if (i != 1){
                    updates[layer-1].push_back(i / 2);
                }
            }
        }

        //get answer
        answers[queries[qq].idx] = dp[1][1];
    }

    for (int ans : answers){
        cout << ans << "\n";
    }

}