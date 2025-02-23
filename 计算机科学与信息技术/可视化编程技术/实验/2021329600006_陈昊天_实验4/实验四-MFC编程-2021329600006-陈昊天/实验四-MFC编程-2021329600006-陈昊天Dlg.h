
// 实验四-MFC编程-2021329600006-陈昊天Dlg.h: 头文件
//

#pragma once


// C实验四MFC编程2021329600006陈昊天Dlg 对话框
class C实验四MFC编程2021329600006陈昊天Dlg : public CDialogEx {
    // 构造
public:
    C实验四MFC编程2021329600006陈昊天Dlg(CWnd* pParent = nullptr);	// 标准构造函数

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MFC2021329600006_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


    // 实现
protected:
    HICON m_hIcon;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    CStatic m_bmp;
    double m_num1;
    double m_num2;
    double m_result;
    int m_operator;
    afx_msg void OnEnChangeNum1();
    afx_msg void OnBnClickedAdd();
    afx_msg void OnBnClickedSub();
    afx_msg void OnBnClickedMul();
    afx_msg void OnBnClickedDiv();
    afx_msg void OnEnChangeNum2();
    afx_msg void OnEnChangeResult();
    afx_msg void OnBnClickedReset();
};
