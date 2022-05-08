/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int>a(n);
    for (auto & i : a){
        cin >> i;
    }
    int currval = a[0];
    int currsize = 0;
    vector<int>segments;
    for (int i = 0; i < n; i++){
        if (a[i] != currval){
            segments.push_back(currsize);
            if (i != n-1){
                currval = a[i];
                currsize = 1;
            }
            else{
                currsize = 1;
                break;
            }
        }
        else{
            currsize++;
        }
    }
    if (currsize > 0){
        segments.push_back(currsize);
    }
    int ans = 0;
    for (int i = 0; i < segments.size(); i++){
        if (segments[i] == 1){
            ans++;
        }
        else if (segments[i] > 1){
            ans += 2;
        }
    }
    cout << ans << "\n";
}

