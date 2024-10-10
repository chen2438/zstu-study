// WindowsProject1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsProject1.h"
#include "cmath"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HMENU hmenu, haddmenu, hmenut;

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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
    haddmenu = CreateMenu();
    hmenut = CreateMenu();

    // hmenut = LoadMenu(hInstance, _T("IDR_MENUCAL"));
    AppendMenu(hmenut, MF_ENABLED, ID_sum, _T("总和"));
    AppendMenu(hmenut, MF_ENABLED, ID_variance, _T("方差"));
    AppendMenu(hmenut, MF_ENABLED, ID_rms, _T("均方根"));
    InsertMenu(hmenu, 1, MF_POPUP | MF_BYPOSITION, (UINT)hmenut, _T("计算(&C)"));
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

    static HCURSOR hCursor = LoadCursorFromFile(L"hao2.cur");
    switch (message) {
        case WM_SETCURSOR:
            // 加载自定义光标文件

            // 设置为当前窗口光标
            SetCursor(hCursor);
            // 返回TRUE表示已处理消息，不需要系统再进行默认处理
            return TRUE;
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);
            const double M_PI = 3.1415926;
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            HPEN hPen;
            HBRUSH hBrush;
            static RECT rc, ovalRc, rc2;
            static POINT center, startPoint;
            static double startAngle, endAngle;
            static RECT squareRc;
            //staint cornerRadius
            // 分析菜单选择:
            switch (wmId) {
                case IDM_PAINT:
                    hPen = CreatePen(PS_DASHDOT, 1, RGB(0, 255, 0));//自定义绿笔
                    //所画线条为点划线，宽度为1
                    hBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));//红色网状
                    SetMapMode(hDC, MM_TEXT);	//设置映射模式，用缺省模式
                    SelectObject(hDC, hBrush);	//更新画刷，用“红色网状”
                    //使用当前缺省画笔、画刷进行绘图
                    //Rectangle(hDC, 130, 60, 270, 200);	//绘制矩形，并填充
                    rc = { 130, 60, 270, 100 }; // 矩形区域
                    RoundRect(hDC, rc.left, rc.top, rc.right, rc.bottom, 20, 20);

                    // 定义椭圆区域
                    //ovalRc = { 150, 100, 250, 160 }; // 椭圆区域

                    // 绘制椭圆饼图
                    //startAngle = M_PI * 0.6; // 起始角度，弧度制
                    //endAngle = M_PI * 0.5; // 结束角度，弧度制

                    //center = { (ovalRc.left + ovalRc.right) / 2, (ovalRc.top + ovalRc.bottom) / 2 }; // 饼图圆心点
                    //startPoint = { center.x + (int)(55 * cos(startAngle)), center.y - (int)(55 * sin(startAngle)) }; // 起始点

                    // 绘制饼图
                    Pie(hDC, 150, 100, 250, 160, 170, 120, 230, 120);

                    rc2 = { 130, 160, 270, 200 }; // 矩形区域
                    RoundRect(hDC, rc2.left, rc2.top, rc2.right, rc2.bottom, 0, 0);

                    // 创建画刷
                    hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 红色画刷

                    // 选择画刷
                    SelectObject(hDC, hBrush);

                    // 绘制正方形
                    squareRc = { 300, 100, 400, 200 }; // 正方形区域
                    Rectangle(hDC, squareRc.left, squareRc.top, squareRc.right, squareRc.bottom);

                    //Ellipse(hDC, 130, 70, 270, 190);//绘制椭圆，并填充    
                    SelectObject(hDC, hPen);	//更新画笔，选“自定义绿笔”

                    MoveToEx(hDC, 100, 130, NULL); //使用当前画笔绘制轴线
                    LineTo(hDC, 300, 130);
                    MoveToEx(hDC, 200, 30, NULL);
                    LineTo(hDC, 200, 230);
                    EndPaint(hWnd, &ps);
                    break;
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case ID_del://删除总和
                    DeleteMenu(hmenut, ID_sum, MF_BYCOMMAND);
                    break;
                case ID_add:
                    AppendMenu(hmenut, MF_ENABLED, ID_avg, _T("平均值"));
                    DrawMenuBar(hWnd);
                    break;
                case ID_modify:
                    //ModifyMenu(hmenut, 2, MF_BYPOSITION, ID_rms, _T("线性拟合"));
                    // 假设hMenu为包含要修改的菜单项的菜单句柄，menuItemId为要修改的菜单项ID，newText为新的菜单项文本
                    ModifyMenu(hmenut, ID_rms, MF_BYCOMMAND | MF_STRING, ID_rms, _T("线性拟合"));

                    DrawMenuBar(hWnd);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        case WM_LBUTTONDOWN:

            AppendMenu(haddmenu, MF_GRAYED, ID_del, _T("删除计算总和"));
            AppendMenu(haddmenu, MF_GRAYED, ID_add, _T("添加计算平均值"));
            AppendMenu(haddmenu, MF_GRAYED, ID_modify, _T("修改计算均方根"));
            InsertMenu(hmenu, 2, MF_POPUP | MF_BYPOSITION, (UINT)haddmenu, _T("编辑(&E)"));
            DrawMenuBar(hWnd);
            break;
        case WM_RBUTTONDOWN:
            EnableMenuItem(haddmenu, ID_del, MF_ENABLED);
            EnableMenuItem(haddmenu, ID_add, MF_ENABLED);
            EnableMenuItem(haddmenu, ID_modify, MF_ENABLED);
            break;
        case WM_PAINT:
        {

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