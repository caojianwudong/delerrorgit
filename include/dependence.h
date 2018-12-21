#ifndef __DEPENDENCE_H
#define __DEPENDENCE_H

#if _MSC_VER>=1800
#include <xkeycheck.h>
#endif
#include <stdio.h>

#ifdef _DEBUG
#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif
#include <CRTDBG.H>
#define xnew new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define xnew new
#endif

/************************************************************************/
// 关键字空指针定义
#ifndef nullptr
#ifndef NULL
    #define NULL 0
#endif
#define nullptr NULL
#endif // nullptr

/************************************************************************/
// 数组数目统计宏

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

#ifndef offsetof
#define offsetof(s,m)   (size_t)&(((s *)0)->m)
#endif // offsetof

#ifndef argb
#define argb(a, r, g, b)    ( unsigned char(b)|(unsigned char(g)<<8)|(unsigned char(r)<<16)|(unsigned char(a)<<24))
#endif

/************************************************************************/
// 调试类宏定义
#ifndef __debug_break
#ifdef _DEBUG
#define __debug_break()  _asm{int 0x03};
#else
#define __debug_break()
#endif
#endif // __debugbreak


#ifndef __debug_assert
#ifdef _DEBUG
#define __debug_assert(x)  if (!(x)) { __debug_break(); }
#else
#define __debug_assert(x)
#endif
#endif // __debug_assert

#ifndef __debug_verify
#ifdef _DEBUG
#define __debug_verify(x)  if (!(x)) { __debug_break(); }
#else
#define __debug_verify(x)  (x);
#endif
#endif // __debug_assert



#ifndef __debug_comptr
#ifdef _DEBUG
#define __debug_comptr(hr) if ( FAILED(hr) ) { __debug_break(); }
#else
#define __debug_comptr(hr) if ( FAILED(hr) ) { _com_issue_error(hr); } 
#endif
#endif // __debug_assert

/************************************************************************/
// 字符串同步

#if defined(UNICODE) || defined(_UNICODE)

#ifndef xchar
#define xchar   wchar_t
#endif

#ifndef xstring
#define xstring std::wstring
#endif 
#else

#ifndef xchar
#define xchar   char
#endif

#ifndef xstring
#define xstring std::string
#endif 

#endif

/************************************************************************/
// 简化式if...else...end语句

#ifndef IFELSEND
#define IFELSEND(b, t, f) if (b) { t; } else { f; }
#endif  IFELSEND

/************************************************************************/

#ifndef getInt64FromVar
#if _MSC_VER<1300
#define getInt64FromVar(var) __getInt64FromVar(var)
#else   // _MSC_VER
#define getInt64FromVar(var) var
#endif // _MSC_VER
#endif //getInt64FromVar

#ifndef getVarFromInt64
#if _MSC_VER<1300
#define getVarFromInt64(i8) __getVarFromInt64(i8)
#else   // _MSC_VER
#define getVarFromInt64(i8) i8
#endif // _MSC_VER
#endif //getVarFromInt64

#ifndef getVarFromVariant
#if _MSC_VER>=1500
#define getVarFromVariant(var) var.GetVARIANT()
#else   // _MSC_VER
#define getVarFromVariant(var) var
#endif // _MSC_VER
#endif //getVarFromVariant

#ifndef getBSTRFromVar
#if _MSC_VER>=1500
#define getBSTRFromVar(var) _bstr_t(var).Detach()
#else   // _MSC_VER
#define getBSTRFromVar(var) __getBSTRFromVar(var)
#endif // _MSC_VER
#endif //getVarFromVariant

#ifndef getVarFromBSTR
#define getVarFromBSTR(bstr, byref) __getVarFromBSTR(bstr, byref)
#endif

/************************************************************************/

template<bool nocase> struct strless { };

template<> struct strless<false>
{
    bool operator()(LPCSTR k, LPCSTR v) const
    { return lstrcmpA(k, v)<0; }

    bool operator()(LPCWSTR k, LPCWSTR v) const
    { return lstrcmpW(k, v)<0; }
    
#ifdef _STRING_
    bool operator()(const std::string & k, LPCSTR v) const
    { return lstrcmpA(k.c_str(), v)<0; }
    
    bool operator()(LPCSTR k, const std::string & v) const
    { return lstrcmpA(k, v.c_str())<0; }
    
    bool operator()(const std::string & k, const std::string & v) const
    { return lstrcmpA(k.c_str(), v.c_str())<0; }

    bool operator()(const std::wstring & k, LPCWSTR v) const
    { return lstrcmpW(k.c_str(), v)<0; }
    
    bool operator()(LPCWSTR k, const std::wstring & v) const
    { return lstrcmpW(k, v.c_str())<0; }
    
    bool operator()(const std::wstring & k, const std::wstring & v) const
    { return lstrcmpW(k.c_str(), v.c_str())<0; }
#endif //_STRING_

#ifdef _INC_COMUTIL
    bool operator()(const _bstr_t & k, const _bstr_t & v) const
    {
        return lstrcmpW(k, v)<0; 
    }
#endif // _INC_COMUTIL
};

