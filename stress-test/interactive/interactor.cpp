// Simple interactive judge in C++
// Usage: ./interactor <hidden_number> <max_queries>
// Protocol: contestant sends lines like "? x" or "! y". Judge replies with "<", ">", "=" or prints "OK"/"WA" and exits.

#include <bits/stdc++.h>
using namespace std;

void fail(const string &msg = "WA") {
    cout << "WA" << endl; // judge output
    cerr << "#INTERACTOR# " << msg << '\n';
    exit(1);
}

void ok(const string &msg = "OK") {
    cout << "OK" << endl;
    cerr << "#INTERACTOR# " << msg << '\n';
    exit(0);
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc < 3) {
        cerr << "Usage: interactor <hidden_number> <max_queries>\n";
        return 2;
    }
    long long H = atoll(argv[1]);
    int maxq = atoi(argv[2]);
    int qcount = 0;
    string line;
    try {
        while (true) {
            if (!std::getline(cin, line)) {
                fail("EOF from contestant");
            }
            if (line.empty()) continue;
            cerr << "#INTERACTOR-RECV# " << line << '\n';
            if (line[0] == '?') {
                qcount++;
                if (qcount > maxq) fail("too many queries (" + to_string(qcount) + ")");
                stringstream ss(line);
                string qsym; long long x; ss >> qsym >> x;
                if (ss.fail()) fail("bad integer in query");
                if (H < x) cout << "<" << endl;
                else if (H > x) cout << ">" << endl;
                else cout << "=" << endl;
            } else if (line[0] == '!') {
                stringstream ss(line);
                string bang; long long y; ss >> bang >> y;
                if (ss.fail()) fail("bad integer in answer");
                if (y == H) ok("correct");
                else fail(string("wrong answer: expected ") + to_string(H) + string(", got ") + to_string(y));
            } else {
                fail("unknown command");
            }
        }
    } catch (exception &e) {
        fail(string("exception in interactor: ") + e.what());
    }
    return 0;
}