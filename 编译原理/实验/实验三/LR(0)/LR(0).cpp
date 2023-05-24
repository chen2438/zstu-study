#include <iostream>
#include <stack>

using namespace std;

#define maxNumberOfState 100
#define maxNumberOfTerminal 100
#define maxNumberOfNonTerminal 100

int numberOfState, numberOfTerminal, numberOfNonTerminal;
stack<char> parsingStack, inputStack;
string inputString;
string terminals = "a+()$";
string nonTerminals = "ET";
string actionTableString, gotoTableString;

struct Node {
    int op;//Shift or Reduce
    int state;//状态
};

Node actionTable[maxNumberOfState][maxNumberOfTerminal];
int gotoTable[maxNumberOfState][maxNumberOfNonTerminal];

void init() {
    numberOfState = 9;
    numberOfTerminal = terminals.size();
    numberOfNonTerminal = nonTerminals.size();
    actionTableString = "s4!!s3!!!!\
!!s5!!!!AC\
r2r2r2r2r2\
s4!!s3!!!!\
r4r4r4r4r4\
s4!!s3!!!!\
r1r1r1r1r1\
r3r3r3r3r3";
    gotoTableString = "12\
!!\
!!\
62\
!!\
!7\
!!\
!!\
!!";
    for (int i = 0; i < numberOfState; i++) {
        for (int j = 0; j < numberOfTerminal * 2; j += 2) {
            int x1 = actionTableString[i * numberOfTerminal * 2 + j];
            int x2 = actionTableString[i * numberOfTerminal * 2 + j + 1];
            if (x1 == 'A') {
                actionTable[i][terminals[j / 2]] = { x1, x2 };
            } else if (x1 != '!') {
                x2 -= '0';
                actionTable[i][terminals[j / 2]] = { x1, x2 };
            } else {
                actionTable[i][terminals[j / 2]] = { '!', '!' };
            }
        }
    }
    for (int i = 0; i < numberOfState; i++) {
        for (int j = 0; j < numberOfNonTerminal; j++) {
            int x1 = gotoTableString[i * numberOfNonTerminal * 2 + j];
            if (x1 != '!') {
                x1 -= '0';
                gotoTable[i][nonTerminals[j / 2]] = x1;
            } else {
                gotoTable[i][nonTerminals[j / 2]] = '!';
            }
        }
    }
    cout << actionTable[1]['$'].op << endl;
    cout << gotoTable[4]['T'] << endl;
    exit(0);
    inputString = "(a+a)+(a)+a";
    int inputLenth = inputString.size();
    parsingStack.push('$');
    inputStack.push('$');
    for (int i = inputLenth - 1; i >= 0; i--) {
        inputStack.push(inputString[i]);
    }

}

void solve() {
    init();

}

int main() {
    solve();
}