template<> struct strless<true>
{
    bool operator()(LPCSTR k, LPCSTR v) const
    { return lstrcmpiA(k, v)<0; }

    bool operator()(LPCWSTR k, LPCWSTR v) const
    { return lstrcmpiW(k, v)<0; }
    
#ifdef _STRING_
    bool operator()(const std::string & k, LPCSTR v) const
    { return lstrcmpiA(k.c_str(), v)<0; }
    
    bool operator()(LPCSTR k, const std::string & v) const
    { return lstrcmpiA(k, v.c_str())<0; }
    
    bool operator()(const std::string & k, const std::string & v) const
    { return lstrcmpiA(k.c_str(), v.c_str())<0; }
    
    bool operator()(const std::wstring & k, LPCWSTR v) const
    { return lstrcmpiW(k.c_str(), v)<0; }
    
    bool operator()(LPCWSTR k, const std::wstring & v) const
    { return lstrcmpiW(k, v.c_str())<0; }
    
    bool operator()(const std::wstring & k, const std::wstring & v) const
    { return lstrcmpiW(k.c_str(), v.c_str())<0; }
#endif //_STRING_
    
#ifdef _INC_COMUTIL
    bool operator()(const _bstr_t & k, const _bstr_t & v) const
    {
        return lstrcmpiW(k, v)<0; 
    }
#endif // _INC_COMUTIL
};

template <class _Tkey, class _Tval>
struct Keyval{
    _Tkey first;
    _Tval second;
};


template<class _Keyval, bool nocase>
struct keyless
    : public strless<nocase>
{
    bool operator()(const _Keyval & k, LPCSTR v) const
    { return strless<nocase>::operator()(k.first, v); }
    
    bool operator()(LPCSTR k, const _Keyval & v) const
    { return strless<nocase>::operator()(k, v.first); }
    
    bool operator()(const _Keyval & k, const _Keyval & v) const
    { return strless<nocase>::operator()(k.first, v.first); }

    bool operator()(const _Keyval & k, LPCWSTR v) const
    { return strless<nocase>::operator()(k.first, v); }
    
    bool operator()(LPCWSTR k, const _Keyval & v) const
    { return strless<nocase>::operator()(k, v.first); }
};


template <class _Ty, class _Key, class _Ptr>
unsigned sortedfind(const _Key & key, const _Ty * pv, unsigned n, const _Ptr & cmp)
{
    unsigned m = n>>1;
    
    for(unsigned s = 0, e = n; s<e;  m = (s+e)>>1)
    {
        IFELSEND(cmp(pv[m].first, key), s=++m, e = m);
    }
    
    return ( m==n || cmp(key, pv[m].first)) ? n : m;
}

template <class _Ty, class _Key>
unsigned sortedfind(const _Key & key, const _Ty * pv, unsigned n)
{
    unsigned m = n>>1;
    
    for(unsigned s = 0, e = n; s<e;  m = (s+e)>>1)
    {
        IFELSEND(pv[m].first<key, s=++m, e = m);
    }
    
    return ( m==n || pv[m].first>key) ? n : m;
}

/************************************************************************/

#ifndef IFELSEND
#define IFELSEND(b, t, f) if (b) { t; } else { f; }
#endif  IFELSEND

/************************************************************************/
// 模块函数

#ifdef _COM_SMARTPTR_TYPEDEF
typedef IUnknownPtr CComLibrary;
#endif

class modules;

#ifdef _INC_COMUTIL
// 载入当前的DLL模块
// (obsoleted), see as LoadDLLModule
modules * LoadDLL(const _bstr_t & dllpath);
#endif // _INC_COMUTIL

// 获取当前模块管理对象
modules *  GetModules(); 

#if defined(UNICODE) || defined(_UNICODE)
#define  LoadDLLModule LoadDLLModuleW
#else
#define  LoadDLLModule LoadDLLModuleA
#endif

// 载入模块
HMODULE    LoadDLLModuleA(LPCSTR dllpath);

// 载入模块
HMODULE    LoadDLLModuleW(LPCWSTR dllpath);

// 获取模块目录
BSTR       GetModuleFolder(HMODULE hModule);

/************************************************************************/
// 字符转化及格式化
#
#ifndef _MAX_STRBUF_ 
#define _MAX_STRBUF_  1024
#endif 

BSTR ATOW(const char * pstr, size_t n = -1, long codepage = CP_ACP);

BSTR WTOA(const wchar_t * pstr, size_t n = -1, long codepage = CP_ACP);

BSTR xcloadA(HMODULE hMoudle, UINT uID);

BSTR xcloadW(HMODULE hMoudle, UINT uID);

BSTR xcprintfA(const char * pstr, ...);

BSTR xcprintfW(const wchar_t * pstr, ...);

