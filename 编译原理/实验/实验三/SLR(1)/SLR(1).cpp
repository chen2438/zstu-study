#include <iomanip>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int table[20][20][2];  // I,(non)terminals,action
int mp[200];           // 映射
string terminals = "+*()i$ETF";
string inputString = "(a+b)*c+(d+e)";
stack<int> pStk, iStk;    // parse stack, input stack
stack<int> reduceResult;  // 存储规约结果, 用于分析树
string reduce[7][2];      // 规约
int step = 1;

namespace Graph {  // 处理分析树
    const int N = 1000, M = N * 2;
    int nodemap[N] = { 0, 'E' };
    int depth[N];

    struct Edge {
        int to, nxt;
    } e[M];

    int adt, head[N];

    void add(int u, int v) {
        e[++adt] = { v, head[u] };
        head[u] = adt;
    }

    int fa[N];

    void dfs(int p1) {  // 输出分析树
        for (int i = 0; i < depth[p1]; i++) {
            cout << "   |";
        }
        cout << "--" << (char)nodemap[p1] << endl;
        for (int i = head[p1]; i != 0; i = e[i].nxt) {
            int p2 = e[i].to;
            if (p2 == fa[p1]) continue;
            fa[p2] = p1;
            dfs(p2);
        }
    }

    void parseTree() {
        int vst[1000] = { 0 };
        depth[1] = 0;
        int cnt = 2;
        while (!reduceResult.empty()) {  // 读出规约结果
            int rTop = reduceResult.top();
            reduceResult.pop();
            int leftChar = reduce[rTop][0][0];     // 产生式左部
            string rightString = reduce[rTop][1];  // 产生式右部
            int oldCnt = cnt;
            for (int j = oldCnt - 1; j >= 1; j--) {  // 从右往左匹配父节点
                if (nodemap[j] == leftChar and !vst[j]) {
                    vst[j] = 1;
                    for (char k : rightString) {
                        nodemap[cnt] = k;  // 给节点编号 加映射
                        depth[cnt] = depth[j] + 1;
                        add(j, cnt);
                        cnt++;
                    }
                    break;
                }
            }
        }
        dfs(1);
    }
}  // namespace Graph

stack<int> reverse(stack<int> s) {
    stack<int> tmp;
    while (!s.empty()) {
        tmp.push(s.top());
        s.pop();
    }
    s = tmp;
    return s;
}

string reverse(string s) {  // 禁止使用引用
    reverse(s.begin(), s.end());
    return s;
}

void show(stack<int> ps, stack<int> is) {
    ps = reverse(ps);
    int width = 25;
    string str1, str2;
    int odd = 1;
    while (!ps.empty()) {
        if (odd == 1)
            str1 += (char)ps.top();
        else
            str1 += to_string(ps.top());
        odd *= -1;
        ps.pop();
    }
    while (!is.empty()) {
        str2 += (char)is.top();
        is.pop();
    }
    string strBlank(width - str1.size() - str2.size(), ' ');
    cout << str1 << strBlank << str2;
}

void init() {
    for (int i = 0; i < terminals.size(); i++) {
        mp[terminals[i]] = i;       // 映射 (non)terminals -> number
        if (terminals[i] == 'i') {  // id = {a ~ z}
            for (int j = 'a'; j <= 'z'; j++) {
                mp[j] = i;
            }
        }
    }
    for (int i = 0; i <= 11; i++) {
        for (int j = 0; j < terminals.size(); j++) {
            char c;
            cin >> c;
            table[i][j][0] = c;
        }
    }
    for (int i = 0; i <= 11; i++) {
        for (int j = 0; j < terminals.size(); j++) {
            int num;
            cin >> num;
            table[i][j][1] = num;
        }
    }
    for (int i = 0; i < 7; i++) {
        cin >> reduce[i][0] >> reduce[i][1];
        reduce[i][1] = reverse(reduce[i][1]);
    }
}

int parseTable() {
    pStk.push('$');
    pStk.push(0);
    iStk.push('$');
    for (int i = inputString.size() - 1; i >= 0; i--) {
        iStk.push(inputString[i]);
    }
    cout << "---------------------------"
        << "--------------------------" << endl;
    cout << "Step   Parsing Stack       Input    Action" << endl;
    while (!iStk.empty() and !pStk.empty()) {
        cout << step << "     ";
        if (step++ < 10) putchar(' ');
        show(pStk, iStk);
        int pTop = pStk.top(), iTop = iStk.top();
        int action[2] = { table[pTop][mp[iTop]][0], table[pTop][mp[iTop]][1] };
        if (action[0] == 'A') {  // 接受
            cout << "    Accept" << endl;
            return 200;
        } else if (action[0] == 'S') {  // 移进
            cout << "    Shift " << action[1] << endl;
            pStk.push(iTop);
            pStk.push(action[1]);
            iStk.pop();
        } else if (action[0] == 'R') {  // 规约
            reduceResult.push(action[1]);

            cout << "    Reduce " << action[1] << ": " + reduce[action[1]][0] + " -> "
                << reverse(reduce[action[1]][1]) << endl;

            for (auto i : reduce[action[1]][1]) {
                while (!pStk.empty()) {
                    int c = pStk.top();
                    pStk.pop();
                    if (c == i) break;
                    if (i == 'i') {
                        if ('a' <= c && c <= 'z') break;
                    }
                }
            }
            int pTop1 = pStk.top();
            pStk.push(reduce[action[1]][0][0]);
            int pTop2 = pStk.top();
            pStk.push(table[pTop1][mp[pTop2]][1]);
        } else {
            return 500;
        }
    }
    return 500;
}

void solve() {
    init();
    int res = parseTable();
    if (res == 200) {
        puts("\nParsing Success");
    } else {
        puts("\nParsing Failed");
    }
    puts("\nParsing Tree:");
    Graph::parseTree();
}

int main() {
    FILE* fp;
    freopen_s(&fp, "input.txt", "r", stdin);
    // freopen("../input.txt", "r", stdin);
    solve();
    // fclose(fp);
}
