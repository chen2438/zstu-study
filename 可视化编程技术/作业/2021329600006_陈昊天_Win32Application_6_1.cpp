#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);

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
    TCHAR lpszTitle[] = L"2021329600006_陈昊天_Win32Application_6_1";
    //SetCursor(LoadCursorFromFile(L"1.cur")); // 将光标设置为新的光标
    hwnd =
        CreateWindow(lpszClassName, lpszTitle,  // 创建窗口
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);  // 显示窗口
    UpdateWindow(hwnd);          // 刷新窗口
    return TRUE;
}

// 消息处理函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam,
    LPARAM lParam) {
    static BOOL operate = FALSE, ready = TRUE;
    static POINT BeginP, EndP;
    static RECT rect = { 0, 0, 0, 0 };
    HDC hdc;
    PAINTSTRUCT PtStr;
    HBRUSH hBrush;
    // SetCursor(LoadCursorFromFile(L"1.cur")); // 将光标设置为新的光标
    switch (message) {
        case WM_LBUTTONDOWN:
            if ((!operate) && ready) {
                operate = TRUE;  // 左键击活俘获
                ready = FALSE;
                SetCapture(hwnd);  // 把所有的鼠标信息输入到被左键击活的窗口.
                SetCursor(LoadCursor(NULL, IDC_CROSS));  // 载入光标
                BeginP.x = LOWORD(lParam);
                BeginP.y = HIWORD(lParam);
            } else {
                SetCursor(LoadCursorFromFile(L"1.cur")); // 将光标设置为新的光标
            }
            return 0;
        case WM_MOUSEMOVE:
            if (operate) {
                EndP.x = LOWORD(lParam);
                EndP.y = HIWORD(lParam);
                rect.left = BeginP.x < EndP.x ? BeginP.x : EndP.x;
                rect.right = BeginP.x > EndP.x ? BeginP.x : EndP.x;
                rect.top = BeginP.y < EndP.y ? BeginP.y : EndP.y;
                rect.bottom = BeginP.y > EndP.y ? BeginP.y : EndP.y;
                SetCursor(LoadCursor(NULL, IDC_WAIT));  // 载入沙漏光标
                InvalidateRect(hwnd, NULL, TRUE);
            } else {
                SetCursor(LoadCursorFromFile(L"1.cur")); // 将光标设置为新的光标
            }
            return 0;
        case WM_LBUTTONUP:
            if (operate) {
                operate = FALSE;
                SetCursor(LoadCursor(NULL, IDC_WAIT));
                GetClientRect(hwnd, &rect);
                InvalidateRect(hwnd, NULL, TRUE);
                SetCursor(LoadCursor(NULL, IDC_ARROW));
                ReleaseCapture();  // 把鼠标从当前窗口中释放出来
            } else {
                SetCursor(LoadCursorFromFile(L"1.cur")); // 将光标设置为新的光标
            }
            return 0;
        case WM_PAINT:
            if (ready == FALSE) {
                hdc = BeginPaint(hwnd, &PtStr);
                hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
                // hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
                SelectObject(hdc, hBrush);
                Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
                DeleteObject(hBrush);
                EndPaint(hwnd, &PtStr);
            } else {
                //MessageBox(NULL, TEXT("Hello, world!"), TEXT("MessageBox Sample"), MB_OK);
                hdc = BeginPaint(hwnd, &PtStr);
                GetClientRect(hwnd, &rect);
                Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
                EndPaint(hwnd, &PtStr);
                SetCursor(LoadCursorFromFile(L"1.cur")); // 将光标设置为新的光标
            }
            return 0;
        case WM_RBUTTONDOWN:
            InvalidateRect(hwnd, NULL, TRUE);
            if (ready == FALSE) {
                ready = TRUE;
                InvalidateRect(hwnd, NULL, TRUE);
                SetCursor(LoadCursorFromFile(L"1.cur")); // 将光标设置为新的光标
            }
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
