// dllmain.cpp : DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "TagIconOverlayHandler_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CTagIconOverlayHandlerModule _AtlModule;

class CTagIconOverlayHandlerApp : public CWinApp
{
public:

// 重写
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CTagIconOverlayHandlerApp, CWinApp)
END_MESSAGE_MAP()

CTagIconOverlayHandlerApp theApp;

BOOL CTagIconOverlayHandlerApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, NULL))
		return FALSE;
#endif
	return CWinApp::InitInstance();
}

int CTagIconOverlayHandlerApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
