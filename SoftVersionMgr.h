
// SoftVersionMgr.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSoftVersionMgrApp:
// �йش����ʵ�֣������ SoftVersionMgr.cpp
//

class CSoftVersionMgrApp : public CWinApp
{
public:
	CSoftVersionMgrApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSoftVersionMgrApp theApp;