BSTR xcformatA(HMODULE hMoudle, UINT uID, ...);

BSTR xcformatW(HMODULE hMoudle, UINT uID, ...);

BSTR _vxcprintfA(const char * pstr, va_list args);

BSTR _vxcprintfW(const wchar_t * pstr, va_list args);

#ifndef _xbs
#define _xbs(x) _bstr_t(x, false)
#endif // 


#if defined(UNICODE) || defined(_UNICODE)
#define  xctobstr   xctobstrW
#define  xcprintf   xcprintfW
#define  xcformat   xcformatW
#define  _vxcprintf _vxcprintfW
#else
#define  xctobstr   xctobstrA
#define  xcprintf   xcprintfA
#define  xcformat   xcformatA
#define  _vxcprintf _vxcprintfA
#endif

#ifdef _STRING_

std::wstring mbstowcs(const char * pstr, size_t n = -1, long codepage = CP_ACP);

std::string  wcstombs(const wchar_t * pstr, size_t n = -1, long codepage = CP_ACP);

std::string  xsloadA(HMODULE hMoudle, UINT uID);

std::wstring xsloadW(HMODULE hMoudle, UINT uID);

std::string  xsprintfA(const char * pstr, ...);

std::wstring xsprintfW(const wchar_t * pstr, ...);

std::string  xsformatA(HMODULE hMoudle, UINT uID, ...);

std::wstring xsformatW(HMODULE hMoudle, UINT uID, ...);

std::string  _vxsprintfA(const char * pstr, va_list args);

std::wstring _vxsprintfW(const wchar_t * pstr, va_list args);

#if defined(UNICODE) || defined(_UNICODE)
#define  xsload     xsloadW
#define  xsprintf   xsprintfW
#define  xsformat   xsformatW
#define  _vxsprintf _vxsprintfW
#else
#define  xsload     xsloadA
#define  xsprintf   xsprintfA
#define  xsformat   xsformatA
#define  _vxsprintf _vxsprintfA
#endif

#endif _STRING_

/************************************************************************/
// 错误处理

#if defined(_INC_COMDEF) && defined(__test_error)
#define __raise_error(hr, errinfo) _com_raise_error(hr, errinfo);
#else
#define __raise_error(hr, errinfo)
#endif 

// 产生错误
#ifndef __strap_error
#define __strap_error(hr, desc) (hr!=S_OK) ? __straperr(hr, desc, __FILE__, __LINE__) : hr
#endif // __strap_error

#ifndef __built_error
#define __built_error(hr, desc) __builterr(hr, (LPCWSTR)desc, __FILE__, __LINE__)
#endif // __built_error

// 传递错误
#ifndef __dispatch_error
#define __dispatch_error(hr) \
do { HRESULT hres = (hr);  if (FAILED(hres)) {  \
__raise_error(hres, __fetcherr(hres));  return hres; } } while (0); 
#endif //__dispatch_error

#ifndef __ignore_error
#define __ignore_error(hr) __fetcherr(hr)
#endif // __fetch_error


/************************************************************************/
// 后续为定义实现代码, 请忽略
/************************************************************************/

#ifndef __COMMODULE_H
#define __COMMODULE_H

class modules : public IUnknown
{
protected:
    
