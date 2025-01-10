#include "elevator.h"

#include "date.cpp"

Elevator::Elevator() {
    floor = 10;
    currentFloor = 1;
}

Elevator::Elevator(int nfloor, int cfloor) {
    floor = nfloor;
    currentFloor = cfloor;
}

adElevator::adElevator() {
    Elevator();
    maxLoad = 800;
}

adElevator::adElevator(int floor, int currentFloor, int nmaxLoad)
    : Elevator(floor, currentFloor) {
    maxLoad = nmaxLoad;
}

void Elevator::showFloor() {
    cout << "当前楼层: " << currentFloor << endl;
    cout << "总楼层数: " << floor << endl;
}

void adElevator::showFloor() {
    cout << "当前楼层: " << currentFloor << endl;
    cout << "总楼层数: " << floor << endl;
    cout << "最大载荷(kg): " << maxLoad << endl;
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
        for (int cfl = l; cfl < r; cfl++) {
            UI::cls();
            cout << "- 电梯运行中 -" << endl;
            for (int i = floor; i >= 1; i--) {
                if (i == cfl)
                    cout << " |   []   |" << i << endl;
                else
                    cout << " |        |" << i << endl;
            }
            cout << endl;
            UI::slp();
        }
    } else {
        for (int cfl = l; cfl > r; cfl--) {
            UI::cls();
            cout << "- 电梯运行中 -" << endl;
            for (int i = floor; i >= 1; i--) {
                if (i == cfl)
                    cout << " |   []   |" << i << endl;
                else
                    cout << " |        |" << i << endl;
            }
            cout << endl;
            UI::slp();
        }
    }
    currentFloor = floorNumber;
}

void adElevator::adShowPassenger(int currentFloor) {
    for (auto i : passenger[currentFloor]) {
        if (i.action == "in") {
            if (currentLoad + i.weight > maxLoad) {
                cout << "已超载, 拒绝编号为" << i.id << "的乘客进入!" << endl;
                rejectID[i.id] = 1;

            } else {
                cout << "在第" << currentFloor << "层接编号为" << i.id
                     << "的乘客" << endl;
                currentLoad += i.weight;
            }
        } else if (i.action == "out") {
            if (rejectID[i.id] == 1) {
                rejectID[i.id] = 0;
            } else {
                cout << "在第" << currentFloor << "层送编号为" << i.id
                     << "的乘客" << endl;
                currentLoad -= i.weight;
            }
        }
        cout << endl;
        UI::fslp();
    }
    passenger[currentFloor].clear();
}

void adElevator::adSetFloorNumber(int minFloor, int maxFloor, string action) {
    int l = minFloor, r = maxFloor;
    if (action == "down") swap(l, r);
    setFloorNumber(l);
    if (l < r) {
        for (int cfl = l; cfl <= r; cfl++) {
            UI::cls();
            cout << "- 电梯运行中 -" << endl;
            for (int i = floor; i >= 1; i--) {
                if (i == cfl)
                    cout << " |   []   |" << i << endl;
                else
                    cout << " |        |" << i << endl;
            }
            cout << endl;
            adShowPassenger(cfl);
            UI::slp();
        }
        currentFloor = maxFloor;
    } else {
        for (int cfl = l; cfl >= r; cfl--) {
            UI::cls();
            cout << "- 电梯运行中 -" << endl;
            for (int i = floor; i >= 1; i--) {
                if (i == cfl)
                    cout << " |   []   |" << i << endl;
                else
                    cout << " |        |" << i << endl;
            }
            cout << endl;
            adShowPassenger(cfl);
            UI::slp();
        }
        currentFloor = minFloor;
    }
}
#ifdef windows
void UI::cls() { system("cls"); }
void UI::slp() { Sleep(1000); }
void UI::fslp() { Sleep(500); }
#endif

#ifndef windows
void UI::cls() { system("clear"); }
void UI::slp() { sleep(1); }
void UI::fslp() { usleep(500000); }  //单位微秒
#endif

void UI::showTime() {
    CDate currentDate;
    currentTime = currentDate.format("ddd");
    cout << "当前日期: " << currentTime << endl;
}

void UI::selectOperation(adElevator &ele) {
    ele.showFloor();
    cout << "请选择操作(1.上行 2.下行 3.退出): " << endl;
    int op;
    cin >> op;
    if (op == 3) {
        cout << "已退出系统, 欢迎下次使用." << endl;
        exit(0);
    }
    cout << "请输入乘坐电梯的人数" << endl;
    int sum, minFloor = INT32_MAX, maxFloor = 0, legal = 1;
    cin >> sum;
    for (int i = 1; i <= sum; i++) {
        int st, ed, weight;
        cout << "请输入第" << i << "位乘客的楼层起点" << endl;
        cin >> st;
        cout << "请输入第" << i << "位乘客的楼层终点" << endl;
        cin >> ed;
        cout << "请输入第" << i << "位乘客的体重" << endl;
        cin >> weight;
        if (op == 1) {
            if (st > ed or st < 1 or ed > 10) {
                cout << "非法操作." << endl;
                legal = 0;
                break;
            }
        } else {
            if (st < ed or st > 10 or st < 1) {
                cout << "非法操作." << endl;
                legal = 0;
                break;
            }
        }
        ele.passenger[st].push_back({i, "in", weight});
        ele.passenger[ed].push_back({i, "out", weight});
        minFloor = min({minFloor, st, ed});
        maxFloor = max({maxFloor, st, ed});
    }

    if (!legal) {
        selectOperation(ele);
    } else if (op == 1) {
        ele.adSetFloorNumber(minFloor, maxFloor, "up");
        selectOperation(ele);
    } else if (op == 2) {
        ele.adSetFloorNumber(minFloor, maxFloor, "down");
        selectOperation(ele);
    }
}

void UI::Start(adElevator &ele) {
    cls();
    showTime();
    selectOperation(ele);
}
