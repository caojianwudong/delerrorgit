#ifndef __IMP_IUNKNOWN_H
#define __IMP_IUNKNOWN_H

/*****************************************************************************/

class CUnknown : public ISupportErrorInfo
{
public:

  CUnknown() : m_ulRef(0) {};

  virtual ~CUnknown() {};

public:

  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvo)
  {
    if (IsEqualIID(riid, __uuidof(IUnknown)))
    {
      *ppvo = (IUnknown *)this; AddRef();
      return S_OK;
    }
    else if(IsEqualIID(riid, __uuidof(ISupportErrorInfo)))
    {
      *ppvo = (ISupportErrorInfo *)this; AddRef();
      return S_OK;
    }
    else
    {
      return E_NOTIMPL;
    }

  }

  virtual ULONG STDMETHODCALLTYPE AddRef(void)
  {
    return InterlockedIncrement(&m_ulRef);
  }

  virtual ULONG STDMETHODCALLTYPE Release(void)
  {
    ULONG uRet = InterlockedDecrement(&m_ulRef);
    if (uRet) { return uRet; }
    delete this; return (0);
  }

  virtual HRESULT STDMETHODCALLTYPE InterfaceSupportsErrorInfo(REFIID riid)
  {
    return S_OK;
  }

private:
  LONG m_ulRef;
};

/*****************************************************************************/

template < class sourcetype, class _Super = CUnknown, class interfacetype = sourcetype>
class __imp : public sourcetype, protected virtual _Super
{
public: 
    __imp() : _Super() {}

    virtual ~__imp() {}

public:
    virtual STDMETHODIMP QueryInterface(REFIID riid, void **ppvo)
    {
        if (IsEqualIID(riid, __uuidof(interfacetype)))
        {
            *ppvo = (interfacetype *)this; AddRef(); return S_OK;
        }
        return _Super::QueryInterface(riid, ppvo);
    }

    virtual STDMETHODIMP_(ULONG) AddRef(void)  
    { return _Super::AddRef();  }
    
    virtual STDMETHODIMP_(ULONG) Release(void) 
    { return _Super::Release(); }
};

/*****************************************************************************/

template < class sourcetype, class advancetype = sourcetype >
class __comptr
{
    typedef sourcetype * nodeptr;

public:

    __comptr(int ptr = nullptr):  __pointer(nullptr)
    { }

    __comptr(const nodeptr ptr):  __pointer(nullptr)
    { assign(ptr); }

    __comptr(struct IUnknown * ptr) : __pointer(nullptr)
    { assign(ptr); }

    __comptr(const __comptr & ptr) : __pointer(nullptr)
    {
        assign(ptr.__pointer);
    }

    ~__comptr() { assign(nullptr); }

public:
  
    nodeptr mynode() const { return __pointer; }

    bool  isnill() const  { return (__pointer==nullptr); }

    operator nodeptr() const { return __pointer; }

public:

    nodeptr* operator&()
    { assign(nullptr); return (sourcetype**)&__pointer;}

    advancetype * operator->() const
    { __debug_comptr(__pointer!=nullptr ? S_OK : E_POINTER); return __pointer; }

    advancetype & operator *()const
    { return *__pointer; }

public:

    __comptr& operator=(int) {  return assign(0); }

    __comptr& operator=(const nodeptr ptr) { return assign(ptr); }

    __comptr& operator=(struct IUnknown * ptr) { assign(ptr); return (*this); }

    __comptr& operator=(const __comptr & ptr) { assign(ptr.__pointer); return (*this); }

public:

    __comptr & assign(int)
    {
        if (nullptr!=__pointer)
        {
            __pointer->Release(); __pointer = nullptr;
        }      
        return (*this);
    }

    __comptr & assign(const nodeptr ptr)
    {
        if (nullptr!=__pointer) { __pointer->Release(); }

        if (nullptr!=(__pointer=(advancetype *)ptr))
        { 
            __pointer->AddRef(); 
        }
        
        return (*this);
    }

    HRESULT assign(struct IUnknown * ptr)
    {
        if (nullptr!=__pointer)
        { 
            __pointer->Release(); __pointer = nullptr;
        }

        return  (ptr!=nullptr)
            ? ptr->QueryInterface(__uuidof(sourcetype), (LPVOID *)&__pointer)
            : S_OK;
    }

    HRESULT attach(int){ return assign((nodeptr)nullptr); }

    HRESULT attach(const nodeptr ptr) 
    { 
        if (nullptr!=__pointer) { __pointer->Release(); }
        __pointer=(advancetype *)ptr;            
        return S_OK;
    }

    HRESULT attach(struct IUnknown * ptr)
    {
        if (nullptr!=__pointer)
        { 
            __pointer->Release(); __pointer = nullptr;
        }

        if (ptr!=nullptr)
        {
            HRESULT hr = ptr->QueryInterface(__uuidof(sourcetype), (LPVOID *)&__pointer);
            if (__pointer!=nullptr) { __pointer->Release(); }
            return hr;
        }

        return S_OK;
    }

    nodeptr clone() const 
    { 
        if (__pointer!=nullptr) 
        {
            __pointer->AddRef(); 
        } 
        return __pointer; 
    }
    
    nodeptr detach()
    { nodeptr ret = __pointer; __pointer = nullptr; return ret; }

private:

    advancetype * __pointer;
};

/*****************************************************************************/

#endif // __IMP_IUNKNOWN_H