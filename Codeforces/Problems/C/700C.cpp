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
    int lo = 1, hi = n;
    int ar[n+1]; memset(ar,0,sizeof(ar));
    while (true){
        int mid = (lo+hi+1)/2;
        int valmid, vallo = 1e9, valhi = 1e9;
        if (ar[mid] == 0){
            cout << "? " << mid << endl;
            cin >> valmid;
            ar[mid] = valmid;
        }
        else{
            valmid = ar[mid];
        }
        if (mid != 1){
            if (ar[mid-1] == 0){
                cout << "? " << mid-1 << endl;
                cin >> vallo;
                ar[mid-1] = vallo;
            }
            else{
                vallo = ar[lo];
            }
        }
        if (mid != n){
            if (ar[mid+1] == 0){
                cout << "? " << mid+1 << endl;
                cin >> valhi;
                ar[mid+1] = valhi;
            }
            else{
                valhi = ar[mid+1];
            }
        }
        if ((mid == 1 || vallo > valmid) && (mid == n || valhi > valmid)){
            cout << "! " << mid << endl;
            return 0;
        }
        else if (mid > 1 && vallo < valmid){
            hi = mid-1;
            continue;
        }
        lo = mid;
    }
}

