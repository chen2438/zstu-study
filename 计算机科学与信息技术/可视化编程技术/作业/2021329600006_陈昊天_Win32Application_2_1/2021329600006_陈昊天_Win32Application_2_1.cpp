#include "windows.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//--------------- 以下是入口函数的代码-----------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wcex;

    HWND hWnd;
    MSG msg;
    TCHAR szWindowClass[] = L"窗口示例";  // 窗口类名
    TCHAR szTitle[] = L"2021329600006_陈昊天_Win32Application_2_1";      // 窗口标题名
    //------------ 以下初始化窗口类----------------
    wcex.cbSize = sizeof(WNDCLASSEX);  // 窗口类的大小
    wcex.style = 0;                    // 窗口样式为默认样式
    wcex.lpfnWndProc = WndProc;        // 定义窗口消息处理函数名称
    wcex.cbClsExtra = 0;               // 窗口类无扩展
    wcex.cbWndExtra = 0;               // 窗口实例无扩展
    wcex.hInstance = hInstance;        // 当前实例句柄
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    // 窗口的图标为默认图标
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);  // 窗口箭头光标
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    // 窗口背景为白色
    wcex.lpszMenuName = NULL;            // 窗口中无菜单
    wcex.lpszClassName = szWindowClass;  // 窗口类名为“窗口示例”
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    // 窗口的小图标为默认图标
    //--------------- 以下进行窗口类的注册-----------------
    if (!RegisterClassEx(&wcex)) {  // 如果注册失败则发出警告

        MessageBox(NULL, L"窗口类注册失败!", L"窗口注册", NULL);
        return 1;
    }
    //--------------- 以下进行创建窗口-----------------
    hWnd = CreateWindow(szWindowClass,        // 窗口类名
        szTitle,              // 窗口实例的标题名
        WS_OVERLAPPEDWINDOW,  // 窗口的风格
        CW_USEDEFAULT, CW_USEDEFAULT,
        // 窗口左上角坐标为默认值
        CW_USEDEFAULT, CW_USEDEFAULT,  // 高和宽为默认值
        NULL,                          // 此窗口无父窗口
        NULL,                          // 此窗口无主菜单
        hInstance,  // 创建应用程序的当前句柄
        NULL        // 不使用该值
    );
    if (!hWnd) {  // 若创建窗口失败则发出警告
        MessageBox(NULL, L"创建窗口失败!", L"创建窗口", NULL);
        return 1;
    }
    ShowWindow(hWnd, nCmdShow);           // 显示窗口
    UpdateWindow(hWnd);                   // 绘制用户区
    while (GetMessage(&msg, NULL, 0, 0)) {  // 消息循环
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;  // 程序终止时将信息返回系统
}
//--------------- 以下是窗口函数的代码-----------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
    LPARAM lParam) {
    switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);  // 调用PostQuitMessage发出WM_QUIT消息
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            // 默认时采用系统消息默认处理函数
            break;
    }
    return 0;
}