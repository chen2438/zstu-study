#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct PageInfo {
    vector<int> serial;  // 模拟的访问页面序列
    int diseffect;       // 缺页次数
    int total_pf;        // 分配的页框数
} pf_info;

vector<int> pageframe;  // 分配的页框

void createps() {
    string line;
    cout << "请输入页面访问序列，以空格分隔，按回车结束：" << endl;
    getline(cin, line);
    stringstream ss(line);
    int page;
    while (ss >> page) {
        pf_info.serial.push_back(page);
    }
}

int findpage(int page) {
    for (size_t i = 0; i < pageframe.size(); i++) {
        if (pageframe[i] == page) {
            return 1;  // 页面存在于内存中
        }
    }
    return 0;  // 页面不存在，缺页
}

void displayinfo(int id, int page, int pstate) {
    cout << "ID: " << setw(2) << id << " 访问 " << setw(2) << page
         << ". 内存状态:<";
    for (size_t i = 0; i < pageframe.size(); i++) {
        if (pageframe[i] != -1) {
            cout << setw(2) << pageframe[i];
        } else {
            cout << "  ";  // 空白占位
        }
        if (i < pageframe.size() - 1) {
            cout << ",";
        }
    }
    cout << ">";
    if (pstate == 0) {
        cout << " 缺页,";
    }
    cout << " 缺页率=" << fixed << setprecision(1)
         << (static_cast<double>(pf_info.diseffect) / (id + 1)) * 100.0 << "%"
         << endl;
}

void FIFO() {
    pf_info.diseffect = 0;
    pageframe.assign(pf_info.total_pf, -1);
    int rpoint = 0;

    cout << " ---FIFO Algorithm: " << pf_info.total_pf << " frames---" << endl;

    for (size_t i = 0; i < pf_info.serial.size(); i++) {
        int page = pf_info.serial[i];
        int pstate = findpage(page);

        if (pstate == 0) {  // 若页不存在，则需装入页面
            pageframe[rpoint % pf_info.total_pf] = page;
            rpoint++;
            pf_info.diseffect++;  // 缺页次数加1
        }

        displayinfo(i, page, pstate);  // 显示当前状态
    }

    cout << "总缺页数=" << pf_info.diseffect << "，总缺页率=" << fixed
         << setprecision(1)
         << (static_cast<double>(pf_info.diseffect) / pf_info.serial.size()) *
                100.0
         << "%" << endl;
}

int main() {
    createps();
    cout << "Please input physical page number: ";
    cin >> pf_info.total_pf;
    cin.ignore();
    FIFO();
}
