#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct PageInfo {
    vector<int> serial;  // 模拟的访问页面序列
    int diseffect;       // 缺页次数
} pf_info;

vector<int> pageframe;  // 分配的页框

void createps() {
    // 这里可以填入一个固定的序列，或者从文件中读取
    int fixed_sequence[] = {2, 7, 1, 3, 5, 0, 8, 9, 4, 6, 2, 7, 1, 0,
                            5, 3, 9, 8, 6, 4, 2, 0, 7, 1, 4, 5, 9, 6,
                            3, 8, 1, 0, 7, 2, 3, 4, 6, 9, 5, 8};
    for (int page : fixed_sequence) {
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

void FIFO(int total_pf) {
    pf_info.diseffect = 0;
    pageframe.assign(total_pf, -1);
    int rpoint = 0;

    for (int page : pf_info.serial) {
        if (findpage(page) == 0) {  // 若页不存在，则需装入页面
            pageframe[rpoint % total_pf] = page;
            rpoint++;
            pf_info.diseffect++;  // 缺页次数加1
        }
    }

    double page_fault_rate =
        static_cast<double>(pf_info.diseffect) / pf_info.serial.size();
    ofstream outfile("page_fault_rates.txt", ios::app);  // 追加模式写入文件
    outfile << total_pf << " " << fixed << setprecision(4) << page_fault_rate
            << endl;
}

int main() {
    createps();  // 创建访问序列

    ofstream outfile("page_fault_rates.txt",
                     ios::trunc);  // 清空文件并写入新内容
    outfile << "Physical_Page_Number Page_Fault_Rate" << endl;

    for (int pf_num = 1; pf_num <= 18; ++pf_num) {
        FIFO(pf_num);  // 执行FIFO置换算法
    }

    return 0;
}
