#include <tchar.h>
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
    int pointx, pointy;
    HDC hdc;            // 定义指向设备环境的句柄
    TEXTMETRIC tm;      // 存放字体各种属性的结构体变量
    PAINTSTRUCT PtStr;  // 指向包含绘图信息的结构体变量
    LPCWSTR textbuf[4] = {{L"故人西辞黄鹤楼"},
                          {L"烟花三月下扬州"},
                          {L"孤帆远影碧空尽"},
                          {L"唯见长江天际流"}};
    // LPCWSTR textbuf[4] = { L"故人西辞黄鹤楼", L"烟花三月下扬州",
    //                       L"孤帆远影碧空尽", L"唯见长江天际流" };
    HFONT hF_black, hF_big;  // 定义两种字体句柄
    PAINTSTRUCT ps;
    // TEXTMETRIC tm;  // 定义一个TEXTMETRIC结构，用以记录字体信息
    LPCWSTR lpsz_1 = L"这是一行红色的、字体为SYSTEM_FONT的文字，红色代表未来";
    LPCWSTR lpsz_2 = L"现在显示的是自定义绿色字体，绿色代表生机勃勃";
    LPCWSTR lpsz_3 = L"这一行是蓝色的粗体字，蓝色代表广阔的海洋和天空";
    LPCWSTR lpsz_4 = L"这是大号、斜体并带有下划线的文字";
    LPCWSTR lpsz_5 = L"您掌握了字体的操作了吗?";
    LPCWSTR lpsz_6 = L"祝您成功!";
    LPCWSTR lpsz_7 = L"Visual C++课程很有用!";
    int X = 0, Y = 0;
    static RECT rect = {0, 300, 0, 350};
    SIZE size;           // 定义一个SIZE类型的结构
    switch (iMessage) {  // 处理消息

        case WM_CREATE:                      // 处理窗口创建消息
            SetTimer(hWnd, 9999, 50, NULL);  // 设置定时器 50ms
            hdc = GetDC(hWnd);               // 获取当前设备表句柄
            GetTextMetrics(hdc, &tm);        // 获取字体信息
            nXChar = tm.tmAveCharWidth;      // 获取字符宽度
            nYChar = tm.tmHeight + tm.tmExternalLeading;  // 字符高度
            nCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * nXChar / 2;  // 字间距
            ReleaseDC(hWnd, hdc);  // 释放当前设备句柄
            break;
        case WM_TIMER:
            if (wParam == 9999)                    // 定时刷新
                InvalidateRect(hWnd, NULL, true);  // 使hWnd失效以便重新绘制
            break;
        case WM_PAINT:                       // 处理重画消息
            hdc = BeginPaint(hWnd, &PtStr);  // 开始绘图
            for (int i = 4; i >= 1; i--) {
                for (int j = 0; j <= 6; j++) {  // 输出文本
                    // 100,50
                    pointx = 700 + i * nXChar * 5;
                    pointy = 50 + j * (nYChar + nCaps);
                    TextOut(hdc, pointx, pointy, textbuf[4 - i] + j, 1);
                }
            }
            // EndPaint(hWnd, &PtStr);

            rect.right += 2;  // 矩形的右边界增2
            // hdc = BeginPaint(hWnd, &ps);
            SetTextColor(hdc, RGB(255, 0, 0));  // 设置文本颜色为红色
            GetTextMetrics(hdc, &tm);  // 获取默认字体，写入tm结构中
            TextOut(hdc, X, Y, lpsz_1,
                    _tcsclen(lpsz_1));  // 使用当前字体输出文本
            Y = Y + tm.tmHeight +
                tm.tmExternalLeading;  // 高度+行间距 计算换行时下一行纵坐标
            hF_black = CreateFont(    // 创建自定义字体
                20,                   // 字体的高度
                0,                    // 系统选取宽度
                0,                    // 倾斜度0，水平
                0,                    // 与基线的倾斜度0，平行
                FW_HEAVY,             // 字体的粗度，FW_HEAVY为最粗
                0,                    // 非斜体字
                0,                    // 无下划线
                0,                    // 无删除线
                GB2312_CHARSET,       // 字符集
                OUT_DEFAULT_PRECIS,   // 输出精度默认
                CLIP_DEFAULT_PRECIS,  // 剪裁精度默认
                DEFAULT_QUALITY,      // 输出质量默认
                DEFAULT_PITCH | FF_DONTCARE,  // 字间距和字体系列使用默认值
                L"粗体字"                     // 字体名称
            );
            SetTextColor(hdc, RGB(0, 255, 0));  // 文本绿色
            SelectObject(hdc, hF_black);  // 将自定义字体选入设备环境
            GetTextMetrics(hdc, &tm);  // 获取字体的信息，并写入tm结构中
            TextOut(hdc, X, Y, lpsz_2,
                    _tcsclen(lpsz_2));  // 使用当前字体输出文本
            // 换行继续输出文本，计算新行的起始Y坐标位置
            Y = Y + tm.tmHeight + 5 * tm.tmExternalLeading;
            GetTextExtentPoint32(hdc, lpsz_2, _tcsclen(lpsz_2), &size);
            // 获取字符串的宽度
            SetTextColor(hdc, RGB(0, 0, 255));  // 设置文本颜色为蓝色
            TextOut(hdc, X, Y, lpsz_3, _tcsclen(lpsz_3));  // 用当前字体输出文本
            Y = Y + tm.tmHeight + 5 * tm.tmExternalLeading;
            hF_big = CreateFont(  // 引入新字体
                30,               // 高度
                0, 0, 0, FW_NORMAL,
                1,  // 斜体
                1,  // 下划线
                0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"大号字");
            SelectObject(hdc, hF_big);  // 将第二种自定义字体选入设备环境
            SetTextColor(hdc, RGB(155, 155, 155));  // 设置文本颜色为灰色
            Y = Y + tm.tmHeight + 5 * tm.tmExternalLeading;
            TextOut(hdc, X, Y, lpsz_4, _tcsclen(lpsz_4));  // 以当前字体输出文本
            SetTextColor(hdc, RGB(255, 0, 0));  // 设置文本颜色为红色
            Y = Y + tm.tmHeight + 10 * tm.tmExternalLeading;
            TextOut(hdc, X, Y, lpsz_5, _tcsclen(lpsz_5));  // 输出文本
            // 在该行继续输出文本
            GetTextExtentPoint32(hdc, lpsz_5, _tcsclen(lpsz_5), &size);
            X = X + size.cx;  // 获取字符串的宽度
            TextOut(hdc, X + 5, Y, lpsz_6, _tcsclen(lpsz_6));  // 输出文本
            hF_big = CreateFont(  // 引入新字体
                48, 0, 0, 0, FW_NORMAL, 0, 0, 0, GB2312_CHARSET,
                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE, L"楷体_GB2312");
            SelectObject(hdc, hF_big);  // 获取起始坐标
            SetTextColor(hdc, RGB(0, 0, 0));
            SetBkColor(hdc, RGB(100, 150, 100));
            TextOut(hdc, 0, 300, lpsz_7, _tcsclen(lpsz_7));  // 输出文本
            SetTextColor(hdc, RGB(0, 255, 0));
            SetBkColor(hdc, RGB(150, 50, 50));
            DrawText(hdc, lpsz_7, _tcslen(lpsz_7), &rect, DT_LEFT);
            GetTextExtentPoint32(hdc, lpsz_7, _tcsclen(lpsz_7), &size);
            if (rect.right >= size.cx) rect.right = 0;
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