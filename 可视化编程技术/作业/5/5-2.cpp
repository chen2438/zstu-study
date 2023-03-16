#include <tchar.h>
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
    TCHAR lpszTitle[] = L"2021329600006_陈昊天_Win32Application_3_1";
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
    TCHAR lpszTitle[] = L"2021329600006_陈昊天_Win32Application_3_1";
    hwnd =
        CreateWindow(lpszClassName, lpszTitle,  // 创建窗口
                     WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                     CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);  // 显示窗口
    UpdateWindow(hwnd);          // 刷新窗口
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
    static const int BufSize = 15;  // 设置存放字符的缓冲区大小
    static wchar_t cCharBuf
        [BufSize];  // 设置静态字符数组，存放输入的字符，字符个数不能超出缓冲区大小
    // static wchar_t wchar[BufSize];
    static int nNumChar = 0;   // 现有字符个数
    static int nArrayPos = 0;  // 字符的位置
    static int nLnHeight;
    static int nCharWidth;
    int x;
    HDC hDC;
    TEXTMETRIC tm;
    PAINTSTRUCT PtStr;   // 定义指向包含绘图信息的结构体变量
    switch (message) {   // 处理消息
        case WM_CHAR: {  // 遇到非系统字符所作的处理
            if (wParam == VK_BACK) {  // 处理“遇到回退键的消息”
                if (nArrayPos ==
                    0)  // 若已在一行文字的开始处，则提示用户"不能回退"
                    MessageBox(hWnd, L"当前位置是文本的起始位置，不能回退",
                               NULL, MB_OK);
                else {
                    nArrayPos =
                        nArrayPos - 1;  // 每按一次回退键就回退一个字符的位置
                    nNumChar = nNumChar - 1;  // 对现有字符总数进行计数
                    InvalidateRect(hWnd, NULL,
                                   TRUE);  // 刷新用户区，并序发送WM_PAINT消息
                }
                break;
            }
            if (wParam == VK_ESCAPE) {  // 处理按下Escape键消息

                MessageBox(hWnd, L"您现在不能按ESC键，请继续其它操作", NULL,
                           MB_OK);
                break;
            }
            if (nNumChar >= BufSize) {  // 如果写入的字符数超过缓冲区大小，则报警

                MessageBox(hWnd,
                           L"缓冲区已满，不能再输入字符了\n若需要删除字符，请用"
                           L"BackSpace键",
                           NULL, MB_OK);
                break;
            }
            for (x = nNumChar; x > nArrayPos; x = x - 1)
                cCharBuf[x] = cCharBuf[x - 1];
            cCharBuf[nArrayPos] = (unsigned char)wParam;
            nArrayPos = nArrayPos + 1;
            nNumChar = nNumChar + 1;
            InvalidateRect(hWnd, NULL, TRUE);
        } break;
        case WM_CREATE: {  // 处理窗口创建消息
            hDC = GetDC(hWnd);
            GetTextMetrics(hDC, &tm);  // 获取字体信息
            nLnHeight = tm.tmHeight + tm.tmExternalLeading;
            nCharWidth = tm.tmAveCharWidth;
            ReleaseDC(hWnd, hDC);
        } break;
        case WM_KEYDOWN: {  // 处理按下键消息
            switch (wParam) {
                case VK_END:               // 处理按下键为End时的消息
                    nArrayPos = nNumChar;  // 输入位置从本行的末尾开始
                    break;
                case VK_HOME:       // 处理按下键为Home时的消息
                    nArrayPos = 0;  // 输入位置为本行的起始位置
                    break;
                case VK_DELETE:  // 处理按下键为Delete时的消息
                    if (nArrayPos == nNumChar)  // 输入位置处于本行的末尾
                        MessageBox(hWnd, L"缓冲区已空，没有字符可供删除", NULL,
                                   MB_OK);
                    else {
                        for (x = nArrayPos; x < nNumChar; x = x + 1)
                            cCharBuf[x] =
                                cCharBuf[x + 1];  // 每删除一个字符，总字符数减1
                        nNumChar = nNumChar - 1;
                        InvalidateRect(hWnd, NULL, TRUE);  // 用户区刷新
                    }
                    break;
                case VK_LEFT:  // 处理按下左方向键时的消息
                    if (nArrayPos > 0)
                        nArrayPos = nArrayPos - 1;  // 当前输入位置往前移一个位置
                    else
                        MessageBox(hWnd,
                                   L"您已经移动到起始位置，不能再往左移动了",
                                   NULL, MB_OK);
                    break;
                case VK_RIGHT:  // 处理按下右方向键时的消息
                    if (nArrayPos <
                        nNumChar)  // 若当前位置未到缓冲区的末尾，可向右移动
                        nArrayPos = nArrayPos + 1;
                    else
                        MessageBox(hWnd, L"已经到缓冲区的末尾,不能再向右移动了",
                                   NULL, MB_OK);
                    break;
            }
        } break;
        case WM_PAINT:  // 处理重画消息
            hDC = BeginPaint(hWnd, &PtStr);
            // lpcwstr
            TextOut(hDC, nCharWidth, nLnHeight, cCharBuf, nNumChar);  // 输出文本
            EndPaint(hWnd, &PtStr);
            break;
        case WM_DESTROY:         // 处理结束应用程序消息
            PostQuitMessage(0);  // 结束应用程序
            break;
        default:  // 其他消息处理程序
            return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return 0;
}
