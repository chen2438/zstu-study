// 注释 Ctrl K + Ctrl C
// 取消注释 Ctrl K + Ctrl U
// 格式化 Ctrl K + Ctrl D
#include "windows.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine,
                   int nCmdShow) {
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
    hwnd = CreateWindow(lpszClassName, lpszTitle, WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    HPEN hP;    // 定义画笔句柄
    HBRUSH hB;  // 定义画刷句柄
    switch (message) {
        case WM_PAINT:  // 通过响应WM_PAINT消息完成绘图工作
            hdc = BeginPaint(hwnd, &ps);  // 取得设备环境句柄
            SetMapMode(hdc, MM_TEXT);  // 设置映射模式,使用像素操作

            {
                hB = CreateSolidBrush(RGB(255, 0, 0));  // 红色笔刷
                SelectObject(hdc, hB);
                // SetBkColor(hdc, RGB(255, 0, 0));      // 将背景颜色设置为红色
                Rectangle(hdc, 130, 60, 270, 200);  // 矩形
            }

            {
                hP = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));  // 绿色画笔
                SelectObject(hdc, hP);
                // hB = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0)); //红色网格
                // SelectObject(hdc, hB);
                hB = CreateSolidBrush(RGB(0, 0, 255));  // 蓝色笔刷
                SelectObject(hdc, hB);
                // SetBkColor(hdc, RGB(0, 0, 255));      // 背景红色
                Ellipse(hdc, 130, 70, 270, 190);  // 椭圆
            }

            // hP = CreatePen(PS_DASHDOT, 1, RGB(0, 255,
            // 0));//宽度为1的绿色画笔，画点划线 SelectObject(hdc, hP);
            // //更新画刷 MoveToEx(hdc, 100, 130, NULL); LineTo(hdc, 300,
            // 130);//用当前画笔绘制轴线 MoveToEx(hdc, 200, 30, NULL);
            // LineTo(hdc, 200, 230);

            {
                hP = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));  // 绿色画笔
                SelectObject(hdc, hP);
                hB = CreateSolidBrush(RGB(255, 0, 0));  // 红色笔刷
                SelectObject(hdc, hB);
                Pie(hdc, 130, 70, 270, 190, 200, 130, 130, 190);  // 绘制饼
            }

            EndPaint(hwnd, &ps);  // 释放设备环境句柄
            DeleteObject(hP);
            DeleteObject(hB);  // 删除画笔画刷句柄
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}