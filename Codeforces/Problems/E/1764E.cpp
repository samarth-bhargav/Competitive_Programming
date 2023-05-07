#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<array<int, 2>> ab;
        array<int, 2> first;
        for (int i = 0; i < n; i++){
            int a, b; cin >> a >> b;
            ab.push_back({a,b});
            if (i == 0){
                first = {a,b};
            }
        }
        ab.erase(find(ab.begin(), ab.end(), first));
        sort(ab.begin(), ab.end(), [&](array<int, 2> x, array<int, 2>y) -> bool{
            if (x[0] + x[1] == y[0] + y[1]){
                return x[0] < y[0];
            }
            return x[0] + x[1] > y[0] + y[1];
        });
        if (ab.empty()){
            cout << (k > first[0] ? "NO" : "YES") << "\n";
            continue;
        }
        int goal = k - first[1];
        if (goal > first[0]){
            cout << "NO\n";
            continue;
        }
        if (first[0] >= k){
            cout << "YES\n";
            continue;
        }
//        for (int i = 0; i < n-1; i++){
//            cout << ab[i][0] << " " << ab[i][1] << "\n";
//        }
//        cout << "\n";
        for (int i = 0; i < ab.size(); i++){
            if (i == ab.size()-1){
                if (ab[i][0] >= goal){
                    cout << "YES\n";
                    break;
                }
                else{
                    cout << "NO\n";
                    break;
                }
            }
            if (ab[i][0] >= goal){
                cout << "YES\n";
                break;
            }
            if (ab[i][0] + ab[i][1] >= goal){
                if (ab[i+1][0] + ab[i+1][1] >= goal){
                    cout << "YES\n";
                    break;
                }
                else{
                    goal -= ab[i][1];
                }
            }
            else{
                cout << "NO\n";
                break;
            }
        }
    }
}
