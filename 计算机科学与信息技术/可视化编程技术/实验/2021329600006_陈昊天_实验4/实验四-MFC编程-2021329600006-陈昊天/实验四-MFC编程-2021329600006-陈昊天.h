
// 实验四-MFC编程-2021329600006-陈昊天.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// C实验四MFC编程2021329600006陈昊天App:
// 有关此类的实现，请参阅 实验四-MFC编程-2021329600006-陈昊天.cpp
//

class C实验四MFC编程2021329600006陈昊天App : public CWinApp
{
public:
	C实验四MFC编程2021329600006陈昊天App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C实验四MFC编程2021329600006陈昊天App theApp;