    typedef STDMETHODIMP STDFUN(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
    
    LONG        m_ulRef; 
    
    struct MStack
    {
        HMODULE     hModule;
        STDFUN *    hCallback;
        MStack *    pPrevious;
    } m_Tailer;
    
protected:
    
    modules(long initref = 0) : m_ulRef(initref)
    {
        m_Tailer.hModule     = nullptr;
        m_Tailer.hCallback   = nullptr;
        m_Tailer.pPrevious   = nullptr;
    }

public:

    modules(LPCWSTR lpszDLLPath) : m_ulRef(0)
    {
        m_Tailer.hCallback   = nullptr;
        m_Tailer.pPrevious   = nullptr;
        m_Tailer.hModule     = Load(lpszDLLPath);
    }

    modules(LPCSTR lpszDLLPath) : m_ulRef(0)
    {
        m_Tailer.hModule     = nullptr;
        m_Tailer.hCallback   = nullptr;
        m_Tailer.pPrevious   = nullptr;
        BSTR str = ATOW(lpszDLLPath);
        Load(str);
        ::SysFreeString(str);
    }

public:
    
    ~modules()
    {
        MStack * pLast;
        while( (pLast= m_Tailer.pPrevious)!=nullptr )
        {
            ::CoFreeLibrary(pLast->hModule); 
            m_Tailer.pPrevious = pLast->pPrevious;
            delete pLast;
        }
#ifdef _INC_CRTDBG
        _CrtDumpMemoryLeaks();
#endif
    }
    
public:
    
    inline static modules * GetUserModules()
    {
        static modules module(1);
        return &module;
    }

    inline static void SetCurrent(HMODULE hMoudle, STDFUN * pDLLExport = nullptr)
    {
        modules * pmoudle = GetUserModules();
        pmoudle->m_Tailer.hModule    = hMoudle;
        pmoudle->m_Tailer.hCallback  = pDLLExport;
    }
    
    inline static HMODULE GetCurrent() 
    { 
        return GetUserModules()->m_Tailer.hModule;
    }   
    
public:
    
    HMODULE Load(LPCWSTR dllpath)
    {
        HMODULE hModule = ::LoadLibraryW(dllpath);
        if (hModule==nullptr)
        {
            WCHAR szbuf[MAX_PATH];
            wsprintfW(szbuf, L"载入组件失败, 组件路径:%s", dllpath);
            MessageBoxW(NULL, szbuf, L"错误", MB_OK|MB_ICONERROR);
            return nullptr;
        }
        
        FARPROC hCallback = GetProcAddress(hModule, "DllGetClassObject");
        if (hCallback==nullptr)
        {
            WCHAR szbuf[MAX_PATH];
            wsprintfW(szbuf, L"无法定位组件入口, 组件路径:%s", dllpath);
            MessageBoxW(NULL, szbuf, L"错误", MB_OK|MB_ICONERROR);
            ::CoFreeLibrary(hModule); 
            return nullptr;
        }
        
        MStack * pStack = xnew MStack;
        pStack->hModule   = hModule;
        pStack->hCallback = (STDFUN *)hCallback;
        pStack->pPrevious = m_Tailer.pPrevious;
        m_Tailer.pPrevious = pStack;
        return hModule;
    }
    
    void Unload(HMODULE hModule)
    {
        MStack  * previous = &m_Tailer, * current;
        while( (current = previous->pPrevious)!=nullptr
            && current->hModule!=hModule)
        {
            previous = current;
        }

        if (current!=nullptr)
        {
            ::CoFreeLibrary(current->hModule);
            previous->pPrevious = current->pPrevious;
            delete current;
        }
    }
    
public:
    
    STDMETHODIMP GetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
    {
        HRESULT hr = CLASS_E_CLASSNOTAVAILABLE;
        MStack * pPrev = m_Tailer.pPrevious;
        while( FAILED(hr) && pPrev!=nullptr)
        {
            hr =  (*pPrev->hCallback)(rclsid, riid, ppv); 
            pPrev = pPrev->pPrevious;
        }
        return hr;
    }
    
    STDMETHODIMP QueryInterface(REFIID riid, void **ppvo)
    { 
        if (IsEqualIID(riid, IID_IUnknown))
        { 
            *ppvo = this; AddRef(); return S_OK;
        }

        return (m_Tailer.hCallback!=nullptr) 
            ? (*m_Tailer.hCallback)(IID_IUnknown, riid, ppvo)
            : GetClassObject(IID_IUnknown, riid, ppvo);
    }
    
    virtual ULONG STDMETHODCALLTYPE AddRef(void)
    {
        return ::InterlockedIncrement(&m_ulRef);
    }
    
    virtual ULONG STDMETHODCALLTYPE Release(void)
    {
        if (::InterlockedDecrement(&m_ulRef)!=0)
        { 
            return m_ulRef; 
        }
        delete this;
        return 0;
    }
};

#endif // __COMMODULE_H

/************************************************************************/
// 模块函数

inline modules *  GetModules()
    { return modules::GetUserModules(); }

#ifdef _INC_COMUTIL
inline modules * LoadDLL(const _bstr_t & dllpath)
    { return (LoadDLLModule(dllpath)!=nullptr) ? GetModules() : nullptr; }
#endif

inline HMODULE LoadDLLModuleW(LPCWSTR dllpath)
    { return GetModules()->Load(dllpath); }

inline HMODULE LoadDLLModuleA(LPCSTR dllpath)
    {
       BSTR tmp = ATOW(dllpath);
       HMODULE retval = LoadDLLModuleW(tmp);
       ::SysFreeString(tmp);
       return retval;
    }

inline BSTR GetModuleFolder(HMODULE hModudle)
{
    wchar_t tmp[_MAX_STRBUF_];
    int ret = ::GetModuleFileNameW(hModudle, tmp, _countof(tmp));    
    if (ret<_countof(tmp)) { 
		while ((ret-->0)&& (tmp[ret] != '\\' && tmp[ret] != '/'));
		return ::SysAllocStringLen(tmp, ++ret);
	}
    
    int  wlength = _countof(tmp)<<1;
    BSTR retval = ::SysAllocStringLen(nullptr, wlength);
    
    while( (retval!=nullptr) 
        && (ret=::GetModuleFileNameW(hModudle, retval, wlength))>=wlength
        && (::SysReAllocStringLen(&retval, nullptr, wlength<<=1)) );
    
    // 获取路径的目录位置
    while ((ret-->0)&& (retval[ret] != '\\' && retval[ret] != '/'));
    
    if (  (retval!=nullptr) || ret<wlength
        || !::SysReAllocStringLen(&retval, retval, ++ret)) 
    {
        ::SysFreeString(retval); retval = nullptr;
    }
    
    return retval;
}

/************************************************************************/

// 字符处理
inline BSTR ATOW(const char * s, size_t n, long c)
{
    BSTR r = nullptr;
    if (n == -1) { n = (s != nullptr) ? strlen(s) : 0 ; }
    size_t l = ::MultiByteToWideChar(c, 0, s, n, NULL, 0);
    
    if ( l!=0 && (r= ::SysAllocStringLen(nullptr, l))!=nullptr )
    {
        ::MultiByteToWideChar(c, 0, s, n, r, l);
    }
    
    return r;
}

inline BSTR WTOA(const wchar_t * s, size_t n, long c)
{
    BSTR r = nullptr;
    if (n == -1) { n = (s != nullptr) ? wcslen(s) : 0; }   
    
    size_t l = ::WideCharToMultiByte(c, 0,
        s, n, nullptr, 0, nullptr, nullptr);

    if ( l!=0 && (r= ::SysAllocStringByteLen(nullptr, l))!=nullptr )
    {
        ::WideCharToMultiByte(
            c, 0, s, n, (LPSTR)r, l, nullptr, nullptr);
    }

    return r;
}

inline BSTR xcloadW(HMODULE hMoudle, UINT uID)
{
    BSTR    retval = nullptr;
    HRSRC   hRSRC = ::FindResource(hMoudle,
        MAKEINTRESOURCE(((uID >> 4) + 1)), RT_STRING);
    HGLOBAL hMem  = ::LoadResource(hMoudle, hRSRC);
    LPCWSTR pStr = (LPCWSTR)::LockResource(hMem);
    
    if (pStr!=nullptr)
    {
        for (UINT i = (uID >> 4) << 4; i < uID; ++i)
        {
            pStr += *(pStr++);
        }
        
        retval = ::SysAllocStringLen(pStr+1, *pStr);
        UnlockResource(hMem);
    }
    ::FreeResource(hRSRC);
    return retval;
}

inline BSTR xcloadA(HMODULE hMoudle, UINT uID)
{
    BSTR    retval = nullptr;
    HRSRC   hRSRC = ::FindResource(hMoudle,
        MAKEINTRESOURCE(((uID >> 4) + 1)), RT_STRING);
    HGLOBAL hMem  = ::LoadResource(hMoudle, hRSRC);
    LPCWSTR pStr = (LPCWSTR)::LockResource(hMem);
    
    if (pStr!=nullptr)
    {
        for (UINT i = (uID >> 4) << 4; i < uID; ++i)
        {
            pStr += *(pStr++);
        }
        
        retval = WTOA(pStr+1, *pStr);
        UnlockResource(hMem);
    }
    ::FreeResource(hRSRC);
    return retval;
}

inline BSTR xcloadA(UINT uID)
{ 
    return xcloadA(modules::GetCurrent(), uID); 
}

inline BSTR xcloadW(UINT uID)
{ 
    return xcloadW(modules::GetCurrent(), uID); 
}

inline BSTR xcprintfA(const char * f, ...)
{
    va_list a; va_start(a, f);
    BSTR r = _vxcprintfA(f, a);
    va_end(a); return r;
}

inline BSTR xcprintfW(const wchar_t * f, ...)
{
    va_list a; va_start(a, f);
    BSTR r = _vxcprintfW(f, a);
    va_end(a); return r;
}

inline BSTR xcprintfA(UINT uID, ...)
{
    BSTR retval= nullptr, p = xcloadA(uID);    
    if (p!=nullptr)
    {
        va_list a; 
        va_start(a, uID);            
        retval = _vxcprintfA((const char *)p, a);
        va_end(a);
        ::SysFreeString(p);
    }
    return retval;
}

inline BSTR xcprintfW(UINT uID, ...)
{
    BSTR retval= nullptr, p = xcloadW(uID);
    if (p!=nullptr)
    {
        va_list a; 
        va_start(a, uID);            
        retval = _vxcprintfW(p, a);
        va_end(a);
        ::SysFreeString(p);
    }
    return retval;
}

inline BSTR xcformatA(HMODULE hMoudle, UINT uID, ...)
{
    BSTR retval= nullptr, p = xcloadA(hMoudle, uID);    
    if (p!=nullptr)
    {
        va_list a; 
        va_start(a, uID);            
        retval = _vxcprintfA((const char *)p, a);
        va_end(a);
        ::SysFreeString(p);
    }
    return retval;
}

inline BSTR xcformatW(HMODULE hMoudle, UINT uID, ...)
{
    BSTR retval= nullptr, p = xcloadW(hMoudle, uID);
    if (p!=nullptr)
    {
        va_list a; 
        va_start(a, uID);            
        retval = _vxcprintfW(p, a);
        va_end(a);
        ::SysFreeString(p);
    }
    return retval;
}

// _vsnprintf/_vsnwprintf函数测试: 
//    1. 缓存大小 < 字符长度, 返回-1
//    2. 缓存大小 = 字符长度, 不输出'\0',返回字符长度
//    3. 缓存大小 > 字符长度, 输出'\0',返回字符长度

#if _MSC_VER<1300

inline BSTR _vxcprintfA(const char * f, va_list a)
{
    char t[_MAX_STRBUF_];
    int n = _vsnprintf(t, _countof(t), f, a);

    if (n > 0) { return ::SysAllocStringByteLen(t, n); }
    if (n!=-1) { return nullptr; }

    int x = _countof(t);
    BSTR r = ::SysAllocStringLen(nullptr, x);    
    while ((r!=nullptr)
        && (-1==(n=_vsnprintf((char *)r, (x<<=1), f, a)))
        && (::SysReAllocStringLen(&r, nullptr, x)));
    
    if ( r==nullptr || ( n>0 && ::SysReAllocStringLen(&r, r, (++n)>>1)) )
    {
        return r;
    }

    ::SysFreeString(r); return nullptr;
}

inline BSTR _vxcprintfW(const wchar_t * f, va_list a)
{
    wchar_t t[_MAX_STRBUF_];
    int n = _vsnwprintf(t, _countof(t), f, a);
    
    if (n > 0) { return ::SysAllocStringLen(t, n); }
    if (n!=-1) { return nullptr; }
    
    int x = _countof(t)<<1;
    BSTR r = ::SysAllocStringLen(nullptr, x);
    
    while ((r!=nullptr)
        && (-1==(n=_vsnwprintf(r, x, f, a)))
        && (::SysReAllocStringLen(&r, nullptr, x<<=1)));
    
    if ( r==nullptr || ( n>0 && ::SysReAllocStringLen(&r, r, n)) )
    {
        return r;
    }
    
    ::SysFreeString(r); return nullptr;
}

#else // _MSC_VER<1300

inline BSTR _vxcprintfA(const char * f, va_list a)
{
    char t[_MAX_STRBUF_];
#if _MSC_VER<1500
    int n = _vsnprintf(t, _countof(t), f, a);
#else
    int n = _vsnprintf_s(t, _countof(t), _countof(t) - 1, f, a);
#endif
    
    if (n > 0) { return ::SysAllocStringByteLen(t, n); }
    if (n!=-1) { return nullptr; }
    
    BSTR r = ::SysAllocStringByteLen(nullptr, n = _vscprintf(f, a));  
#if _MSC_VER<1500
    if ( r!=nullptr && (_vsnprintf((char *)r, n, f, a) < 0) )
#else
    if (r != nullptr && (_vsnprintf_s((char *)r, n+1, n, f, a) < 0))
#endif
    {
        ::SysFreeString(r); return nullptr;
    }
    return r;
}

inline BSTR _vxcprintfW(const wchar_t * f, va_list a)
{
    wchar_t t[_MAX_STRBUF_];
#if _MSC_VER<1500
    int n = _vsnwprintf(t, _countof(t), f, a);
#else
    int n = _vsnwprintf_s(t, _countof(t), _countof(t)-1, f, a);
#endif
    
    if (n > 0) { return ::SysAllocStringLen(t, n); }
    if (n!=-1) { return nullptr; }

    BSTR r = ::SysAllocStringLen(nullptr, n = _vscwprintf(f, a));
#if _MSC_VER<1500
    if (r != nullptr && (_vsnwprintf(r, n, f, a) < 0))
#else
    if (r != nullptr && (_vsnwprintf_s(r, n+1, n, f, a) < 0))
#endif
    {
        ::SysFreeString(r); return nullptr;
    }
    return r;
}

#endif

#ifdef _STRING_

inline std::wstring mbstowcs(const char * s, size_t n, long c)
{
   if (n == -1) { n = (s != nullptr) ? strlen(s) : 0; }

    std::wstring r(::MultiByteToWideChar(c, 0, s, n, nullptr, 0), 0);
    if ( !r.empty() )
    {
        ::MultiByteToWideChar(c, 0,
            s, n, &(*r.begin()), r.length());
    }
    return r;
}

inline std::string wcstombs(const wchar_t * s, size_t n, long c)
{
    if (n == -1) { n = (s != nullptr) ? wcslen(s) : 0; }
    
    std::string r(::WideCharToMultiByte(
        c, 0, s, n, nullptr, 0, nullptr, nullptr), 0);
    
    if ( !r.empty() )
    {
        ::WideCharToMultiByte(
            c, 0, s, n, &(*r.begin()), r.length(), nullptr, nullptr);
    }
    return r;
}

inline std::string xsloadA(HMODULE hMoudle, UINT uID)
{
    std::string retval;
    HRSRC   hRSRC = ::FindResource(hMoudle,
        MAKEINTRESOURCE(((uID >> 4) + 1)), RT_STRING);
    HGLOBAL hMem  = ::LoadResource(hMoudle, hRSRC);
    LPCWSTR pStr = (LPCWSTR)::LockResource(hMem);
    
    if (pStr!=nullptr)
    {
        for (UINT i = (uID >> 4) << 4; i < uID; ++i)
        {
            pStr += *(pStr++);
        }
        
        retval = wcstombs(pStr+1, *pStr);
        UnlockResource(hMem);
    }
    ::FreeResource(hRSRC);
    return retval;
}

inline std::string xsloadA(UINT uID)
{
    return xsloadA(modules::GetCurrent(), uID);
}

inline std::wstring xsloadW(HMODULE hMoudle, UINT uID)
{
    std::wstring retval;
    HRSRC   hRSRC = ::FindResource(hMoudle,
        MAKEINTRESOURCE(((uID >> 4) + 1)), RT_STRING);
    HGLOBAL hMem  = ::LoadResource(hMoudle, hRSRC);
    LPCWSTR pStr = (LPCWSTR)::LockResource(hMem);
    
    if (pStr!=nullptr)
    {
        for (UINT i = (uID >> 4) << 4; i < uID; ++i)
        {
            pStr += *(pStr++);
        }
        
        retval.assign(pStr+1, *pStr);
        UnlockResource(hMem);
    }
    ::FreeResource(hRSRC);
    return retval;
}

inline std::wstring xsloadW(UINT uID)
{
    return xsloadW(modules::GetCurrent(), uID);
}

inline std::string xsprintfA(const char * f, ...)
{
    va_list a; va_start(a, f); 
    std::string r = _vxsprintfA(f, a);
    va_end(a); return r;
}

inline std::wstring xsprintfW(const wchar_t * f, ...)
{
    va_list a; va_start(a, f); 
    std::wstring r = _vxsprintfW(f, a);
    va_end(a); return r;
}

inline std::string xsprintfA(UINT uID, ...)
{
    std::string retval = xsloadA(modules::GetCurrent(), uID);
    if (!retval.empty())
    {
        va_list a; va_start(a, uID);
        retval = _vxsprintfA(retval.c_str(), a);
        va_end(a); 
    }
    return retval;
}

inline std::wstring xsprintfW(UINT uID, ...)
{
    std::wstring retval, p = xsloadW(uID);
    if (!p.empty())
    {
        va_list a; va_start(a, uID);
        retval = _vxsprintfW(p.c_str(), a);
        va_end(a); 
    }
    return retval;
}

inline std::string xsformatA(HMODULE hMoudle, UINT uID, ...)
{
    std::string retval = xsloadA(hMoudle, uID);
    if (!retval.empty())
    {
        va_list a; va_start(a, uID);
        retval = _vxsprintfA(retval.c_str(), a);
        va_end(a); 
    }
    return retval;
}

inline std::wstring xsformatW(HMODULE hMoudle, UINT uID, ...)
{
    std::wstring retval, p = xsloadW(hMoudle, uID);
    if (!p.empty())
    {
        va_list a; va_start(a, uID);
        retval = _vxsprintfW(p.c_str(), a);
        va_end(a); 
    }
    return retval;
}

#if _MSC_VER<1300

inline std::string _vxsprintfA(const char * f, va_list a)
{
    // 不使用 std::string 测试长度
    BSTR rbyte = _vxcprintfA(f, a);
    if (rbyte==nullptr) { return std::string(); }
    
    std::string r((char *)rbyte);
    ::SysFreeString(rbyte);
    return r;
}

inline std::wstring _vxsprintfW(const wchar_t * f, va_list a)
{
    // 不使用 std::string 测试长度
    BSTR rwide = _vxcprintfW(f, a);
    if (rwide==nullptr) { return std::wstring(); }

    std::wstring r(rwide);
    ::SysFreeString(rwide);
    return r;
}

#else // _MSC_VER<1300

inline std::string _vxsprintfA(const char * f, va_list a)
{
    char t[_MAX_STRBUF_];
#if _MSC_VER<1500
    int n = _vsnprintf(t, _countof(t), f, a);
#else
    int n = _vsnprintf_s(t, _countof(t), _countof(t) - 1, f, a);
#endif
    
    if (n > 0) { return std::string(t, n); }
    if (n!=-1) { return std::string();     }
    
    std::string r(n = _vscprintf(f, a), 0);

#if _MSC_VER<1500
    if (!r.empty() && (_vsnprintf(&(*r.begin()), n, f, a) < 0))
#else
    if (!r.empty() && (_vsnprintf_s(&(*r.begin()), n+1, n, f, a) < 0))
#endif
    {
        r.clear();
    }
    return r;
}

inline std::wstring _vxsprintfW(const wchar_t * f, va_list a)
{
    wchar_t t[_MAX_STRBUF_];
#if _MSC_VER<1500
    int n = _vsnwprintf(t, _countof(t), f, a);
#else
    int n = _vsnwprintf_s(t, _countof(t), _countof(t) - 1, f, a);
#endif
    
    if (n > 0) { return std::wstring(t, n); }
    if (n!=-1) { return std::wstring();     }
    
    std::wstring r(n = _vscwprintf(f, a), 0);

#if _MSC_VER<1500
    if (!r.empty() && (_vsnwprintf(&(*r.begin()), n, f, a) < 0))
#else
    if (!r.empty() && (_vsnwprintf_s(&(*r.begin()), n + 1, n, f, a) < 0))
#endif
    {
        r.clear();
    }
    return r;
}

#endif // _MSC_VER<1300

#endif _STRING_

/************************************************************************/
inline IErrorInfo * __fetcherr(HRESULT hr)
{
  IErrorInfo * pError = nullptr;
  if (FAILED(hr)) { GetErrorInfo(0, &pError); }
  return pError;
}

inline IErrorInfo * __builterr(HRESULT hr, LPCWSTR description, LPCSTR file, long line)
{
    IErrorInfo * pret = NULL;
    ICreateErrorInfo * creator = NULL;
    if (SUCCEEDED(::CreateErrorInfo(&creator)))
    {
        creator->SetHelpContext(hr);
        if (file != NULL) 
        { 
            BSTR fileline = xcprintfW(L"%hs, at Line:%d", file, line);
            creator->SetSource(fileline);
            ::SysFreeString(fileline);
        }
        
        if (description != NULL)
        {
            creator->SetDescription((LPOLESTR)description);
        }
        else
        {
            LPOLESTR pszMsg = NULL;
            DWORD lenMsg = ::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                hr,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPOLESTR)&pszMsg,
                0,
                NULL);
            
            if (lenMsg != 0) { creator->SetDescription(pszMsg);}
            ::LocalFree(pszMsg);
        }
        
