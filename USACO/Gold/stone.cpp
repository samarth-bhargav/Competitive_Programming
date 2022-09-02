#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    map<int,int> freq;
    int x = *max_element(a.begin(), a.end());
    int cnt = 0;
    for (int k = 1; k <= x; k++){
        for (int i = 0; i < n; i++){
            if (a[i]/k != 0){
                freq[a[i]/k]++;
            }
        }
        if (freq.empty()){
            cnt++;
            freq.clear();
            continue;
        }
        for (int i = 0; i < n; i++){
            if (a[i]/k != 0){
                freq[a[i]/k]--;
                if (freq[a[i]/k] == 0){
                    freq.erase(a[i]/k);
                }
                if (a[i]/k != 1){
                    freq[a[i]/k - 1]++;
                }
                if (freq.empty()){
                    freq[a[i]/k]++;
                    cnt++;
                    continue;
                }
                bool flag = false;
                for (auto it = prev(freq.end()); it != freq.begin(); it--){
                    if (it->second % 2 == 1){
                        //elsie wins
                        flag = true;
                        break;
                    }
                }
                if (freq.begin() -> second % 2 == 1){
                    flag = true;
                }
                cnt += (!flag);
                freq[a[i]/k - 1]--;
                freq[a[i]/k]++;
            }
        }
        freq.clear();
    }
    cout << cnt << "\n";
}
