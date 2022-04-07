#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool know(int x){
    return x != 1e9;
}
void solve(){
    set<array<int,3>>solutions;
    int N;
    cin >> N;
    vector<int>X(7,1e9);
    for (int i = 0; i < N; i++){
        cin >> X[i];
    }
    sort(X.begin(),X.end());
    do{
        int A = 1e9,B = 1e9,C = 1e9,AB = 1e9,BC = 1e9,AC = 1e9,ABC = 1e9;
        if (X[0] != 1e9){A = X[0];}
        if (X[1] != 1e9){B = X[1];}
        if (X[2] != 1e9){C = X[2];}
        if (X[3] != 1e9){AB = X[3];}
        if (X[4] != 1e9){BC = X[4];}
        if (X[5] != 1e9){AC = X[5];}
        if (X[6] != 1e9){ABC = X[6];}
        while (true){
            bool change = false;
            if (know(A)&&know(B)&&!know(AB)){
                AB = A+B;
                change = true;
            }
            if (know(A)&&know(C)&&!know(AC)){
                AC = A+C;
                change = true;
            }
            if (know(B)&&know(C)&&!know(BC)){
                BC = B+C;
                change = true;
            }
            if (know(A)&&know(B)&&know(C)&&!know(ABC)){
                ABC = A+B+C;
                change = true;
            }
            if (know(A)&&know(AB)&&!know(B)){
                B = AB-A;
                change = true;
            }
            if (know(A)&&know(AC)&&!know(C)){
                C = AC-A;
                change = true;
            }
            if (know(B)&&know(AB)&&!know(A)){
                A = AB-B;
                change = true;
            }
            if (know(B)&&know(BC)&&!know(C)){
                C = BC-B;
                change = true;
            }
            if (know(C)&&know(AC)&&!know(A)){
                A = AC-C;
                change = true;
            }
            if (know(C)&&know(BC)&&!know(B)){
                B = BC-C;
                change = true;
            }
            if (know(ABC)){
                if (know(AB)&&!know(C)){
                    C = ABC-AB;
                    change = true;
                }
                if (know(BC)&&!know(A)){
                    A = ABC-BC;
                    change = true;
                }
                if (know(AC)&&!know(B)){
                    B = ABC-AC;
                    change = true;
                }
                if (know(A)&&!know(BC)){
                    BC = ABC-A;
                    change = true;
                }
                if (know(B)&&!know(AC)){
                    AC = ABC-B;
                    change = true;
                }
                if (know(C)&&!know(AB)){
                    AB = ABC-C;
                    change = true;
                }
                if (know(AB)&&know(BC)&&!know(AC)){
                    //(AB+BC+AC)/2 = ABC
                    AC = 2*ABC - AB - BC;
                    change = true;
                }
                if (know(AB)&&know(AC)&&!know(BC)){
                    BC = 2*ABC - AC - AB;
                    change = true;
                }
                if (know(BC)&&know(AC)&&!know(AB)){
                    AB = 2*ABC - BC - AC;
                    change = true;
                }
            }
            if (know(AB)&&know(BC)&&know(AC)&&!know(ABC)){
                ABC = (AB+BC+AC)/2;
            }
            if (!change){
                break;
            }
        }
        if (know(A)&&know(B)&&know(C)&&know(AB)&&know(AC)&&know(BC)&&know(ABC)){
            if (AB == A+B && AC == A+C && BC == B+C && ABC == A+B+C){
                if (A > 0 && B > 0 && C > 0){
                    solutions.insert({A,B,C});
                }
            }
        }
        else{
            assert(false);
        }
    } while (next_permutation(X.begin(),X.end()));
    cout << solutions.size() << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--){
        solve();
    }
}

