#include "stu.h"

#define echo(x) cout << x << endl

// 学生基类函数
Student::Student(string number, string name, string gender, int age,
                 string type)
    : number_(number), name_(name), gender_(gender), age_(age), type_(type) {}

ostream &operator<<(ostream &out, Student &stu) {
    out << stu.number_ << "\t" << stu.name_ << "\t" << stu.gender_ << "\t"
        << stu.age_ << "\t" << stu.type_ << "\t" << stu.get_point();
    return out;
}

// 本科生函数
CStudent::CStudent(string number, string name, string gender, int age,
                   string type, double english, double math, double computer)
    : Student(number, name, gender, age, type),
      english_(english),
      math_(math),
      computer_(computer) {}

double CStudent::get_point() {
    return english_ * 0.03 + math_ * 0.04 + computer_ * 0.03;
}

// 留学生函数
FStudent::FStudent(string number, string name, string gender, int age,
                   string type, double chinese, double math, double computer)
    : Student(number, name, gender, age, type),
      chinese_(chinese),
      math_(math),
      computer_(computer) {}

double FStudent::get_point() {
    return chinese_ * 0.03 + math_ * 0.04 + computer_ * 0.03;
}

// 研究生函数
GStudent::GStudent(string number, string name, string gender, int age,
                   string type, double philosophy, double math, double computer)
    : Student(number, name, gender, age, type),
      philosophy_(philosophy),
      math_(math),
      computer_(computer) {}

double GStudent::get_point() {
    return philosophy_ * 0.03 + math_ * 0.04 + computer_ * 0.03;
}

void Report::insert(Student *stu) { stu_list.push_back(stu); }  // 插入学生记录

void Report::print(vector<Student *> slist) {  // 显示学生信息
    cout << "学号\t姓名\t性别\t年龄\t类别\t\t绩点" << endl;
    string type[] = {"CStudent", "FStudent", "GStudent"};
    for (auto T : type) {
        for (auto stu : slist) {
            if (stu->type_ != T) continue;
            cout << *stu << endl;
        }
        cout << endl;
    }
}

int Report::del(string number) {  // 根据学号删除
    vector<Student *>::iterator it;
    for (it = stu_list.begin(); it != stu_list.end(); it++) {
        if ((*it)->number_ == number) {
            stu_list.erase(it);
            return 1;
        }
    }
    return 0;
}

vector<Student *> Report::operator[](
    string type) {  // 重载[]查找所有number类别的学生
    vector<Student *> res;
    for (auto stu : stu_list) {
        if (stu->type_ == type) {
            res.push_back(stu);
        }
    }
    return res;
}

void Report::stats() {  // 统计各类别学生的优秀率
    int num_sum[3] = {0}, qualified[3] = {0};
    double rate[3];
    string type[] = {"CStudent", "FStudent", "GStudent"};
    cout << "类别\t\t优秀率" << endl;
    for (int i = 0; i < 3; i++) {
        for (auto stu : stu_list) {
            if (stu->type_ == type[i]) {
                num_sum[i]++;
                if (stu->get_point() > 8.0) qualified[i]++;
            }
        }
        rate[i] = (qualified[i] * 1.0) / (num_sum[i] * 1.0);
        cout << type[i] << "\t" << rate[i] << endl;
    }
}

void Report::save() {  // 存储到文件
    ofstream file;
    file.open("stuInfo.txt");
    string type[] = {"CStudent", "FStudent", "GStudent"};
    for (auto T : type) {
        for (auto stu : stu_list) {
            if (stu->type_ != T) continue;
            file << *stu << endl;
        }
    }
    file.close();
}