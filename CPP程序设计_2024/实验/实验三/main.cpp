#include "person.h"

int main() {
    Report report;

    // ����������Ա����
    Manager manager1(1, "Alice", "Female", "2020-01-01", 5000, 1000);
    Manager manager2(2, "Adam", "Male", "2020-05-01", 6000, 2000);
    Technicist technicist1(3, "Bob", "Male", "2019-05-15", 4000);
    Technicist technicist2(4, "Tom", "Male", "2019-05-15", 6000);
    SalesPerson salesPerson1(5, "Charlie", "Male", "2021-07-20", 3000, 20000);

    // �򱨱��������Ա��Ϣ
    report.insert(&manager1);
    report.insert(&manager2);
    report.insert(&technicist1);
    report.insert(&technicist2);
    report.insert(&salesPerson1);

    // �������Ա��н���������
    report.print();

    // �����ض�ְλ��Ա��
    vector<Employee*> managers = report["Manager"];
    cout << "\nManagers:" << endl;
    for (const auto& manager : managers) {
        cout << *manager << endl;
    }

    return 0;
}