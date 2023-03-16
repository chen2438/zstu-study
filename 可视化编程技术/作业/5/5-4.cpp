#include <tchar.h>
#include <windows.h>

BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HFONT CreateFont(HDC hDC, int nCharHeight, BOOL bItalic);

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

static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
                                LPARAM lParam) {
    HDC hDC;                        // 设备环境句柄
    HFONT hF;                       // 字体句柄
    PAINTSTRUCT ps;                 // 包含绘图信息的结构体变量
    TEXTMETRIC tm;                  // 包含字体信息的结构体变量
    TCHAR str[] = L" Hello VC   ";  // 输出的字符串
    int i = 0;
    static int x[11], y[11], color[11];
    POINT pt;

    switch (iMessage) {
        case WM_CREATE:
            SetTimer(hWnd, 1000, 200, NULL);  // 每隔毫秒发送一个WM_TIMER的消息
            GetCursorPos(&pt);                // 获取当前光标的位置
            ScreenToClient(hWnd, &pt);  // 将屏幕坐标转换为窗口坐标
            for (i = 0; i < 11; i++) {  // 初始化表示位置的数组和颜色
                x[i] = pt.x + (i - 1) * 40;
                y[i] = pt.y;
                color[i] = 25 * (i - 1);
            }
            break;
        case WM_PAINT:                    // 处理绘图消息
            hDC = BeginPaint(hWnd, &ps);  // 获得设备环境指针
            hF = CreateFont(hDC, 40, 0);  // 创建字体
            SelectObject(hDC, hF);        // 选入字体
            for (i = 10; i > 1; i--) {  // 后一个字的位置调整到前一个字的位置
                x[i] = x[i - 1] + 40;
                y[i] = y[i - 1];
            }
            GetCursorPos(&pt);
            ScreenToClient(hWnd, &pt);
            x[1] = pt.x;
            y[1] =
                pt.y;  // 第一个字位置是当前鼠标的位置，后续字符就会跟随鼠标不断移动
            for (i = 1; i < 11; i++) {
                SetTextColor(
                    hDC, RGB(255 - color[i], color[i], 255));  // 设置字体颜色
                TextOut(hDC, x[i], y[i], &str[i],
                        1);  // 输出从第个到第nChar个字符
            }
            color[1] = color[10];
            for (i = 10; i > 1; i--)  // 调整颜色，使颜色不断循环变化
                color[i] = color[i - 1];
            DeleteObject(hF);     // 删除字体句柄
            EndPaint(hWnd, &ps);  // 删除设备用户指针
            break;
        case WM_TIMER:  // 处理由标识为的计时器发出的消息
            if (wParam == 1000) InvalidateRect(hWnd, NULL, 1);  // 刷新用户区
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, iMessage, wParam, lParam);
            break;
    }
    return 0;
}

HFONT CreateFont(HDC hDC, int nCharHeight, BOOL bItalic) {
    HFONT hFont;
    hFont = CreateFont(  // 定义字体句柄
        nCharHeight,     // 字体高度
        0,               // 系统根据高宽比选取字体最佳宽度值
        0, 0,            // 文本倾斜度，表示水平 //字体倾斜度为0
        400,             // 字体粗度，为正常
        bItalic,         // 是斜体字
        0, 0,            // 无下划线，//无删除线
        ANSI_CHARSET,    // ANSI_CHARSET字符集
        OUT_DEFAULT_PRECIS,           // 删除精度为默认值
        CLIP_DEFAULT_PRECIS,          // 裁剪精度为默认值
        DEFAULT_QUALITY,              // 输出质量为默认值
        DEFAULT_PITCH | FF_DONTCARE,  // 字间距
        L"Arial");                    // 字体名称
    if (hFont == NULL)
        return NULL;
    else
        return hFont;
}
