#include <bits/stdc++.h>
using namespace std;

#define ll int64_t

int n, m, b;
const ll INF = 7e18;

struct peer{
    ll cost, problems, monitors;
    peer(ll cost, ll monitors, ll problems){
        this->cost = cost;
        this->problems = problems;
        this->monitors = monitors;
    }
    peer(){}
    bool operator <(const peer &o){
        return monitors < o.monitors;
    }
};

ll dp[1 << 20];

int main(){
    cin >> n >> m >> b;
    peer friends[n];
    for (int i = 0; i < n; i++){
        int xi, ki, mi;
        cin >> xi >> ki >> mi;
        int problems = 0;
        for (int j = 0; j < mi; j++){
            int a; cin >> a; a--;
            problems = problems | (1 << a);
        }
        friends[i] = peer(xi, ki, problems);
    }
    ll answer = INF;
    sort(friends, friends+n);
    for (int i = 0; i < (1 << 20); i++){
        dp[i] = INF;
    }
    dp[0] = 0;
    for (int i = 0; i < n; i++){
        //iterating through last possible element
        for (int mask = 0; mask < (1<<20); mask++){
            if (dp[mask] != INF) {
                ll potential_cost = dp[mask] + friends[i].cost;
                if ((dp[mask | friends[i].problems]) > potential_cost) {
                    dp[mask | friends[i].problems] = potential_cost;
                }
            }
        }
        if (dp[(1 << m) - 1] != INF){
            answer = min(answer, dp[(1 << m) - 1] + friends[i].monitors * b);
        }
    }
    if (answer == INF){
        cout << -1 << "\n";
        return 0;
    }
    cout << answer << "\n";
}