#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 1<<30;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int>a(n);
    vector<pair<int,int>>neg,pos,zero;
    set<int>erased;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        if (a[i] < 0){
            neg.push_back({a[i],i});
        }
        else if (a[i] > 0){
            pos.push_back({a[i],i});
        }
        else if (a[i] == 0){
            zero.push_back({0,i});
        }
    }
    sort(pos.begin(),pos.end());
    sort(neg.begin(),neg.end());
    bool two = 0;
    int operations = 0;
    //combine all zeroes
    if (zero.size() == 0 || zero.size() == 1){
        0;
    }
    else{
        for (int i = 0; i < zero.size()-1; i++){
            cout << 1 << " " << zero[i].second+1 << " " << zero[i+1].second+1 << "\n";
            operations++;
            erased.insert(zero[i].second+1);
        }
    }
    if (neg.size()%2 == 1 && operations != n-1){
        if (!zero.empty()){
            cout << 1 << " " << zero[zero.size()-1].second+1 << " " << neg[0].second+1 << "\n";
            erased.insert(zero[zero.size()-1].second+1);
            operations++;
        }
        if (operations != n-1){
            cout << 2 << " " << neg[0].second+1 << "\n";
            erased.insert(neg[0].second+1);
            operations++;
        }
    }
    else if (neg.size()%2 == 0 && operations != n-1){
        if (!zero.empty()){
            cout << 2 << " " << zero[zero.size()-1].second+1 << "\n";
            erased.insert(zero[zero.size()-1].second+1);
            operations++;
        }
    }
    for (int i = 1; i < n; i++){
        if (erased.find(i) != erased.end()){
            continue;
        }
        if (erased.find(i+1) != erased.end()){
            int k = i+1;
            while (erased.find(k) != erased.end() && k <= n){
                k++;
            }
            if (k != n+1){
                cout << 1 << " " << i << " " << k << "\n";
                operations++;
                i = k-2;
            }
        }
        else{
            cout << 1 << " " << i << " " << i+1 << "\n";
            operations++;
            erased.insert(i);
        }
    }
}

