#pragma once
#pragma optimize(2)

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::ofstream;
using std::ostream;
using std::pair;
using std::string;
using std::vector;

class Student {  // 学生基类
   public:
    Student(){};
    Student(string number, string name, string gender, int age, string type);
    virtual double get_point() = 0;  // 计算绩点
    friend ostream &operator<<(ostream &out, const Student &stu);
    string number_;
    string name_;
    string gender_;
    int age_;
    string type_;
};

class CStudent : public Student {  // 本科生类
   public:
    CStudent() {}
    CStudent(string number, string name, string gender, int age, string type,
             double english, double math, double computer);
    double get_point();
    double english_;
    double math_;
    double computer_;
};

class FStudent : public Student {  // 留学生类
   public:
    FStudent() {}
    FStudent(string number, string name, string gender, int age, string type,
             double chinese, double math, double computer);
    double get_point();
    double chinese_;
    double math_;
    double computer_;
};

class GStudent : public Student {  // 研究生类
   public:
    GStudent() {}
    GStudent(string number, string name, string gender, int age, string type,
             double philosophy, double math, double computer);
    double get_point();
    double philosophy_;
    double math_;
    double computer_;
};

// 报表类
class Report {
   public:
    Report() {}
    void insert(Student *stu);            // 插入信息
    void stats();                         // 统计报表
    void save();                          // 存储成绩
    int del(string number);               // 根据学号删除
    void print(vector<Student *> slist);  // 显示学生信息
    vector<Student *> operator[](
        string type);            // 重载[]查找所有number类别的学生
    vector<Student *> stu_list;  // 保存学生信息
};
