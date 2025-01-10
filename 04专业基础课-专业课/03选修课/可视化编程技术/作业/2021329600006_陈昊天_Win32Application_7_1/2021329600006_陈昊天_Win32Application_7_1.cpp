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
LPCWSTR cUpWarn = L"�����������ƶ���";
LPCWSTR cDownWarn = L"�����������ƶ���";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    hBm = LoadBitmap(hInstance, L"pic6");
    GetObject(hBm, sizeof(BITMAP), (LPVOID)&bm);
    //���λͼ��Ϣ
    iWindowWidth = 2 * 160;	//�õ����ڵĿ��
    iWindowHeight = 2 * 138;	//�õ����ڵĸ߶�

    if (!InitWindowClass(hInstance, nCmdShow)) {
        MessageBox(NULL, L"��������ʧ��", L"��������", NULL);
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
                case VK_UP:			//���ϼ�ͷʱ,λ��-10
                    iY = iY - 10;	break;
                case VK_DOWN:			//���¼�ͷʱ,λ��+10
                    iY = iY + 10;	break;
            }
            InvalidateRect(hWnd, NULL, 1);	//ˢ���û���
            break;
        case WM_CREATE:
            hDC = GetDC(hWnd);
            hdcmem = CreateCompatibleDC(hDC);
            ReleaseDC(hWnd, hDC);
        case WM_PAINT:				//�����ͼ��Ϣ
            hDC = BeginPaint(hWnd, &ps);		//�õ��豸�������
            if (iY > 0 && iY < iWindowHeight / 2)	//��λͼ�������ڴ�����ʱ
            {
                SelectObject(hdcmem, hBm);	//ѡ���ڴ���
                BitBlt(hDC, 60, iY, bm.bmWidth, bm.bmHeight,
                    hdcmem, 0, 0, SRCCOPY);//���λͼ
            } else if (iY <= 0)	//��λͼ���ϱ߽糬���˴���ʱ
                TextOut(hDC, 0, 0, cUpWarn, sizeof(cUpWarn));//�������
            else			//��λͼ���±߽糬���˴���ʱ
                TextOut(hDC, 0, 0, cDownWarn, sizeof(cDownWarn));//�������
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
    WNDCLASSEX wcex;                        // ������
    TCHAR szWindowClass[] = L"Bitmap";
    TCHAR szTitle[] = L"2021329600006_�����_Win32Application_7_2";
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = 0;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;  // Ӧ�ó���ʵ�����
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
        MessageBox(NULL, L"ע�ᴰ��ʧ��", L"ע�ᴰ��", NULL);
        return FALSE;
    }
    hWndMain = CreateWindow(szWindowClass, szTitle,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0,
        iWindowWidth, iWindowHeight, NULL, NULL, hInstance, NULL);
    if (!hWndMain) {
        MessageBox(NULL, L"��������ʧ��", L"��������", NULL);
        return FALSE;
    }
    ShowWindow(hWndMain, nCmdShow);  // ��ʾ����
    UpdateWindow(hWndMain);          // ˢ�´���
    return TRUE;
}