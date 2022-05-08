/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

string s; int ar[100005];
int nextsmallest[100005]; 
vector<int>fnd[26];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    fill(nextsmallest,nextsmallest+100005,1000000000);
    int n,q;
    cin >> n >> q;
    cin >> s;
    for (int i = 0; i < n; i++){
        ar[i] = s[i] - 'A';
    }
    stack<pair<int,int>>x; x.push({ar[0],0});
    for (int i = 1; i < n; i++){
        if (x.empty()){
            x.push({ar[i],i});
            continue;
        }
        while (!x.empty() && x.top().first > ar[i]){
            nextsmallest[x.top().second] = i;
            x.pop();
        }
        x.push({ar[i],i});
    }
    for (int i = 0; i < n; i++){
        fnd[ar[i]].push_back(i);
    }
    //now comes the difficult part
    //figure out the stroke intervals that are possible
    vector<pair<int,int>>strokes[26];
    for (int i = 0; i < 26; i++){
        if (fnd[i].empty()){
            continue;
        }
        int init = fnd[i][0];
        for (int j = 0; j < fnd[i].size(); j++){
            if (j == fnd[i].size()-1){
                strokes[i].push_back({init,fnd[i][j]});
                break;
            }
            if (nextsmallest[fnd[i][j]] < fnd[i][j+1]){
                strokes[i].push_back({init,nextsmallest[fnd[i][j]]});
                init = fnd[i][j+1];
            }
            else{
                continue;
            }
        }
    }
    while (q--){
        int a1, b1;
        cin >> a1 >> b1; a1--; b1--;
        int strk = 0;
        for (int i = 0; i < 26; i++){
            if (a1 == 0){
                break;
            }
            if (strokes[i].empty()){
                continue;
            }
            if (strokes[i][0].first > a1){
                continue;
            }
            strk += lower_bound(strokes[i].begin(),strokes[i].end(),make_pair(a1,1000000007)) - strokes[i].begin();
        }
        for (int i = 0; i < 26; i++){
            if (b1 == n-1){
                break;
            }
            if (strokes[i].empty()){
                continue;
            }
            if (strokes[i][strokes[i].size()-1].second < b1){
                continue;
            }
            auto it = lower_bound(strokes[i].begin(),strokes[i].end(),make_pair(b1,1000000007));
            if (it != strokes[i].begin()){
                if (it == strokes[i].end()){
                    if (prev(it)->first == b1){
                        it--;
                    }
                }
                else if (prev(it)->second >= b1 || prev(it)->first == b1){
                    it--;
                }
            }
            strk += strokes[i].end()-it;
        }
        cout << strk << "\n";
    }
}

