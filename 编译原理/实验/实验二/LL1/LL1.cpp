#include<iostream>
#include<vector>

using namespace std;

class PARSER {
public:
    vector<string> token;
    string input;
    char symbol;
    int index = -1, oldIndex = -1;
    void getToken() {
        cin >> input;
        /*for (auto i : input) {
            token.push_back("" + i);
        }*/
    }
    char getSymbol() {
        index++;
        cout << input[index] << endl;
        return input[index];
    }
    void success(string func) {
        cout << func + " parse success" << endl;
    }
    void failed(string func) {
        cout << func + " parse failed" << endl;
    }
    bool lexp() {
        if (atom() or list()) {
            success("lexp");
            return true;
        }
        failed("lexp");
        return false;
    }
    bool atom() {
        oldIndex = index;
        symbol = getSymbol();
        if (symbol > '0' and symbol < '9') {
            success("atom");
            return true;
        } else if (symbol > 'a' and symbol < 'z') {
            success("atom");
            return true;
        }
        failed("atom");
        index = oldIndex;
        return false;

    }
    bool list() {
        oldIndex = index;
        symbol = getSymbol();
        if (symbol == '(' and lexpSeq0()) {
            symbol = getSymbol();
            if (symbol == ')') {
                success("list");
                return true;
            }
        }
        failed("list");
        index = oldIndex;
        return false;
    }
    bool lexpSeq0() {
        if (lexp() and lexpSeq1()) {
            success("lexp-seq");
            return true;
        }
        failed("lexp-seq");
        return false;
    }
    bool lexpSeq1() {
        if (lexp() and lexpSeq1()) {
            success("lexp-seq'");
            return true;
        }
        success("lexp-seq'");
        return true;
    }
};

int main() {
    PARSER parser;
    parser.getToken();
    parser.lexp();

    //到最后的处理
    return 0;
}