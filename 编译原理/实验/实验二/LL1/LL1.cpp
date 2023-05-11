#include <iostream>
#include <vector>

using namespace std;

class PARSER {
   public:
    vector<string> token;
    string input;
    char symbol;
    int index = 0, oldIndex = 0;
    void getToken() {
        // cin >> input;
        input = "(a(b(2))(c))";
        /*for (auto i : input) {
            token.push_back("" + i);
        }*/
    }
    void getSymbol() {
        symbol = input[index];
        index++;
        cout << symbol << endl;
    }
    void start(string func) { cout << func + " start" << endl; }
    void success(string func) { cout << func + " success" << endl; }
    void failed(string func) { cout << func + " failed" << endl; }
    bool lexp() {
        start("lexp");
        if (atom() or list()) {
            success("lexp");
            return true;
        }
        failed("lexp");
        return false;
    }
    bool atom() {
        start("atom");
        oldIndex = index;
        getSymbol();
        if (symbol >= '0' and symbol <= '9') {
            success("atom");
            return true;
        } else if (symbol >= 'a' and symbol <= 'z') {
            success("atom");
            return true;
        }
        failed("atom");
        index = oldIndex;
        return false;
    }
    bool list() {
        start("list");
        cout << "list start" << endl;
        oldIndex = index;
        getSymbol();
        if (symbol == '(') {
            if (lexpSeq0()) {
                getSymbol();
                if (symbol == ')') {
                    success("list");
                    return true;
                }
            }
        }
        failed("list");
        index = oldIndex;
        return false;
    }
    bool lexpSeq0() {
        start("lexp-seq");
        if (lexp()) {
            if (lexpSeq1()) {
                success("lexp-seq");
                return true;
            }
        }
        failed("lexp-seq");
        return false;
    }
    bool lexpSeq1() {
        start("lexp-seq'");
        if (lexp()) {
            if (lexpSeq1()) {
                success("lexp-seq'");
                return true;
            }
        }
        success("lexp-seq'");
        return true;
    }
};

int main() {
    cout << "hello, world" << endl;
    PARSER parser;
    parser.getToken();
    if (parser.lexp()) {
        cout << "LL(1) parse success" << endl;
    } else {
        cout << "LL(1) parse failed";
    }
    return 0;
}