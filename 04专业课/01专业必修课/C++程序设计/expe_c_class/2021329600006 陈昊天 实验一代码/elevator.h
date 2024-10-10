#include "head.h"

class Elevator {
   private:
    int floor;         //电梯总的楼层数
    int currentFloor;  //当前所在楼层
   public:
    Elevator();
    Elevator(int floor, int currentFloor);
    void showFloor();      //展示当前楼层
    void setUpButton();    //按下上行按钮
    void setDownButton();  //按下下行按钮
    void setFloorNumber(int floorNumber);
    //根据要进入的楼层电梯开始运行，并逐层显示经过的楼层
};

namespace UI {
string currentTime;
void showTime();                      // 展示当前日期
void Start(Elevator &ele);            // 开始UI
void selectOperation(Elevator &ele);  // 选择按钮
};                                    // namespace UI
