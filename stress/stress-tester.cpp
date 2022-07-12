#include <bits/stdc++.h>
using namespace std;

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


int main() {
    srand(time(0));

    for (int t = 0;; t++) {
        cout << "testing: " << t << endl;

        ofstream out("in.txt");

        {
            int n = 5;
            int m = rnd(1, 6);
            out << n << " " << m << "\n";
            for (int i = 0; i < m; i++){
                out << rnd(1, 5) << " " << rnd(1, 5) << "\n";
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