#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m;
    cin >> n >> m;
    vector<long long>a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(),a.end());
    long long currans = 0;
    for (int i = 0; i < n; i++){
        if (i < m){
            currans += a[i];
        }
        else{
            a[i] += a[i-m];
            currans += a[i];
        }
        cout << currans << "\n";
    }
}
