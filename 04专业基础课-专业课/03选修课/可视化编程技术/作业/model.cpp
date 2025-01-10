#include <tchar.h>
#include <windows.h>
// wcslen(LPCWSTR)
//
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);

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
    int pointx, pointy;
    HDC hdc;            // 定义指向设备环境的句柄
    TEXTMETRIC tm;      // 存放字体各种属性的结构体变量
    PAINTSTRUCT PtStr;  // 指向包含绘图信息的结构体变量
    static RECT rect = {0, 300, 0, 350};
    SIZE size;                               // 定义一个SIZE类型的结构
    switch (iMessage) {                      // 处理消息
        case WM_CREATE:                      // 处理窗口创建消息
            SetTimer(hWnd, 9999, 50, NULL);  // 设置定时器 50ms
            hdc = GetDC(hWnd);               // 获取当前设备表句柄

            ReleaseDC(hWnd, hdc);  // 释放当前设备句柄
            break;
        case WM_TIMER:
            if (wParam == 9999)                    // 定时刷新
                InvalidateRect(hWnd, NULL, true);  // 使hWnd失效以便重新绘制
            break;
        case WM_PAINT:                       // 处理重画消息
            hdc = BeginPaint(hWnd, &PtStr);  // 开始绘图
            //...
            EndPaint(hWnd, &ps);
            DeleteObject(hF_black);  // 删除自定义字体句柄
            DeleteObject(hF_big);
            break;
        case WM_DESTROY:  // 结束应用程序
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, iMessage, wParam, lParam));
    }
}