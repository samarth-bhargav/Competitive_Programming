/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>
using namespace std;

struct friends{
    int friendship;
    long long money;
};
bool cmp (friends a, friends b){
    return a.money < b.money;
}



int main() {
    //setIO();
    int t, d;
    cin >> t >> d;
    friends ar[t];
    for (int i = 0; i < t; i++){
        cin >> ar[i].money >> ar[i].friendship;
    }
    sort(ar, ar+t, cmp);
    long long prefixsums[t+1];
    prefixsums[0] = 0;
    for (int i = 1; i <= t; i++){
        prefixsums[i] = prefixsums[i-1] + ar[i-1].friendship;
    }
    vector <int> dollars;
    for (int i = 0; i < t; i++){
        dollars.push_back(ar[i].money);
    }
    //iterating through all
    long long maxN = -1e9;
    for (int i = 0; i < t; i++){
        auto it = lower_bound(dollars.begin(), dollars.end(), ar[i].money - d + 1);
        maxN = max(maxN, prefixsums[i+1] - prefixsums[it-dollars.begin()]);
    }

    cout << maxN << "\n";
}

