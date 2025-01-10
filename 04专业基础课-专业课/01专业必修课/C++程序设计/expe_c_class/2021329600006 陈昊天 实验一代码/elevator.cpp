#include "elevator.h"

#include "date.cpp"

using std::cin;
using std::swap;

Elevator::Elevator() {
    floor = 10;
    currentFloor = 1;
}

Elevator::Elevator(int nfloor, int cfloor) {
    floor = nfloor;
    currentFloor = cfloor;
}

void Elevator::showFloor() {
    cout << "当前楼层: " << currentFloor << endl;
    cout << "总楼层数: " << floor << endl;
}

void Elevator::setUpButton() {
    int ed;
    cout << "请输入目标楼层: " << endl;
    cin >> ed;
    if (ed <= currentFloor or ed > floor) {
        cout << "非法操作." << endl;
    } else {
        setFloorNumber(ed);
    }
}

void Elevator::setDownButton() {
    int ed;
    cout << "请输入目标楼层: " << endl;
    cin >> ed;
    if (ed >= currentFloor or ed < 1) {
        cout << "非法操作." << endl;
    } else {
        setFloorNumber(ed);
    }
}

void Elevator::setFloorNumber(int floorNumber) {
    int l = currentFloor, r = floorNumber;
    if (l < r) {
        for (int cfl = l; cfl <= r; cfl++) {
            // system("clear");  // linux / mac
            system("cls");  // windows
            cout << "- 电梯运行中 -" << endl;
            for (int i = floor; i >= 1; i--) {
                if (i == cfl)
                    cout << " |   []   |" << i << endl;
                else
                    cout << " |        |" << i << endl;
            }
            cout << endl;
            // sleep(1);  // linux / mac
            Sleep(1000);  // windows
        }
    } else {
        for (int cfl = l; cfl >= r; cfl--) {
            // system("clear");  // linux / mac
            system("cls");  // windows
            cout << "- 电梯运行中 -" << endl;
            for (int i = floor; i >= 1; i--) {
                if (i == cfl)
                    cout << " |   []   |" << i << endl;
                else
                    cout << " |        |" << i << endl;
            }
            cout << endl;
            // sleep(1);  // linux / mac
            Sleep(1000);  // windows
        }
    }
    currentFloor = floorNumber;
}

void UI::showTime() {
    CDate currentDate;
    currentTime = currentDate.format("ddd");
    cout << "当前日期: " << currentTime << endl;
}

void UI::selectOperation(Elevator &ele) {
    ele.showFloor();
    cout << "请选择操作(1.上行 2.下行 3.退出): " << endl;
    int op;
    cin >> op;
    if (op == 1) {
        ele.setUpButton();
        selectOperation(ele);
    } else if (op == 2) {
        ele.setDownButton();
        selectOperation(ele);
    } else {
        cout << "已退出系统, 欢迎下次使用." << endl;
        exit(0);
    }
}

void UI::Start(Elevator &ele) {
    // system("clear");  // linux / mac
    system("cls");  // windows
    showTime();
    selectOperation(ele);
}