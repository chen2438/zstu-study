#include <tchar.h>
#include <windows.h>
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    if (!InitWindowClass(hInstance, nCmdShow)) {
        MessageBox(NULL, L"创建窗口失败!", _T("创建窗口"), NULL);
        return 1;
    }
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
    HDC hdc;
    HFONT hF_black, hF_big;  // 定义两种字体句柄
    PAINTSTRUCT ps;
    TEXTMETRIC tm;  // 定义一个TEXTMETRIC结构，用以记录字体信息
    LPCWSTR lpsz_1 = L"这是一行红色的、字体为SYSTEM_FONT的文字，红色代表未来";
    LPCWSTR lpsz_2 = L"现在显示的是自定义绿色字体，绿色代表生机勃勃";
    LPCWSTR lpsz_3 = L"这一行是蓝色的粗体字，蓝色代表广阔的海洋和天空";
    LPCWSTR lpsz_4 = L"这是大号、斜体并带有下划线的文字";
    LPCWSTR lpsz_5 = L"您掌握了字体的操作了吗?";
    LPCWSTR lpsz_6 = L"祝您成功!";
    LPCWSTR lpsz_7 = L"Visual C++课程很有用!";
    int X = 0, Y = 0;
    static RECT rect = {0, 300, 0, 350};
    SIZE size;  // 定义一个SIZE类型的结构
    switch (message) {
        case WM_CREATE:
            SetTimer(hWnd, 9999, 50, NULL);  // 设置定时器 50ms
            break;
        case WM_TIMER:
            if (wParam == 9999)                    // 定时刷新
                InvalidateRect(hWnd, NULL, true);  // 使hWnd失效以便重新绘制
            break;
        case WM_PAINT:
            rect.right += 2;  // 矩形的右边界增2
            hdc = BeginPaint(hWnd, &ps);
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
        case WM_DESTROY:
            PostQuitMessage(0);  // 调用PostQuitMessage发出WM_QUIT消息
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }
    return 0;
}
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) {
    WNDCLASSEX wcex;
    HWND hWnd;
    TCHAR szWindowClass[] = L"窗口示例";
    TCHAR szTitle[] = L"2021329600006_陈昊天_Win32Application_4_1";

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;

    if (!RegisterClassEx(&wcex)) return FALSE;

    // return 0;
    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (!hWnd) return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}
