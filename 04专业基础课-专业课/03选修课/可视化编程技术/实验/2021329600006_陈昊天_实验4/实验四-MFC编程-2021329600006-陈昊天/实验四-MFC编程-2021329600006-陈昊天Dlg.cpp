
// 实验四-MFC编程-2021329600006-陈昊天Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "实验四-MFC编程-2021329600006-陈昊天.h"
#include "实验四-MFC编程-2021329600006-陈昊天Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx {
public:
    CAboutDlg();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    // 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C实验四MFC编程2021329600006陈昊天Dlg 对话框



C实验四MFC编程2021329600006陈昊天Dlg::C实验四MFC编程2021329600006陈昊天Dlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MFC2021329600006_DIALOG, pParent), m_num1(0), m_num2(0), m_result(0), m_operator(0) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C实验四MFC编程2021329600006陈昊天Dlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_BMP, m_bmp);
    //DDX_Control(pDX, IDC_NUM1, m_num);
    DDX_Text(pDX, IDC_NUM1, m_num1);
    DDX_Text(pDX, IDC_NUM2, m_num2);
    DDX_Text(pDX, IDC_RESULT, m_result);
    DDX_Radio(pDX, IDC_ADD, m_operator);
}

BEGIN_MESSAGE_MAP(C实验四MFC编程2021329600006陈昊天Dlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()

    ON_EN_CHANGE(IDC_NUM1, &C实验四MFC编程2021329600006陈昊天Dlg::OnEnChangeNum1)
    ON_BN_CLICKED(IDC_ADD, &C实验四MFC编程2021329600006陈昊天Dlg::OnBnClickedAdd)
    ON_BN_CLICKED(IDC_SUB, &C实验四MFC编程2021329600006陈昊天Dlg::OnBnClickedSub)
    ON_BN_CLICKED(IDC_MUL, &C实验四MFC编程2021329600006陈昊天Dlg::OnBnClickedMul)
    ON_BN_CLICKED(IDC_DIV, &C实验四MFC编程2021329600006陈昊天Dlg::OnBnClickedDiv)
    ON_EN_CHANGE(IDC_NUM2, &C实验四MFC编程2021329600006陈昊天Dlg::OnEnChangeNum2)
    ON_EN_CHANGE(IDC_RESULT, &C实验四MFC编程2021329600006陈昊天Dlg::OnEnChangeResult)
    ON_BN_CLICKED(IDC_RESET, &C实验四MFC编程2021329600006陈昊天Dlg::OnBnClickedReset)
END_MESSAGE_MAP()


// C实验四MFC编程2021329600006陈昊天Dlg 消息处理程序

BOOL C实验四MFC编程2021329600006陈昊天Dlg::OnInitDialog() {
    CDialogEx::OnInitDialog();
    SetWindowText(_T("实验四-MFC编程-2021329600006-陈昊天"));
    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr) {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    // TODO: 在此添加额外的初始化代码
    m_bmp.ModifyStyle(0, SS_BITMAP);
    HBITMAP hBmp = LoadBitmap(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDB_BITMAP1));
    m_bmp.SetBitmap(hBmp);

    // 获取对应的static text控件对象指针
    CStatic* pStaticText = (CStatic*)GetDlgItem(IDC_STATIC_YSS);
    pStaticText->SetWindowText(_T("运算数"));
    pStaticText = (CStatic*)GetDlgItem(yunsuanfu);
    pStaticText->SetWindowText(_T("运算符"));
    pStaticText = (CStatic*)GetDlgItem(yunsuanshu2);
    pStaticText->SetWindowText(_T("运算数"));
    pStaticText = (CStatic*)GetDlgItem(jieguo);
    pStaticText->SetWindowText(_T("结果"));

    pStaticText = (CStatic*)GetDlgItem(IDC_ADD);
    pStaticText->SetWindowText(_T("加"));
    pStaticText = (CStatic*)GetDlgItem(IDC_SUB);
    pStaticText->SetWindowText(_T("减"));
    pStaticText = (CStatic*)GetDlgItem(IDC_MUL);
    pStaticText->SetWindowText(_T("乘"));
    pStaticText = (CStatic*)GetDlgItem(IDC_DIV);
    pStaticText->SetWindowText(_T("除"));

    pStaticText = (CStatic*)GetDlgItem(IDC_RESET);
    pStaticText->SetWindowText(_T("重置"));
    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C实验四MFC编程2021329600006陈昊天Dlg::OnSysCommand(UINT nID, LPARAM lParam) {
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    } else {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C实验四MFC编程2021329600006陈昊天Dlg::OnPaint() {
    if (IsIconic()) {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    } else {
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C实验四MFC编程2021329600006陈昊天Dlg::OnQueryDragIcon() {
    return static_cast<HCURSOR>(m_hIcon);
}



void C实验四MFC编程2021329600006陈昊天Dlg::OnEnChangeNum1() {
    UpdateData(TRUE); //使用UpdateData(TRUE)是将对话框各控件的内容更新到所对应的成员变量
    switch (m_operator)   //设为组的单选框若对应的成员变量为整型，选中后变量的值按ID从低到高的顺序对应的值从递增
    {
        case 0:	m_result = m_num1 + m_num2;	break;
        case 1:	m_result = m_num1 - m_num2;	break;
        case 2:	m_result = m_num1 * m_num2;	break;
        case 3:
            if (m_num2 == 0)
                AfxMessageBox(L"Error", MB_YESNO | MB_ICONQUESTION);
            else
                m_result = m_num1 / m_num2;
    }
    UpdateData(FALSE); //将成员变量的值更新到对话框中的控件

}


void C实验四MFC编程2021329600006陈昊天Dlg::OnBnClickedAdd() {
    // TODO: 在此添加控件通知处理程序代码
    OnEnChangeNum1();
}


void C实验四MFC编程2021329600006陈昊天Dlg::OnBnClickedSub() {
    // TODO: 在此添加控件通知处理程序代码
    OnEnChangeNum1();
}


void C实验四MFC编程2021329600006陈昊天Dlg::OnBnClickedMul() {
    // TODO: 在此添加控件通知处理程序代码
    OnEnChangeNum1();
}


void C实验四MFC编程2021329600006陈昊天Dlg::OnBnClickedDiv() {
    // TODO: 在此添加控件通知处理程序代码
    OnEnChangeNum1();
}


void C实验四MFC编程2021329600006陈昊天Dlg::OnEnChangeNum2() {
    OnEnChangeNum1();
    // TODO:  如果该控件是 RICHEDIT 控件，它将不
    // 发送此通知，除非重写 CDialogEx::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

    // TODO:  在此添加控件通知处理程序代码
}


void C实验四MFC编程2021329600006陈昊天Dlg::OnEnChangeResult() {
    // TODO:  如果该控件是 RICHEDIT 控件，它将不
    // 发送此通知，除非重写 CDialogEx::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

    // TODO:  在此添加控件通知处理程序代码
}


void C实验四MFC编程2021329600006陈昊天Dlg::OnBnClickedReset() {
    // TODO: 在此添加控件通知处理程序代码
    m_result = m_num1 = m_num2 = m_operator = 0;
    UpdateData(FALSE);

}
