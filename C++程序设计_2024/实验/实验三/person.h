#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

// ���� Employee �࣬��ʾԱ��
class Employee {
protected:
    int id;                          // Ա�����
    string name;                     // ����
    string gender;                   // �Ա�
    string hire_date;                // ��ְ����
    string position;                 // ְλ
    double base_salary;              // ��������

public:
    Employee(int id, const string& name, const string& gender, const string& hire_date, const string& position, double base_salary)
        : id(id), name(name), gender(gender), hire_date(hire_date), position(position), base_salary(base_salary) {}

    virtual double get_pay() const = 0;  // ��ȡ���ʣ����麯��

    friend ostream& operator<<(ostream& os, const Employee& emp) {
        os << setw(10) << emp.id << setw(20) << emp.name << setw(10) << emp.gender << setw(15) << emp.hire_date << setw(15) << emp.position << setw(10) << emp.get_pay();
        return os;
    }

    string get_position() const {
        return position;
    }

    int get_id() const {
        return id;
    }

    string get_name() const {
        return name;
    }

    string get_gender() const {
        return gender;
    }

    string get_hire_date() const {
        return hire_date;
    }
};

// ���� Manager �࣬��ʾ�����̳��� Employee ��
class Manager : public Employee {
private:
    double bonus;  // ����

public:
    Manager(int id, const string& name, const string& gender, const string& hire_date, double base_salary, double bonus)
        : Employee(id, name, gender, hire_date, "Manager", base_salary), bonus(bonus) {}

    double get_pay() const override {
        return base_salary + bonus;
    }
};

// ���� Technicist �࣬��ʾ������Ա���̳��� Employee ��
class Technicist : public Employee {
public:
    Technicist(int id, const string& name, const string& gender, const string& hire_date, double base_salary)
        : Employee(id, name, gender, hire_date, "Technicist", base_salary) {}

    double get_pay() const override {
        return base_salary;
    }
};

// ���� SalesPerson �࣬��ʾ������Ա���̳��� Employee ��
class SalesPerson : public Employee {
private:
    double sales_profit;  // ��������

public:
    SalesPerson(int id, const string& name, const string& gender, const string& hire_date, double base_salary, double sales_profit)
        : Employee(id, name, gender, hire_date, "SalesPerson", base_salary), sales_profit(sales_profit) {}

    double get_pay() const override {
        return base_salary + sales_profit * 0.05;
    }
};

// ���� Report �࣬�������ɱ���
class Report {
private:
    vector<Employee*> employees;  // Ա���б�

public:
    void insert(Employee* emp) {
        employees.push_back(emp);
    }

    // ��ӡ����
    void print() const {
        map<string, vector<Employee*>> grouped_by_position;
        for (const auto& emp : employees) {
            grouped_by_position[emp->get_position()].push_back(emp);
        }

        for (const auto& entry : grouped_by_position) {
            const string& position = entry.first;
            const vector<Employee*>& emps = entry.second;

            cout << "\nPosition: " << position << endl;
            cout << "---------------------------------------------------------------------------------------------------" << endl;
            cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Gender" << setw(15) << "Hire Date" << setw(15) << "Position" << setw(10) << "Salary" << endl;
            cout << "---------------------------------------------------------------------------------------------------" << endl;

            double max_salary = 0;
            double min_salary = numeric_limits<double>::max();

            for (const auto& emp : emps) {
                cout << *emp << endl;
                double salary = emp->get_pay();
                if (salary > max_salary) max_salary = salary;
                if (salary < min_salary) min_salary = salary;
            }

            cout << "---------------------------------------------------------------------------------------------------" << endl;
            cout << "Max Salary: " << max_salary << "  Min Salary: " << min_salary << endl;
        }
    }

    // ���������[]
    vector<Employee*> operator[](const string& position) const {
        vector<Employee*> result;
        for (const auto& emp : employees) {
            if (emp->get_position() == position) {
                result.push_back(emp);
            }
        }
        return result;
    }
};

#endif
