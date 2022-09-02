#include <bits/stdc++.h>
using namespace std;

#define int long long

int rnd(int l, int r) {
    return l + rand() % (r - l + 1);
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


int32_t main() {
    srand(time(0));

    for (int t = 0;; t++) {
        cout << "testing: " << t << endl;

        ofstream out("in.txt");

        {
            int n = 1000;
            out << n << "\n";
            for (int i = 0; i < n; i++){
//                char c = ('a' + rnd(0,16));
//                out << (rnd(0,2) ? '?' : c);
                out << '?';
            }
            out << "\n";
            int q = rnd(10, 15);
            out << q << "\n";
            for (int i = 0; i < q; i++){
                int sz = rnd(1, 17);
                unordered_set<char> s;
                for (int j = 0; j <= sz; j++){
                    char c = ('a' + rnd(0,16));
                    s.insert(c);
                }
                for (char c : s){
                    out << c;
                }
                out << "\n";
            }
        }

        out.close();

        system("C:\\Users\\samar\\Coding\\Competitive_Programming\\cmake-build-debug\\real.exe < in.txt > out1.txt");
        system("C:\\Users\\samar\\Coding\\Competitive_Programming\\cmake-build-debug\\brute.exe < in.txt > out2.txt");

        if (!equal("out1.txt", "out2.txt")) {
            cout << "difference found\n";
            return 0;
        }
    }
}