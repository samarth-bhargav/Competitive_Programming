#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    multiset <pair<pair<int,int>,bool>> events;
    pair<int,int> ar[n+1];
    for (int i = 1; i <= n; i++){
        int a,b;
        cin >> a >> b;
        events.insert({{a,i},0});
        events.insert({{b,i},1});
        ar[i] = {a,b};
    }
    multiset<int>active;
    int times[n+1];
    int timein[n+1];
    int tottime = 0;
    int lasttottime = 0;
    memset(times,0,sizeof(times));
    for (auto & i : events){
        if (!i.second){
            active.insert(i.first.second);
            if (active.size() == 2){
                int a = *active.begin();
                int b = *next(active.begin());
                if (a != i.first.second){
                    //a is the init element
                    times[a] += i.first.first - timein[a];
                }
                else{
                    times[b] += i.first.first - timein[b];
                }
            }
            else if (active.size() == 1){
                lasttottime = i.first.first;
                timein[i.first.second] = i.first.first;
            }
        }
        else{
            active.erase(i.first.second);
            if (active.empty()){
                tottime += i.first.first-lasttottime;
                times[i.first.second] += i.first.first - timein[i.first.second];
            }
            else if (active.size() == 1){
                timein[*active.begin()] = i.first.first;
            }
        }
    }
    int lo = 1e9;
    for (int i = 1; i <= n; i++){
        lo = min(lo,times[i]);
    }
    cout << tottime-lo << "\n";
}
