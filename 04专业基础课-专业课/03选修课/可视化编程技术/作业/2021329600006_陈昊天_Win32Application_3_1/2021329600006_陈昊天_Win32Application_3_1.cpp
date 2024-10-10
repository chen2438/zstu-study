//注释 Ctrl K + Ctrl C
//取消注释 Ctrl K + Ctrl U
//格式化 Ctrl K + Ctrl D
#include "windows.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow) {
    HWND hwnd;
    MSG Msg;
    WNDCLASS wndclass;
    TCHAR lpszClassName[] = L"My_Drawing";
    TCHAR lpszTitle[] = L"2021329600006_陈昊天_Win32Application_3_1";
    wndclass.style = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = lpszClassName;
    if (!RegisterClass(&wndclass)) {
        MessageBeep(0);
        return FALSE;
    }
    hwnd = CreateWindow(lpszClassName, lpszTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM  wParam, LPARAM  lParam) {
    HDC hdc;    PAINTSTRUCT ps;
    HPEN hP;                        //定义画笔句柄
    HBRUSH hB;                      //定义画刷句柄
    switch (message) {
        case WM_PAINT:          //通过响应WM_PAINT消息完成绘图工作
            hdc = BeginPaint(hwnd, &ps);            //取得设备环境句柄
            SetMapMode(hdc, MM_TEXT);               //设置映射模式,使用像素操作

            {
                hB = CreateSolidBrush(RGB(255, 0, 0));//红色笔刷
                SelectObject(hdc, hB);
                Rectangle(hdc, 130, 60, 270, 200);   // 矩形
            }

            {
                hP = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));//绿色画笔
                SelectObject(hdc, hP);
                hB = CreateSolidBrush(RGB(0, 0, 255));//蓝色笔刷
                SelectObject(hdc, hB);
                Ellipse(hdc, 130, 70, 270, 190);    // 椭圆
            }

            {
                hP = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));//绿色画笔
                SelectObject(hdc, hP);
                hB = CreateSolidBrush(RGB(255, 0, 0));//红色笔刷
                SelectObject(hdc, hB);
                Pie(hdc, 130, 70, 270, 190, 200, 130, 130, 190);   // 绘制饼
            }

            EndPaint(hwnd, &ps);                //释放设备环境句柄
            DeleteObject(hP);
            DeleteObject(hB);       //删除画笔画刷句柄
            break;
        case WM_DESTROY:
            PostQuitMessage(0);     break;
        default:    return  DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

/*
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // 设置画笔和填充颜色
            HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));  // 红色画笔，线宽为2像素
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));  // 白色填充

            // 选择画笔和填充到设备环境
            HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
            HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

            // 绘制倒三角形
            POINT points[3] = { {50, 50}, {150, 50}, {100, 150} };  // 定义三个点坐标
            Polygon(hdc, points, 3);  // 绘制多边形

            // 恢复原来的画笔和填充
            //SelectObject(hdc, hOldPen);
            //SelectObject(hdc, hOldBrush);
            // 绘制圆形
            HBRUSH hCircleBrush = CreateSolidBrush(RGB(255, 255, 255));  // 绿色填充
            SelectObject(hdc, hCircleBrush);
            Ellipse(hdc, 50, 150, 150, 250);  // 绘制椭圆

            POINT points2[5] = { {100, 250}, {150, 300}, {150, 350},{50,350},{50,300} };  // 定义5个点坐标
            Polygon(hdc, points2, 5);  // 绘制多边形

            // 绘制圆角矩形
            HPEN hRectPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));  // 红色画笔，线宽为2像素
            SelectObject(hdc, hRectPen);
            HBRUSH hRectBrush = CreateSolidBrush(RGB(0, 0, 0));  // 黑色填充
            RECT rect = { 220, 50, 320, 150 };  // 定义矩形区域
            int radius = 20;  // 定义圆角半径
            RoundRect(hdc, rect.left, rect.top, rect.right, rect.bottom, radius, radius);  // 绘制圆角矩形

            // 恢复原来的填充
            SelectObject(hdc, hOldBrush);
            DeleteObject(hCircleBrush);

            // 删除画笔和填充
            DeleteObject(hPen);
            DeleteObject(hBrush);

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
*/