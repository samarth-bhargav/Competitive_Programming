#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, q; cin >> n >> q;
    string s; cin >> s;
    for (int i = 0; i < q; i++){
        int idx; char c;
        cin >> idx >> c; idx--;
        s[idx] = c;
        int first_a = -1, last_c = -1, first_b = -1, last_b = -1;
        for (int j = 0; j < n; j++){
            if (s[j] == 'a'){
                first_a = j;
                break;
            }
        }
        for (int j = n-1; j > 0; j--){
            if (s[j] == 'c'){
                last_c = j;
                break;
            }
        }
        if (first_a == -1 || last_c == -1){
            cout << 0 << "\n";
            continue;
        }
        if (first_a > last_c){
            cout << 0 << "\n";
            continue;
        }
        int l = first_a, r = last_c;
        for (int j = l; j <= r; j++){
            if (s[j] == 'b'){
                first_b = j;
                break;
            }
        }
        for (int j = r; j >= l; j--){
            if (s[j] == 'b'){
                last_b = j;
                break;
            }
        }
        if (first_b == -1){
            cout << 0 << "\n";
            continue;
        }
        int ans = 1e9;
        int temp = 0;
        for (int j = l; j < last_b; j++){
            temp += (s[j] == 'a');
        }
        ans = min(ans, temp);
        temp = 0;
        for (int j = r; j > first_b; j--){
            temp += (s[j] == 'c');
        }
        ans = min(ans, temp);
        ans = min(ans, (int)count(s.begin()+l, s.begin()+r+1, 'b'));
        cout << ans << "\n";
    }
}
