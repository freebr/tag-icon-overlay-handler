// TagIconOverlayShlExt.h : CTagIconOverlayShlExt ������

#pragma once
#include "resource.h"       // ������



#include "TagIconOverlayHandler_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CTagIconOverlayShlExt

class ATL_NO_VTABLE CTagIconOverlayShlExt :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTagIconOverlayShlExt, &CLSID_TagIconOverlayShlExt>,
	public IDispatchImpl<ITagIconOverlayShlExt, &IID_ITagIconOverlayShlExt, &LIBID_TagIconOverlayHandlerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellIconOverlayIdentifier
{
public:
	CTagIconOverlayShlExt()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TAGICONOVERLAYSHLEXT)


BEGIN_COM_MAP(CTagIconOverlayShlExt)
	COM_INTERFACE_ENTRY(ITagIconOverlayShlExt)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellIconOverlayIdentifier)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(IsMemberOf)(THIS_ _In_ PCWSTR pwszPath, DWORD dwAttrib);
	STDMETHOD(GetOverlayInfo)(THIS_ _Out_writes_(cchMax) PWSTR pwszIconFile,
		int cchMax, _Out_ int* pIndex, _Out_ DWORD* pdwFlags);
	STDMETHOD(GetPriority)(THIS_ _Out_ int* pIPriority);


};

OBJECT_ENTRY_AUTO(__uuidof(TagIconOverlayShlExt), CTagIconOverlayShlExt)

WCHAR* extensions[] = {
	L".csv",
	L".doc",
	L".dot",
	L".docx",
	L".docm",
	L".xls",
	L".xlsx",
	L".xlst",
	L".xlsm",
	L".ppt",
	L".pptx",
	L".pdf",
	L".bmp",
	L".png",
	L".jpg",
	L".jpeg",
	L".gif",
	L".tiff",
	L".txt",
	L".rtf",
	L".rar",
	L".wps",
	L".xps",
};