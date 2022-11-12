

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for TagIconOverlayHandler.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __TagIconOverlayHandler_i_h__
#define __TagIconOverlayHandler_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITagIconOverlayShlExt_FWD_DEFINED__
#define __ITagIconOverlayShlExt_FWD_DEFINED__
typedef interface ITagIconOverlayShlExt ITagIconOverlayShlExt;

#endif 	/* __ITagIconOverlayShlExt_FWD_DEFINED__ */


#ifndef __TagIconOverlayShlExt_FWD_DEFINED__
#define __TagIconOverlayShlExt_FWD_DEFINED__

#ifdef __cplusplus
typedef class TagIconOverlayShlExt TagIconOverlayShlExt;
#else
typedef struct TagIconOverlayShlExt TagIconOverlayShlExt;
#endif /* __cplusplus */

#endif 	/* __TagIconOverlayShlExt_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITagIconOverlayShlExt_INTERFACE_DEFINED__
#define __ITagIconOverlayShlExt_INTERFACE_DEFINED__

/* interface ITagIconOverlayShlExt */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITagIconOverlayShlExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C339978C-9102-424E-8188-D35A7597BEDD")
    ITagIconOverlayShlExt : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct ITagIconOverlayShlExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITagIconOverlayShlExt * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITagIconOverlayShlExt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITagIconOverlayShlExt * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITagIconOverlayShlExt * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITagIconOverlayShlExt * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITagIconOverlayShlExt * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITagIconOverlayShlExt * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } ITagIconOverlayShlExtVtbl;

    interface ITagIconOverlayShlExt
    {
        CONST_VTBL struct ITagIconOverlayShlExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITagIconOverlayShlExt_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITagIconOverlayShlExt_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITagIconOverlayShlExt_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITagIconOverlayShlExt_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITagIconOverlayShlExt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITagIconOverlayShlExt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITagIconOverlayShlExt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITagIconOverlayShlExt_INTERFACE_DEFINED__ */



#ifndef __TagIconOverlayHandlerLib_LIBRARY_DEFINED__
#define __TagIconOverlayHandlerLib_LIBRARY_DEFINED__

/* library TagIconOverlayHandlerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_TagIconOverlayHandlerLib;

EXTERN_C const CLSID CLSID_TagIconOverlayShlExt;

#ifdef __cplusplus

class DECLSPEC_UUID("33177D20-AAE9-4D63-AD9E-86BF0377F923")
TagIconOverlayShlExt;
#endif
#endif /* __TagIconOverlayHandlerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


