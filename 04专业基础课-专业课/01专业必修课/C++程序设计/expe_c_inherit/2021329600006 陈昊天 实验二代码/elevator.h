#include "head.h"

class Elevator {
   protected:
    int floor;         //电梯总的楼层数
    int currentFloor;  //当前所在楼层
   public:
    Elevator();
    Elevator(int floor, int currentFloor);
    void showFloor();      //展示楼层信息
    void setUpButton();    //按下上行按钮
    void setDownButton();  //按下下行按钮
    void setFloorNumber(int floorNumber);
    //根据要进入的楼层电梯开始运行，并逐层显示经过的楼层
};

class Passenger {
   public:
    int id;         //乘客编号
    string action;  //乘客动作(in/out)
    int weight;     //乘客体重
};

class adElevator : public Elevator {
   private:
    int maxLoad;             //载荷
    int currentLoad;         //当前载重
    map<int, int> rejectID;  //因超载而无法进入的乘客
   public:
    adElevator();
    adElevator(int floor, int currentFloor, int maxLoad);
    void showFloor();  //展示楼层信息
    void adSetFloorNumber(int minFloor, int maxFloor, string action);
    //根据要进入的楼层电梯开始运行，并逐层显示经过的楼层
    map<int, vector<Passenger>> passenger;   //乘客信息
    void adShowPassenger(int currentFloor);  //显示乘客进出信息
};

namespace UI {
    string currentTime;
    void showTime();                        // 展示当前日期
    void Start(adElevator &ele);            // 开始UI
    void selectOperation(adElevator &ele);  // 选择按钮
    void cls();                             // 清屏
    void slp();                             // sleep
    void fslp();                            // fast sleep
};                                          // namespace UI
