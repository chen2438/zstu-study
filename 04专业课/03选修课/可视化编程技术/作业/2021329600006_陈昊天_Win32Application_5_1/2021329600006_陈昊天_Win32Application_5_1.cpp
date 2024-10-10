#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);
HWND hWndMain;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    MSG Message;
    if (!InitWindowsClass(hInstance)) return FALSE;
    if (!InitWindows(hInstance, nCmdShow)) return FALSE;
    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}

LRESULT WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
    HDC hDC;         // 定义设备环境句柄
    PAINTSTRUCT ps;  // 定义包含绘图信息的结构体变量
    HPEN hPen;       // 定义画笔句柄
    HBRUSH hBrush;   // 定义画刷句柄
    LPCWSTR cUp = L"You had pressed the UP key";
    LPCWSTR cCtrl = L"You had pressed the Ctrl key";
    LPCWSTR cShift = L"You had pressed the SHIFT key";
    LPCWSTR cCtrl_A = L"You had pressed the CTRL A key";
    LPCWSTR cShift_B = L"You had pressed the SHIFT B key";
    static BOOL nUpKeyDown = FALSE, nShiftKeyDown = FALSE, nCtrlKeyDown = FALSE;
    static BOOL nCtrlAKeyDown = FALSE, nShiftBKeyDown = FALSE;
    switch (iMessage) {
        case WM_KEYDOWN: {
            switch (wParam) {
                case VK_UP:  // 当按上箭头键时，变量置为真
                    nUpKeyDown = TRUE;
                    break;
                case VK_SHIFT:  // 当按shift键时，变量置为真
                    nShiftKeyDown = TRUE;
                    nShiftBKeyDown = FALSE;
                    break;
                case VK_CONTROL:  // 当按control键时，变量置为真
                    nCtrlKeyDown = TRUE;
                    nCtrlAKeyDown = FALSE;
                    break;
                default:
                    break;
            }
        } break;
        case WM_KEYUP:
            InvalidateRect(hWnd, NULL, FALSE);  // 刷新用户区
            break;
        case WM_CHAR:
            if (wParam == 1) {
                if (nCtrlKeyDown == TRUE) {
                    nCtrlAKeyDown = TRUE;
                    nCtrlKeyDown = FALSE;
                }
            } else if (wParam == 98 || wParam == 66) {  // 当按下b键时
                if (nShiftKeyDown == TRUE) {  // 检查shift键是否处于按下状态
                    nShiftBKeyDown = TRUE;  // 当SHIFT键按下时，变量置为真
                    nShiftKeyDown = FALSE;
                }
            } else
                ;
            break;
        case WM_PAINT:  // 处理绘图消息
            hDC = BeginPaint(hWnd, &ps);
            hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
            hPen = (HPEN)GetStockObject(WHITE_PEN);
            SelectObject(hDC, hPen);
            SelectObject(hDC, hBrush);
            SetTextColor(hDC, RGB(255, 0, 0));  // 设置字体颜色为红色
            if (nUpKeyDown == TRUE) {           // 输出信息。

                Rectangle(hDC, 0, 0, 300, 200);
                TextOut(hDC, 0, 0, cUp, wcslen(cUp));
                nUpKeyDown = FALSE;
            } else if (nCtrlAKeyDown == TRUE) {
                Rectangle(hDC, 0, 0, 300, 200);
                TextOut(hDC, 0, 100, cCtrl_A, wcslen(cCtrl_A));
                nCtrlAKeyDown = FALSE;
                nCtrlKeyDown = FALSE;
            } else if ((nCtrlKeyDown == TRUE) && (nCtrlAKeyDown == FALSE)) {
                Rectangle(hDC, 0, 0, 300, 200);
                TextOut(hDC, 0, 60, cCtrl, wcslen(cCtrl));
                nCtrlKeyDown = FALSE;
            } else if (nShiftBKeyDown == TRUE) {
                Rectangle(hDC, 0, 0, 300, 200);
                TextOut(hDC, 0, 0, cShift_B, wcslen(cShift_B));
                nShiftBKeyDown = FALSE;
                nShiftKeyDown = FALSE;
            } else if ((nShiftKeyDown == TRUE) && (nShiftBKeyDown == FALSE)) {
                Rectangle(hDC, 0, 0, 300, 200);
                TextOut(hDC, 0, 0, cShift, wcslen(cShift));
                nShiftKeyDown = FALSE;
            } else
                ;
            DeleteObject(hPen);  // 删除画笔和画刷
            DeleteObject(hBrush);
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
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