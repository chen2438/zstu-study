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
            cout << "getSymbol: out of token range" << endl;
            symbol = '`';
            index++;
            return;
        }
        symbol = input[index];
        index++;
        cout << symbol << endl;
    }
    void start(string func) { cout << func + " start" << endl; }
    void success(string func) { cout << func + " success" << endl; }
    void failed(string func) { cout << func + " failed" << endl; }
    bool E0() {
        start("E");
        if (T0()) {
            if (E1()) {
                success("E");
                return true;
            }
        }
        failed("E");
        return false;
    }
    bool E1() {
        start("E'");
        oldIndex = index;
        getSymbol();
        if (symbol == '+') {
            if (T0()) {
                if (E1()) {
                    success("E'");
                    return true;
                }
            }
        }
        index = oldIndex;
        success("E'");
        return true;
    }
    bool T0() {
        start("T");
        if (F()) {
            if (T1()) {
                success("T");
                return true;
            }
        }
        failed("T");
        return false;
    }
    bool T1() {
        start("T'");
        oldIndex = index;
        getSymbol();
        if (symbol == '*') {
            if (F()) {
                if (T1()) {
                    success("T'");
                    return true;
                }
            }
        }
        index = oldIndex;
        success("T'");
        return true;
    }
    bool F() {
        start("F");
        getSymbol();
        if (symbol == '(') {
            if (E0()) {
                getSymbol();
                if (symbol == ')') {
                    success("F");
                    return true;
                }
            }
            failed("F");
            return false;
        }
        if (symbol >= 'a' and symbol <= 'z') {
            success("F");
            return true;
        }
        failed("F");
        return false;
    }
};

int main() {
    // cout << "hello, world" << endl;
    PARSER parser;
    parser.getToken();
    if (parser.E0()) {
        cout << "LL(1) parse success" << endl;
    } else {
        cout << "LL(1) parse failed";
    }
    // 到最后的处理
    return 0;
}