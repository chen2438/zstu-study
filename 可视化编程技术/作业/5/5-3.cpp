#include <windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitWindowsClass(HINSTANCE hInstance);  // 初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);
HWND hWndMain;  // 定义全局窗口句柄
RECT rect1;     // 定义矩形结构体.记录了图形的信息
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    MSG Message;
    if (!InitWindowsClass(hInstance))  // 初始化窗口类
        return FALSE;
    if (!InitWindows(hInstance, nCmdShow))  // 初始化窗口
        return FALSE;
    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);  // 消息循环
        DispatchMessage(&Message);
    }
    return Message.wParam;
}
static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
                                LPARAM lParam) {
    HDC hDC;                                     // 定义设备环境句柄
    int x, y;                                    // 定义鼠标的位置坐标
    static BOOL bCircle = FALSE, bRect = FALSE;  // 绘制圆和矩形的标志
    PAINTSTRUCT ps;                              // 定义绘图结构体变量
    x = LOWORD(lParam);                          // 得到鼠标的位置
    y = HIWORD(lParam);
    switch (iMessage) {
        case WM_MOUSEMOVE:    // 处理鼠标移动信息
            rect1.right = x;  // 图形的右下角坐标为当前鼠标位置
            rect1.bottom = y;
            if (bCircle == TRUE || bRect == TRUE)
                InvalidateRect(hWnd, NULL, TRUE);  // 发出重绘信息
            break;
        case WM_LBUTTONDOWN:          // 处理按下鼠标左键消息
            if (wParam & MK_CONTROL)  // 同时按下Ctrl键时
            {
                bCircle = TRUE;  // 画圆
                bRect = FALSE;
                rect1.left = x;  // 圆的左上角坐标为当前鼠标位置
                rect1.top = y;
            } else if (wParam & MK_SHIFT)  // 同时按下shift键时
            {
                bRect = TRUE;  // 画矩形
                bCircle = FALSE;
                rect1.left = x;  // 矩形的左上角坐标为当前鼠标位置
                rect1.top = y;
            } else {
                bCircle = FALSE;
                bRect = FALSE;
            }
            break;
        case WM_LBUTTONUP:  // 当松开左键时.绘图标志为false
            bRect = FALSE;
            bCircle = FALSE;
            break;
        case WM_PAINT:
            hDC = BeginPaint(hWnd, &ps);
            if (bCircle == TRUE)  // 绘制圆形
                Ellipse(hDC, rect1.left, rect1.top, rect1.right, rect1.bottom);
            if (bRect == TRUE)  // 绘制矩形
                Rectangle(hDC, rect1.left, rect1.top, rect1.right,
                          rect1.bottom);
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:  // 处理退出窗口信息
            PostQuitMessage(0);
            return 0;
        default:
            return (DefWindowProc(hWnd, iMessage, wParam, lParam));
    }
    return 0;
}

BOOL InitWindowsClass(HINSTANCE hInstance) {  // 初始化窗口类
    WNDCLASS wndclass;                        // 窗口类
    TCHAR lpszClassName[] = L"My_Drawing";
    TCHAR lpszTitle[] = L"2021329600006_陈昊天_Win32Application_5_1";
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
    TCHAR lpszTitle[] = L"2021329600006_陈昊天_Win32Application_5_1";
    hwnd =
        CreateWindow(lpszClassName, lpszTitle,  // 创建窗口
                     WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                     CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);  // 显示窗口
    UpdateWindow(hwnd);          // 刷新窗口
    return TRUE;
}