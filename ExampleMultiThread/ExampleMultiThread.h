
// ExampleMultiThread.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExampleMultiThreadApp:
// �йش����ʵ�֣������ ExampleMultiThread.cpp
//

class CExampleMultiThreadApp : public CWinApp
{
public:
	CExampleMultiThreadApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExampleMultiThreadApp theApp;