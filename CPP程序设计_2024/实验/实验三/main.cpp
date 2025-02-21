#include "person.h"

int main() {
    Report report;

    // 创建各类人员对象
    Manager manager1(1, "Alice", "Female", "2020-01-01", 5000, 1000);
    Manager manager2(2, "Adam", "Male", "2020-05-01", 6000, 2000);
    Technicist technicist1(3, "Bob", "Male", "2019-05-15", 4000);
    Technicist technicist2(4, "Tom", "Male", "2019-05-15", 6000);
    SalesPerson salesPerson1(5, "Charlie", "Male", "2021-07-20", 3000, 20000);

    // 向报表中添加人员信息
    report.insert(&manager1);
    report.insert(&manager2);
    report.insert(&technicist1);
    report.insert(&technicist2);
    report.insert(&salesPerson1);

    // 输出当月员工薪酬情况报表
    report.print();

    // 查找特定职位的员工
    vector<Employee*> managers = report["Manager"];
    cout << "\nManagers:" << endl;
    for (const auto& manager : managers) {
        cout << *manager << endl;
    }

    return 0;
}