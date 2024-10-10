#include <iostream>
#include <vector>

using namespace std;

class PARSER {
   public:
    vector<string> token;
    string input;
    char symbol;
    int index = 0, oldIndex = 0, slen = 0;
    void getToken() {
        // cin >> input;
        input = "a*b+b*(d)";
        slen = input.size();
        /*for (auto i : input) {
            token.push_back("" + i);
        }*/
    }
    void getSymbol() {
        if (index >= slen) {
            // cout << "getSymbol: out of token range" << endl;
            symbol = '`';
            index++;
            return;
        }
        symbol = input[index];
        index++;
        // cout << symbol << endl;
    }
    void start(string func, int depth) {
        for (int i = 0; i < depth; i++) {
            cout << "   |";
        }
        cout << "--" + func << endl;
    }
    void success(string func) {}
    void failed(string func, int depth) {
        for (int i = 0; i < depth; i++) {
            cout << "   |";
        }
        cout << "--" + func + ": rollback" << endl;
        // cout << "Err: " + func + " rollback" << endl;
        //  cout << func + " failed" << endl;
    }
    bool E0(int depth) {
        start("E", depth);
        if (T0(depth + 1)) {
            if (E1(depth + 1)) {
                success("E");
                return true;
            }
        }
        failed("E", depth);
        return false;
    }
    bool E1(int depth) {
        start("E'", depth);
        oldIndex = index;
        getSymbol();
        if (symbol == '+') {
            string tmp(1, symbol);
            start(tmp, depth + 1);
            if (T0(depth)) {
                if (E1(depth)) {
                    success("E'");
                    return true;
                }
            }
        }
        index = oldIndex;
        success("E'");
        return true;
    }
    bool T0(int depth) {
        start("T", depth);
        if (F(depth + 1)) {
            if (T1(depth + 1)) {
                success("T");
                return true;
            }
        }
        failed("T", depth);
        return false;
    }
    bool T1(int depth) {
        start("T'", depth);
        oldIndex = index;
        getSymbol();
        if (symbol == '*') {
            start("*", depth + 1);
            if (F(depth + 1)) {
                if (T1(depth + 1)) {
                    success("T'");
                    return true;
                }
            }
        }
        index = oldIndex;
        success("T'");
        return true;
    }
    bool F(int depth) {
        start("F", depth);
        getSymbol();
        if (symbol == '(') {
            start("(", depth + 1);
            if (E0(depth + 1)) {
                getSymbol();
                if (symbol == ')') {
                    start(")", depth + 1);
                    success("F");
                    return true;
                }
            }
            failed("F", depth + 1);
            return false;
        }
        if (symbol >= 'a' and symbol <= 'z') {
            string tmp(1, symbol);
            start(tmp, depth + 1);
            success("F");
            return true;
        }
        failed("F", depth + 1);
        return false;
    }
};

int main() {
    // cout << "unit test" << endl;
    PARSER parser;
    parser.getToken();
    if (parser.E0(1)) {
        cout << "LL(1) parse success" << endl;
    } else {
        cout << "LL(1) parse failed" << endl;
    }
    return 0;
}