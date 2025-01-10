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
        input = "(a(b(2))(c))";
        slen = input.size();
        /*for (auto i : input) {
            token.push_back("" + i);
        }*/
    }
    void getSymbol() {
        if (index >= slen) {
            cout << "getSymbol: out of token range" << endl;
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
    bool lexp(int depth) {
        start("lexp", depth);
        if (atom(depth + 1) or list(depth + 1)) {
            success("lexp");
            return true;
        }
        failed("lexp", depth);
        return false;
    }
    bool atom(int depth) {
        start("atom", depth);
        oldIndex = index;
        getSymbol();
        if (symbol >= '0' and symbol <= '9') {
            string tmp(1, symbol);
            start(tmp, depth + 1);
            success("atom");
            return true;
        } else if (symbol >= 'a' and symbol <= 'z') {
            string tmp(1, symbol);
            start(tmp, depth + 1);
            success("atom");
            return true;
        }
        failed("atom", depth);
        index = oldIndex;
        return false;
    }
    bool list(int depth) {
        start("list", depth);
        oldIndex = index;
        getSymbol();
        if (symbol == '(') {
            start("(", depth + 1);
            if (lexpSeq0(depth + 1)) {
                getSymbol();
                if (symbol == ')') {
                    start(")", depth + 1);
                    success("list");
                    return true;
                }
            }
        }
        failed("list", depth);
        index = oldIndex;
        return false;
    }
    bool lexpSeq0(int depth) {
        start("lexp-seq", depth);
        if (lexp(depth + 1)) {
            if (lexpSeq1(depth + 1)) {
                success("lexp-seq");
                return true;
            }
        }
        failed("lexp-seq", depth);
        return false;
    }
    bool lexpSeq1(int depth) {
        start("lexp-seq'", depth);
        if (lexp(depth + 1)) {
            if (lexpSeq1(depth + 1)) {
                success("lexp-seq'");
                return true;
            }
        }
        success("lexp-seq'");
        return true;
    }
};

int main() {
    // cout << "unit test" << endl;
    PARSER parser;
    parser.getToken();
    if (parser.lexp(1)) {
        cout << "LL(1) parse success" << endl;
    } else {
        cout << "LL(1) parse failed";
    }
    return 0;
}