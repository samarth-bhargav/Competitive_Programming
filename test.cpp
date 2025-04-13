#include <iostream>
#include <vector>

using namespace std;


#ifdef LOCAL
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 7;
#endif

vector<vector<int>> getDiagonals(const vector<vector<int>>& matrix) {
    vector<vector<int>> diagonals;
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Main diagonals
    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 0; j < cols - 2; ++j) {
            vector<int> main_diagonal = {matrix[i + 0][j + 0], matrix[i + 1][j + 1], matrix[i + 2][j + 2]};
            diagonals.push_back(main_diagonal);
        }
    }

    // Off-diagonals
    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 0; j < cols - 2; ++j) {
            vector<int> off_diagonal = {matrix[i + 0][j + 2], matrix[i + 1][j + 1], matrix[i + 2][j + 0]};
            diagonals.push_back(off_diagonal);
        }
    }

    return diagonals;
}

int main() {
    vector<vector<int>> g(5, vector<int>(5, 0));

    for (int i = (1 << 22); i < (1 << 25); ++i) {
//        if (i == 0b1010010110100101){
//            dbg("hi");
//        }
//        if (i % 10000 == 0){
//            cout << i << "\n";
//        }
        for (int j = 0; j < 25; ++j) {
            if (i & (1 << j)) {
                g[j / 5][j % 5] = 1;
            }
            else{
                g[j / 5][j % 5] = 0;
            }
        }

        bool good = true;
        for (int ii = 0; ii < 5; ++ii) {
            for (int j = 0; j < 3; ++j) {
                if (g[ii][j] == g[ii][j+1] && g[ii][j+1] == g[ii][j+2]) {
                    good = false;
                    break;
                }
                if (g[j][ii] == g[j+1][ii] && g[j+1][ii] == g[j+2][ii]) {
                    good = false;
                    break;
                }
            }
            if (!good) {
                break;
            }
        }


        vector<vector<int>> diagonals = getDiagonals({{0, 1, 2, 3, 4},
                                                      {5, 6, 7, 8, 9},
                                                      {10, 11, 12, 13, 14},
                                                      {15, 16, 17, 18, 19},
                                                      {20, 21, 22, 23, 24}});

//        if (good){
//            dbg(g);
//        }

        for (const auto& x : diagonals) {
            if (g[x[0] / 5][x[0] % 5] == g[x[1] / 5][x[1] % 5] && g[x[1] / 5][x[1] % 5] == g[x[2] / 5][x[2] % 5]) {
                good = false;
                break;
            }
        }

        if (good) {
            for (int ii = 0; ii < 5; ++ii) {
                for (int j = 0; j < 5; ++j) {
                    cout << g[ii][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    return 0;
}