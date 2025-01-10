#include<windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);

PAINTSTRUCT ps;
HWND hWndMain;
HDC hDC;
HDC hdcmem;
HBITMAP hBm;
BITMAP bm;
int iY = 50;
int iWindowWidth, iWindowHeight;
LPCWSTR cUpWarn = L"不能再向上移动了";
LPCWSTR cDownWarn = L"不能再向下移动了";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    hBm = LoadBitmap(hInstance, L"pic6");
    GetObject(hBm, sizeof(BITMAP), (LPVOID)&bm);
    //获得位图信息
    iWindowWidth = 2 * 160;	//得到窗口的宽度
    iWindowHeight = 2 * 138;	//得到窗口的高度

    if (!InitWindowClass(hInstance, nCmdShow)) {
        MessageBox(NULL, L"创建窗口失败", L"创建窗口", NULL);
        return 1;
    }
    HACCEL hAccel = LoadAccelerators(hInstance, L"lpszMenuName");
    while (GetMessage(&msg, NULL, 0, 0)) {
        //if (!TranslateAccelerator(hwnd, hAccel, &msg)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        //}
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
    LPARAM lParam) {

    switch (message) {
        case WM_LBUTTONDOWN:
            iY = iY - 10;
            InvalidateRect(hWnd, NULL, 1);
            break;
        case WM_RBUTTONDOWN:
            iY = iY + 10;
            InvalidateRect(hWnd, NULL, 1);
            break;
        case WM_KEYDOWN:
            switch (wParam) {
                case VK_UP:			//按上箭头时,位置-10
                    iY = iY - 10;	break;
                case VK_DOWN:			//按下箭头时,位置+10
                    iY = iY + 10;	break;
            }
            InvalidateRect(hWnd, NULL, 1);	//刷新用户区
            break;
        case WM_CREATE:
            hDC = GetDC(hWnd);
            hdcmem = CreateCompatibleDC(hDC);
            ReleaseDC(hWnd, hDC);
        case WM_PAINT:				//处理绘图消息
            hDC = BeginPaint(hWnd, &ps);		//得到设备环境句柄
            if (iY > 0 && iY < iWindowHeight / 2)	//当位图完整的在窗口中时
            {
                SelectObject(hdcmem, hBm);	//选入内存句柄
                BitBlt(hDC, 60, iY, bm.bmWidth, bm.bmHeight,
                    hdcmem, 0, 0, SRCCOPY);//输出位图
            } else if (iY <= 0)	//当位图的上边界超出了窗口时
                TextOut(hDC, 0, 0, cUpWarn, sizeof(cUpWarn));//输出警告
            else			//当位图的下边界超出了窗口时
                TextOut(hDC, 0, 0, cDownWarn, sizeof(cDownWarn));//输出警告
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            DeleteObject(hBm);
            PostQuitMessage(0);
            return 0;
        default:
            return(DefWindowProc(hWnd, message, wParam, lParam));
    }
}
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) {
    //HWND hwnd;
    WNDCLASSEX wcex;                        // 窗口类
    TCHAR szWindowClass[] = L"Bitmap";
    TCHAR szTitle[] = L"2021329600006_陈昊天_Win32Application_7_2";
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = 0;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;  // 应用程序实例句柄
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    //wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    //wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    //wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = L"Menu";
    wcex.lpszClassName = szWindowClass;

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, L"注册窗口失败", L"注册窗口", NULL);
        return FALSE;
    }
    hWndMain = CreateWindow(szWindowClass, szTitle,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0,
        iWindowWidth, iWindowHeight, NULL, NULL, hInstance, NULL);
    if (!hWndMain) {
        MessageBox(NULL, L"创建窗口失败", L"创建窗口", NULL);
        return FALSE;
    }
    ShowWindow(hWndMain, nCmdShow);  // 显示窗口
    UpdateWindow(hWndMain);          // 刷新窗口
    return TRUE;
}