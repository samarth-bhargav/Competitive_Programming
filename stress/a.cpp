#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const ll INF = 1e9;

int32_t main(){
    int t;
    cin >> t;
    while (t--){
        int n; ll x, y;
        cin >> n >> x >> y;
        deque<ll> opp(n);
        for (int i = 0; i < n; i++){
            cin >> opp[i];
        }
        sort(opp.begin(), opp.end());
        int tot_gain = 0, tot_games = 0;
        deque<int> aux;
        for (int i = 0; i < n; i++){
            if (x == y){
                break;
            }
            tot_games++;
            if (x >= opp[i]){
                x++; tot_gain++;
            }
            else{
                aux.push_back(opp[i] - i);
                x--; tot_gain--;
            }
        }
        if (x == y){
            cout << tot_games << "\n";
            continue;
        }
        if (tot_gain <= 0){
            cout << -1 << "\n";
            continue;
        }
        sort(aux.begin(), aux.end());
        while (x < y){
            int curr_cyc;
            if (aux.empty()){
                break;
            }
            else{
                curr_cyc = (aux[0] - x + tot_gain - 1) / tot_gain;
                aux.pop_front();
            }
            int tot_end_gain = 2;
            while (!aux.empty() && (aux[0] - x + tot_gain - 1) / tot_gain == curr_cyc){
                tot_end_gain += 2;
                aux.pop_front();
            }
            //if it ends early
            if (x + tot_gain * (curr_cyc-1) + (tot_gain + n) / 2 >= y){
                break;
            }
            //so you go through n * curr_cyc games and then you start winning more
            tot_games += (n * curr_cyc);
            x += (tot_gain * curr_cyc);
            tot_gain += tot_end_gain;
        }
        //simulate last games
        int curr_run = (tot_gain + n) / 2;
        int rounds = (y - curr_run - x + tot_gain - 1) / tot_gain;
        tot_games += n * rounds;
        x += tot_gain * rounds;
        for (int i = 0; i < n; i++){
            if (x == y){
                break;
            }
            tot_games++;
            if (x >= opp[i]){
                x++; tot_gain++;
            }
            else{
                x--; tot_gain--;
            }
        }
        cout << tot_games << "\n";
    }
}
//you want to play opponents in order of increasing difficulty
//when does the number of opponents you beat change?
