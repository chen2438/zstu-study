#include <windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);
// InitWindowsClass()和InitWindows()函数体略，详见网络学堂代码 
// 主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    MSG Message;
    if (!InitWindowsClass(hInstance)) return FALSE;
    if (!InitWindows(hInstance, nCmdShow)) return FALSE;
    while (GetMessage(&Message, 0, 0, 0)) {  // 消息循环
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}
BOOL InitWindowsClass(HINSTANCE hInstance) {  // 初始化窗口类
    WNDCLASS wndclass;                        // 窗口类
    TCHAR lpszClassName[] = L"My_Drawing";
    TCHAR lpszTitle[] = L"2021329600006_陈昊天_Win32Application_4_1";
    wndclass.style = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;  // 应用程序实例句柄
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = lpszClassName;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    return RegisterClass(&wndclass);
}
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow) {  // 初始化窗口
    HWND hwnd;
    TCHAR lpszClassName[] = L"My_Drawing";
    TCHAR lpszTitle[] = L"2021329600006_陈昊天_Win32Application_4_1";
    hwnd =
        CreateWindow(lpszClassName, lpszTitle,  // 创建窗口
                     WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                     CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);  // 显示窗口
    UpdateWindow(hwnd);          // 刷新窗口
    return TRUE;
}
static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
                                LPARAM lParam) {
    static long nXChar, nCaps, nYChar;
    int pointx, pointy, i, j;
    HDC hDC;            // 定义指向设备环境的句柄
    TEXTMETRIC tm;      // 存放字体各种属性的结构体变量
    PAINTSTRUCT PtStr;  // 指向包含绘图信息的结构体变量
    LPCWSTR textbuf[4] = {{L"故人西辞黄鹤楼"},
                          {L"烟花三月下扬州"},
                          {L"孤帆远影碧空尽"},
                          {L"唯见长江天际流"}};
    // LPCWSTR textbuf[4] = { L"故人西辞黄鹤楼", L"烟花三月下扬州",
    //                       L"孤帆远影碧空尽", L"唯见长江天际流" };
    switch (iMessage) {  // 处理消息

        case WM_CREATE:                  // 处理窗口创建消息
            hDC = GetDC(hWnd);           // 获取当前设备表句柄
            GetTextMetrics(hDC, &tm);    // 获取字体信息
            nXChar = tm.tmAveCharWidth;  // 获取字符宽度
            nYChar = tm.tmHeight + tm.tmExternalLeading;  // 字符高度
            nCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * nXChar / 2;  // 字间距
            ReleaseDC(hWnd, hDC);  // 释放当前设备句柄
            return 0;
        case WM_PAINT:                       // 处理重画消息
            hDC = BeginPaint(hWnd, &PtStr);  // 开始绘图
            for (i = 4; i >= 1; i--) {
                for (j = 0; j <= 6; j++) {  // 输出文本
                    // 100,50
                    pointx = 700 + i * nXChar * 5;
                    pointy = 50 + j * (nYChar + nCaps);
                    TextOut(hDC, pointx, pointy, textbuf[4 - i] + j, 1);
                }
            }
            EndPaint(hWnd, &PtStr);
            return 0;     // 结束绘图
        case WM_DESTROY:  // 结束应用程序
            PostQuitMessage(0);
            return 0;
        default:
            return (DefWindowProc(hWnd, iMessage, wParam, lParam));
    }
}