        creator->QueryInterface(&pret);
        creator->Release();
    }
    return pret;
}

// 设置错误信息
inline HRESULT __straperr(HRESULT hr, 
                          LPCWSTR description,
                          LPCSTR file, 
                          long line)
{
    IErrorInfo * pret = __builterr(hr, description, file, line);
    if (pret!=nullptr)
    {
        ::SetErrorInfo(0, pret);
        pret->Release();
        __raise_error(hr, __fetcherr(hr));
    }
    return (hr);
}

// 设置错误信息
inline HRESULT __straperr(HRESULT hr, LPCSTR description, LPCSTR file, long line)
{
    BSTR desc = ATOW(description);
    HRESULT hret = __straperr(hr, desc, file, line);
    SysFreeString(desc);
    return hret;
}

// 设置错误信息
inline HRESULT __straperr(HRESULT hr, int descres, LPCSTR file, long line)
{
    if (descres==0) { return __straperr(hr, (LPCWSTR)nullptr, file, line); }

    BSTR desc = xcloadW(descres);
    HRESULT hret = __straperr(hr, desc, file, line);
    SysFreeString(desc);
    return hret;
}

/************************************************************************/

#ifndef ERRLOG
#define ERRLOG(xsprintfA) printf((xsprintfA).c_str());
#endif

