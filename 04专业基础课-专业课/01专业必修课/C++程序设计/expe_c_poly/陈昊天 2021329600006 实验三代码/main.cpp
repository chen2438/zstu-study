#include "stu.cpp"

Report report;

void init() {
    const int MAXN = 12;
    Student *stu[MAXN];
    stu[0] = new CStudent("1001", "c1", "男", 20, "CStudent", 80, 65, 97);
    stu[1] = new CStudent("1002", "c2", "男", 21, "CStudent", 88, 72, 86);
    stu[2] = new FStudent("1003", "f1", "男", 18, "FStudent", 70, 87, 95);
    stu[3] = new FStudent("1004", "f2", "女", 19, "FStudent", 85, 93, 95);
    stu[4] = new CStudent("1005", "c3", "女", 20, "CStudent", 85, 90, 88);
    stu[5] = new CStudent("1006", "c4", "女", 21, "CStudent", 60, 93, 75);
    stu[6] = new FStudent("1007", "f3", "男", 20, "FStudent", 62, 85, 97);
    stu[7] = new FStudent("1008", "f4", "女", 19, "FStudent", 88, 72, 66);
    stu[8] = new GStudent("1009", "g1", "女", 20, "GStudent", 82, 60, 78);
    stu[9] = new GStudent("1010", "g2", "女", 21, "GStudent", 70, 83, 65);
    stu[10] = new GStudent("1011", "g3", "男", 20, "GStudent", 72, 65, 87);
    stu[11] = new GStudent("1012", "g4", "男", 19, "GStudent", 98, 62, 96);
    for (int i = 0; i < MAXN; i++) {
        report.insert(stu[i]);
    }
}

int main() {
    init();
    echo("1: 输入学号, 删除相应记录");
    echo("2: 删除所有学生的记录");
    echo("3: 分类别显示所有学生绩点记录表");
    echo("4: 输入类别, 显示该类别学生绩点记录表");
    echo("5: 插入记录");
    echo("6: 统计报表");
    echo("7: 存储成绩到文件");
    echo("-1: 退出");
    int cmd;
    while (cin >> cmd) {
        if (cmd == 1) {  // 输入学号, 删除相应记录
            string number;
            echo("请输入学号: ");
            cin >> number;
            if (report.del(number)) {
                echo("删除成功");
            } else {
                echo("学号不存在, 删除失败");
            }
        } else if (cmd == 2) {  // 删除所有学生的记录
            report.stu_list.clear();
            echo("删除成功！");
        } else if (cmd == 3) {  // 分类别显示所有学生绩点记录表
            report.print(report.stu_list);
        } else if (cmd == 4) {  // 输入类别, 显示该类别学生绩点记录表
            echo("请输入类别: ");
            string type;
            cin >> type;
            vector<Student *> slist = report[type];
            report.print(slist);
        } else if (cmd == 5) {  // 插入记录
            string number, name, gender, type;
            int age, s1, s2, s3;
            echo("请输入学号\t姓名\t性别\t年龄\t类别\t三项成绩, 以空格间隔");
            cin >> number >> name >> gender >> age >> type >> s1 >> s2 >> s3;
            Student *stu;
            if (type == "CStudent") {
                stu = new CStudent(number, name, gender, age, type, s1, s2, s3);
            } else if (type == "FStudent") {
                stu = new FStudent(number, name, gender, age, type, s1, s2, s3);
            } else if (type == "GStudent") {
                stu = new GStudent(number, name, gender, age, type, s1, s2, s3);
            }
            report.insert(stu);
        } else if (cmd == 6) {  // 统计报表
            report.stats();
        } else if (cmd == 7) {  // 存储
            report.save();
            echo("信息已存储到 \"stuInfo.txt\" .");
        } else if (cmd == -1) {
            echo("已退出系统, 欢迎下次使用.");
            exit(0);
        }
        echo("任务完成, 请输入下一个指令:");
    }
    return 0;
}