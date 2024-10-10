// 2021329600006_陈昊天_课内考察.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "2021329600006_陈昊天_课内考察.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名


// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY2021329600006, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2021329600006));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

HMENU hmenu, hmenut, hmenuw;
int stPaint = 0;

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2021329600006));
    //wcex.hIcon = LoadIcon(hInstance, L"tian.ico");
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY2021329600006);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    //wcex.hIconSm = LoadIcon(hInstance, L"tian.ico");
    wcex.hCursor = LoadCursorFromFile(_T("chen.cur"));
    //wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance; // 将实例句柄存储在全局变量中

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) {
        return FALSE;
    }

    hmenu = GetMenu(hWnd);
    DeleteMenu(hmenu, 0, MF_POPUP | MF_BYPOSITION);//把自带的删掉
    hmenut = CreateMenu();
    hmenuw = CreateMenu();
    AppendMenu(hmenuw, MF_ENABLED, ID_CREATE, _T("创建"));
    AppendMenu(hmenuw, MF_GRAYED, ID_DELETE, _T("删除"));
    AppendMenu(hmenuw, MF_ENABLED, IDM_EXIT, _T("退出"));
    InsertMenu(hmenu, 0, MF_POPUP | MF_BYPOSITION, (UINT)hmenuw, _T("文件(&F)"));
    DrawMenuBar(hWnd);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hDC;
    HBRUSH hBrush;
    HPEN hPen;
    switch (message) {
        //case WM_SETCURSOR:
            // 设置为当前窗口光标
            //SetCursor(LoadCursorFromFile(L"chen.cur"));
            //return TRUE;
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId) {
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                case IDM_PAINT:
                    stPaint = 1;
                    InvalidateRect(hWnd, NULL, 1);
                    break;
                case ID_CREATE:
                    EnableMenuItem(hmenuw, ID_CREATE, MF_GRAYED);
                    EnableMenuItem(hmenuw, ID_DELETE, MF_ENABLED);
                    hmenut = CreateMenu();
                    AppendMenu(hmenut, MF_ENABLED, IDM_PAINT, _T("绘图"));
                    InsertMenu(hmenu, 1, MF_POPUP | MF_BYPOSITION, (UINT)hmenut, _T("编辑(&E)"));
                    DrawMenuBar(hWnd);
                    break;
                case ID_DELETE:
                    EnableMenuItem(hmenuw, ID_CREATE, MF_ENABLED);
                    EnableMenuItem(hmenuw, ID_DELETE, MF_GRAYED);
                    DeleteMenu(hmenu, 1, MF_BYPOSITION);
                    DrawMenuBar(hWnd);
                    break;

                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        case WM_PAINT:
        {
            hDC = BeginPaint(hWnd, &ps);
            hBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));//红色网状
            hPen = CreatePen(PS_SOLID, 2.5, RGB(0, 200, 255)); //淡蓝色画笔
            SelectObject(hDC, hBrush);
            SelectObject(hDC, hPen);
            RoundRect(hDC, 161, 148, 235, 185, 20, 20);
            Pie(hDC, 161, 185, 236, 260, 188, 185, 208, 185); 	//饼
            Rectangle(hDC, 161, 260, 235, 298);


            hPen = (HPEN)GetStockObject(BLACK_PEN); //空画笔
            hBrush = CreateSolidBrush(RGB(255, 0, 0));//红色画刷
            SelectObject(hDC, hPen);
            SelectObject(hDC, hBrush);
            Rectangle(hDC, 1000, 100, 1200, 300);//红正方形



            if (stPaint == 1) {
                hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
                hPen = (HPEN)GetStockObject(BLACK_PEN);
                SelectObject(hDC, hBrush);
                SelectObject(hDC, hPen);
                RoundRect(hDC, 600, 100, 800, 300, 40, 40);  //圆角正方形
                hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
                SelectObject(hDC, hBrush);
                Pie(hDC, 600, 110, 800, 290, 0, 0, 0, 0);//椭圆
            }
            DeleteObject(hPen);    //删除画笔
            DeleteObject(hBrush);  //删除画刷
            EndPaint(hWnd, &ps);
        }
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}
