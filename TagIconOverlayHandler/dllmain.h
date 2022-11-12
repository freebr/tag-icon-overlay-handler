// dllmain.h : 模块类的声明。

class CTagIconOverlayHandlerModule : public ATL::CAtlDllModuleT< CTagIconOverlayHandlerModule >
{
public :
	DECLARE_LIBID(LIBID_TagIconOverlayHandlerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TAGICONOVERLAYHANDLER, "{FF226B45-46A7-4616-BFEB-0214B46869D9}")
};

extern class CTagIconOverlayHandlerModule _AtlModule;
