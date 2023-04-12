#include <windows.h>
#include <tchar.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);

// 主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    MSG Message;
    if (!InitWindowClass(hInstance, nCmdShow)) {
        MessageBox(NULL, L"创建窗口失败", L"创建窗口", NULL);
        return 1;
    }
    while (GetMessage(&Message, 0, 0, 0)) {  // 消息循环
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) {
    HWND hwnd;
    WNDCLASSEX wcex;                        // 窗口类
    TCHAR szWindowClass[] = L"Bitmap";
    TCHAR szTitle[] = L"2021329600006_陈昊天_实验1";
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = 0;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;  // 应用程序实例句柄
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = L"Menu";
    wcex.lpszClassName = szWindowClass;

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, L"注册窗口失败", L"注册窗口", NULL);
        return FALSE;
    }
    hwnd = CreateWindow(szWindowClass, szTitle,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0,
        800, 600, NULL, NULL, hInstance, NULL);
    if (!hwnd) {
        MessageBox(NULL, L"创建窗口失败", L"创建窗口", NULL);
        return FALSE;
    }
    ShowWindow(hwnd, nCmdShow);  // 显示窗口
    UpdateWindow(hwnd);          // 刷新窗口
    return TRUE;
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
    LPARAM lParam) {
    static long nXChar, nCaps, nYChar;
    int pointx, pointy;
    HDC hdc;            // 定义指向设备环境的句柄
    TEXTMETRIC tm;      // 存放字体各种属性的结构体变量
    PAINTSTRUCT PtStr;  // 指向包含绘图信息的结构体变量
    LPCWSTR textbuf[4] = { {L"故人西辞黄鹤楼"},
                          {L"烟花三月下扬州"},
                          {L"孤帆远影碧空尽"},
                          {L"唯见长江天际流"} };

    HFONT hF_black, hF_big;  // 定义两种字体句柄
    PAINTSTRUCT ps;
    //TEXTMETRIC tm;  // 定义一个TEXTMETRIC结构，用以记录字体信息
    int X = 0, Y = 0;
    static RECT rect = { 0, 300, 0, 350 };
    SIZE size;  // 定义一个SIZE类型的结构
    switch (iMessage) {  // 处理消息

        case WM_CREATE:                  // 处理窗口创建消息
            //SetTimer(hWnd, 9999, 50, NULL);  // 设置定时器 50ms
            hdc = GetDC(hWnd);           // 获取当前设备表句柄
            GetTextMetrics(hdc, &tm);    // 获取字体信息
            nXChar = tm.tmAveCharWidth;  // 获取字符宽度
            nYChar = tm.tmHeight + tm.tmExternalLeading;  // 字符高度
            nCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * nXChar / 2;  // 字间距
            ReleaseDC(hWnd, hdc);  // 释放当前设备句柄
            break;
        case WM_TIMER:
            if (wParam == 9999)                    // 定时刷新
                InvalidateRect(hWnd, NULL, true);  // 使hWnd失效以便重新绘制
            break;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);
            HPEN hPen = (HPEN)GetStockObject(NULL_PEN); //获取系统定义的空画笔
            SelectObject(hDC, hPen);    	//选择画笔
            HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH); //获取系统定义的画刷
            SelectObject(hDC, hBrush);  	//选择画刷
            LineTo(hDC, 50, 50);  		//画线
            DeleteObject(hPen); 		//删除画笔
            hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); //创建画笔
            SelectObject(hDC, hPen);  	//选择画笔
            //画一个三角形
            LineTo(hDC, 150, 50);
            LineTo(hDC, 100, 137);
            LineTo(hDC, 50, 50);
            //定义一个POINT数组，包括6个点
            POINT points[6] = { {100,212},{70,227},{70,250},{130,250},{130,227},{100,212} };
            Polyline(hDC, points, 6); //五边形
            Arc(hDC, 63, 137, 138, 212, 100, 137, 100, 137);//圆
            Pie(hDC, 213, 137, 288, 212, 240, 137, 260, 137);//圆饼
            Rectangle(hDC, 213, 212, 287, 250);//长方形
            RoundRect(hDC, 213, 100, 287, 137, 20, 20);//圆角长方形
            DeleteObject(hPen);    //删除画笔
            DeleteObject(hBrush);  //删除画刷
            static long nXChar, nCaps, nYChar;
            int pointx, pointy;
            int i, j;
            static LPCWSTR textbuf[4] = { {L"故人西辞黄鹤楼"},
                                            {L"烟花三月下扬州"},
                                            {L"孤帆远影碧空尽"},
                                            {L"唯见长江天际流"} };
            TEXTMETRIC tm;
            GetTextMetrics(hDC, &tm); 			//获取字体信息
            nXChar = tm.tmAveCharWidth;  			//获取字符宽度
            nYChar = tm.tmHeight + tm.tmExternalLeading;	//字符高度
            nCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * nXChar / 2;	//字间距

            for (i = 4; i > 0; i--) {
                for (j = 0; j < 7; j++) {				//输出文本
                    pointx = 300 + i * nXChar * 5;
                    pointy = 50 + j * (nYChar + nCaps);
                    TextOut(hDC, pointx, pointy, textbuf[4 - i] + j * 1, 1);
                }
            }
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_DESTROY:  // 结束应用程序
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, iMessage, wParam, lParam));
    }
}