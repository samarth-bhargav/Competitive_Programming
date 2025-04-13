#include <bits/stdc++.h>
using namespace std;

#define int long long

int rnd(int l, int r) {
    return l + (rand() * rand()) % (r - l + 1);
}

string rnd_str(int len){
    string ret = "";
    for (int i = 0; i < len; i++){
        ret += char(rnd(97, 97+1));
    }
    return ret;
}

vector<array<int, 2>> gen_tree(int sz){
    vector<int> p(sz+1);
    for (int i = 2; i <= sz; i++){
        p[i] = rnd(1, i-1);
    }
    vector<array<int, 2>> ret;
    for (int i = 2; i <= sz; i++){
        ret.push_back({i, p[i]});
    }
    return ret;
}

bool equal(string file1, string file2) {
    auto read_file = [&](string f) {
        vector<string> words;
        ifstream in(f);
        string token;
        while (in >> token) words.push_back(token);
        return words;
    };
    return read_file(file1) == read_file(file2);
}

int NUM_TESTCASES = 10;

int32_t main() {
    srand(time(NULL));
    std::random_device rd;
    std::mt19937 g(rd());
    for (int t = 0; t < 10; t++) {
        cout << "testing: " << t << endl;

        ofstream out("test\\" + to_string(t));

        {
            int n = rnd(3, 5);
            out << 1 << "\n";
            for (int i = 0; i < n; i++){
                out << rnd(1, 5) << " " << rnd(1, 5) << "\n";
            }
        }

        out.close();

        string cmd = "C:\\Users\\samar\\Coding\\Competitive_Programming\\cmake-build-debug\\real.exe < test\\" +
                          to_string(t)
                          + "> sol\\" + to_string(t);

        system(cmd.c_str());
    }
}
