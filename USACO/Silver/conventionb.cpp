/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

struct cow{
    int id;
    int start;
    int finish;
    bool operator<(const cow& x) const{
        return id > x.id;
    }
};
bool cmp(cow a, cow b){
    return a.start < b.start;
}

int main() {
    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);
    int t;
    cin >> t;
    cow ar[t];
    for (int i = 0; i < t; i++){
        cin >> ar[i].start >> ar[i].finish;
        ar[i].id = i;
    }
    sort(ar, ar+t, cmp);
    int maxwaiting = -1e9;
    int currtime = ar[0].start, cnt = 1;
    cow pos;// current cow on the field
    pos.id = ar[0].id; pos.start = ar[0].start; pos.finish = ar[0].finish;
    priority_queue<cow>pq;
    int starttime[t], endtime[t]; // time when cow starts waiting, total cow waiting time
    memset(starttime, 0, sizeof(starttime));
    memset(endtime, 0, sizeof(endtime));
    endtime[pos.id] = pos.start;
    starttime[pos.id] = pos.start;
//    cout << "hi" << "\n";
    while (true){
        bool alg = false;
        if (pos.id == t-1){
            endtime[pos.id] = pos.finish;
            break;
        }
        while (true){
            if (cnt >= t){
                endtime[pos.id] = pos.finish;
                alg = true;
                break;
            }
            if (ar[cnt].start <= pos.finish + endtime[pos.id]){
                pq.push(ar[cnt]);
                starttime[ar[cnt].id] = ar[cnt].start;
                cnt++;
            }
            else{
                break;
            }
        }
        if (alg){
            break;
        }
        if (pq.empty()){
            pos = ar[cnt];
            starttime[pos.id] = pos.start;
            endtime[pos.id] = pos.start;
            cnt++;
            continue;
        }
        endtime[pq.top().id] = pos.finish + endtime[pos.id];
        pos = pq.top();
        pq.pop();
    }
//    cout << "hi" << "\n";
    for (int i = 0; i < t; i++){
        maxwaiting = max(maxwaiting, endtime[i] - starttime[i]);
    }
    cout << maxwaiting << "\n";
}

