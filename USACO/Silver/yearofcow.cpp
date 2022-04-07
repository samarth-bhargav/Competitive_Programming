#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,k;
    cin >> n >> k; k--;
    ll answer = 0;
    vector<ll>differences;
    vector<ll>waiting;
    waiting.push_back(0LL);
    for (int i = 0; i < n; i++){
        ll a;
        cin >> a;
        waiting.push_back((a+11)/12);
    }
    sort(waiting.begin(), waiting.end());
    waiting.erase(unique(waiting.begin(),waiting.end()),waiting.end());
    for (int i = 1; i < waiting.size(); i++){
        differences.push_back(waiting[i]-waiting[i-1]-1);
    }
    sort(differences.begin(),differences.end());
    for (int i = 0; i < differences.size()-k; i++){
        answer += 12*differences[i];
    }
    answer += 12*(waiting.size()-1);
    cout << answer << "\n";
}