/************************************************************************/
// VC6.0 支持
#if _MSC_VER < 1300

#ifndef for
#define for if(0) {} else for
#endif

inline __int64 __getInt64FromVar(const VARIANT & var)
{
    VARIANT myval; myval.vt = VT_EMPTY; 
    HRESULT myhr = ::VariantChangeType(
        &myval, const_cast<LPVARIANT>(&var), 0, VT_I8); 

#ifdef _INC_COMDEF
    if (FAILED(myhr)) { ::_com_issue_error(myhr); } 
#else
    if (FAILED(myhr)) { __debug_assert(0); }
#endif

    return myval.cyVal.int64;
}

inline BSTR __getBSTRFromVar(const VARIANT & var)
{
    if (var.vt<=VT_NULL) { return nullptr;}

    VARIANT myval; myval.vt = VT_EMPTY; 
    HRESULT myhr = ::VariantChangeType(
        &myval, const_cast<LPVARIANT>(&var), 0, VT_BSTR); 
    
#ifdef _INC_COMDEF
    if (FAILED(myhr)) { ::_com_issue_error(myhr); } 
#else
    if (FAILED(myhr)) { __debug_assert(0); }
#endif

    return myval.bstrVal;
}

inline VARIANT __getVarFromInt64(const __int64 & i8)
{
    VARIANT myval;
    myval.vt = VT_I8; 
    myval.cyVal.int64 = i8;
    return myval;
}

#endif // _MSC_VER < 1300

inline VARIANT __getVarFromBSTR(BSTR & bstr, bool byref)
{
    VARIANT myval;

    if (byref)
    {
        myval.vt = VT_BYREF|VT_BSTR;
        myval.pbstrVal = &bstr;
    }
    else
    {
        myval.vt = VT_BSTR;
        myval.bstrVal = bstr;
        bstr = nullptr;
    }
    return myval;
}



#endif // __DEPENDENCE_H