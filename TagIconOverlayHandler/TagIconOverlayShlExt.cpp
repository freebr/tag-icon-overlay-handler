// TagIconOverlayShlExt.cpp : CTagIconOverlayShlExt µÄÊµÏÖ

#include "stdafx.h"
#include "TagIconOverlayShlExt.h"
#include "TagDataReader.h"

// CTagIconOverlayShlExt

STDMETHODIMP CTagIconOverlayShlExt::IsMemberOf(THIS_ _In_ PCWSTR pwszPath, DWORD dwAttrib)
{
	if (dwAttrib & SFGAO_FOLDER) return S_FALSE;
	LPWSTR ext = PathFindExtension(pwszPath);
	for (int i = 0; i < _countof(extensions); ++i) {
		if (_tcscmp(ext, extensions[i]) == 0)
		{
			CTagDataReader* reader = new CTagDataReader();
			if (reader->detectTagData(pwszPath)) return S_OK;
			reader = NULL;
			return S_FALSE;
		}
	}
	return S_FALSE;
}

STDMETHODIMP CTagIconOverlayShlExt::GetOverlayInfo(THIS_ _Out_writes_(cchMax) PWSTR pwszIconFile,
	int cchMax, _Out_ int* pIndex, _Out_ DWORD* pdwFlags)
{
	GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), pwszIconFile, cchMax);
	*pIndex = 0;	// 128*128
	*pdwFlags = ISIOI_ICONFILE | ISIOI_ICONINDEX;
	return S_OK;
}

STDMETHODIMP CTagIconOverlayShlExt::GetPriority(THIS_ _Out_ int* pIPriority)
{
	*pIPriority = 0;
	return S_OK;
}
