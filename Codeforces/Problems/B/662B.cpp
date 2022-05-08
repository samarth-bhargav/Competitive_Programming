/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}


int main() {
    //setIO();
    int n;
    cin >> n;
    int ar[100001] = {0};
    priority_queue <pair <int,int>> pq;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        ar[x] ++;
    }
    for (int i = 0; i < n; i++){
        pq.push(make_pair(ar[i], i));
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        char c;
        cin >> c;
        int k;
        if (c == '-'){
            cin >> k;
            ar[k] --;
            pq.push(make_pair(ar[k], k));
        }
        else{
            cin >> k;
            ar[k] ++;
            pq.push(make_pair(ar[k], k));
        }
        if (pq.top().first >= 4){
            int x = pq.top().second;
            pq.push(make_pair(pq.top().first - 4, x));
            pq.pop();
            if ((c == '-' && pq.top().first == ar[k]+1) || c == '+' && pq.top().first == ar[k] - 1){
                pq.pop();
            }
                if (pq.top().second == k){
                    if ((c == '-' && pq.top().first == ar[k]+1) || c == '+' && pq.top().first == ar[k] - 1){
                        pq.pop();
                    }
                }
                if (pq.top().first >= 2){
                    int h = pq.top().second;
                    pq.push(make_pair(pq.top().first - 2, h));
                    pq.pop();
                    if ((c == '-' && pq.top().first == ar[k]+1) || c == '+' && pq.top().first == ar[k] - 1){
                        pq.pop();
                    }
                    if (pq.top().first >= 2){
                        cout << "YES\n";
                    }
                    else{
                        cout << "NO\n";
                    }
                }
                else{
                    cout << "NO\n";
                }
        }
        else{
            cout << "NO\n";
        }
    }
}

