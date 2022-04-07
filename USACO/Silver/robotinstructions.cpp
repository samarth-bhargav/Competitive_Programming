#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

int n;
vector<pair<ll,ll>> coords;
pair<ll,ll> sumcoord = {0,0};
pair<ll,ll> targetcoord;
int iter = 0;

pair<bool, bool> valid(pair<ll, ll> sumcoords){
    pair<ll,ll> choose_n = sumcoords;
    pair<ll,ll> choose_nminusk = {sumcoord.first - choose_n.first,
                                  sumcoord.second - choose_n.second};
    pair<bool, bool> ret = {false, false};
    if (choose_n == targetcoord){
        ret.first = true;
    }
    if (choose_nminusk == targetcoord){
        ret.second = true;
    }
    return ret;
}

vector<int> answer(41, 0);

void dfs(vector<int> elements, int new_element, int sz, pair<ll, ll> temp_sumcoords){
    iter++;
    if (iter % 1000 == 0){
        cerr << iter << "\n";
    }
    if (sz > n/2) {
        return;
    }
    elements.push_back(new_element);
    temp_sumcoords.first += coords[new_element].first;
    temp_sumcoords.second += coords[new_element].second;
    pair<bool, bool> ret = valid(temp_sumcoords);
    if (ret.first){
        answer[sz]++;
    }
    if (ret.second && n - sz != sz){
        answer[n-sz]++;
    }
    for (int i = elements[elements.size()-1] + 1; i < n; i++){
        dfs(elements, i, sz+1, temp_sumcoords);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    cin >> targetcoord.first >> targetcoord.second;
    for (int i = 0; i < n; i++){
        ll a, b;
        cin >> a >> b;
        coords.emplace_back(a,b);
        sumcoord.first += a;
        sumcoord.second += b;
    }
    //iterating through how many elements you can choose
    for (int i = 0; i < n; i++){
        vector<int> x;
        dfs(x, i, 1, {0,0});
    }
    for (int i = 1; i <= n; i++){
        cout << answer[i] << "\n";
    }
}

