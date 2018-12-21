#ifndef __JSON_H
#define __JSON_H

#include "jmeta.h"

#ifndef __debug_assert
#define __debug_assert(x)
#endif

#define mbstobs(x, retval) do{                                                 \
  BSTR r = nullptr; unsigned n = (x!=nullptr) ? strlen(x) : 0;                 \
  size_t l = ::MultiByteToWideChar(CP_ACP, 0, (x), n, NULL, 0);                \
  if (l != 0 && (r = ::SysAllocStringLen(nullptr, l)) != nullptr)              \
    ::MultiByteToWideChar(CP_ACP, 0, (x), n, r, l);                            \
  (retval) = r;  } while (0)

#ifdef _DEBUG
#define JSON_INFO(x) do { std::string str; (x).encode(str); printf("%s\n", str.c_str()); } while(0);
#else
#define JSON_INFO(x) do { std::string str; (x).encode(str); printf("%s\n", str.c_str()); } while(0);
#endif

class json : protected jmeta
{
public:
  enum {
            jnull    = 0, 
            jboolean = 1, 
            jtiny    = 2,
            jsmall   = 3,
            jlong    = 4, 
            jbigint  = 5,
            jdouble  = 6, 
            jstring  = 7, 
            jbinary  = 8, 
            jnode    = 9,
            jarray   = 10, 
            jkeymap  = 11,
        };
public:

  json() { jmeta_init(this); }
  json(bool v)            { jmeta_init(this);  operator=(v); }
  json(char v)            { jmeta_init(this);  operator=(v); }
  json(short v)           { jmeta_init(this);  operator=(v); }
  json(int v)             { jmeta_init(this);  operator=(v); }
  json(long v)            { jmeta_init(this);  operator=(v); }
  json(__int64 v)         { jmeta_init(this);  operator=(v); }
  json(double v)          { jmeta_init(this);  operator=(v); }
  json(const char * v)    { jmeta_init(this);  operator=(v); }
  json(const wchar_t * v) { jmeta_init(this);  operator=(v); }
  json(const VARIANT & v) { jmeta_init(this);  operator=(v); }
  json(const json & source)
  { 
      if (source.jtype==jnode) 
      { 
          jmeta_make(jnode, this, jmeta_node(&source)); 
      }
      else
      {
          jmeta_init(this);
          jmeta_clone(jmeta_node(&source), this);
      }
  }

  ~json() { jmeta_free(this); }

protected:

  json(const jmeta * psource)
  {
    jmeta_make(jnode, this, (jmeta *)psource);
  }

public:

  json& operator=(bool v) 
  {
    VARIANT var;
    var.vt = VT_BOOL;
    var.boolVal = v ? VARIANT_TRUE : VARIANT_FALSE;
    jmeta_set(jmeta_node(this), &var);
    return *this;
  }

  json& operator=(char v)
  {
      VARIANT var; var.vt = VT_I1; var.cVal = v;
      jmeta_set(jmeta_node(this), &var);
      return *this;
  }
  
  json& operator=(short v)
  {
      VARIANT var; var.vt = VT_I2; var.iVal = v;
      jmeta_set(jmeta_node(this), &var);
      return *this;
  }

  json& operator=(int v)
  {
    VARIANT var; var.vt = VT_I4; var.lVal = v;
    jmeta_set(jmeta_node(this), &var);
    return *this;
  }

  json& operator=(long v)
  {
    VARIANT var; var.vt = VT_I4; var.lVal = v;
    jmeta_set(jmeta_node(this), &var);
    return *this;
  }

  json& operator=(__int64 v)
  {
    VARIANT var; var.vt = VT_I8; var.cyVal.int64 = v;
    jmeta_set(jmeta_node(this), &var);
    return *this;
  }

  json& operator=(double v)
  {
    VARIANT var; var.vt = VT_R8; var.dblVal = v ;
    jmeta_set(jmeta_node(this), &var);
    return *this;
  }

  json& operator=(const wchar_t* v)
  {
    VARIANT var; var.vt = VT_BSTR; var.bstrVal = (BSTR)v;
    jmeta_set(jmeta_node(this), &var);
    return *this;
  }

  json& operator=(const char * v)
  {
    jmeta * p = jmeta_node(this);
    VARIANT var; var.vt = VT_BSTR; var.bstrVal = nullptr;
    jmeta_set(p, &var);
    mbstobs(v, p->jvalue.s);
    return *this;
  }

  json& operator=(const VARIANT & v)
  {
    jmeta_set(jmeta_node(this), &v);
    return *this;
  }

  json& operator=(const json& v)
  {
    json tmp;
    jmeta_clone(jmeta_node(&v), &tmp);
    swap(tmp);
    return *this;
  }

public:
 
  operator bool() const
  {
    VARIANT var; 
    return (jmeta_get(jmeta_node(this), &var) &&
     ::VariantChangeType(&var, &var, 0, VT_BOOL) == S_OK)
      ? var.boolVal!=VARIANT_FALSE : false;
  }

  operator long() const
  {
    VARIANT var;
    return (jmeta_get(jmeta_node(this), &var) &&
      ::VariantChangeType(&var, &var, 0, VT_I4) == S_OK)
      ? var.lVal : false;
  }

  operator int() const
  {
    VARIANT var;
    return (jmeta_get(jmeta_node(this), &var) &&
      ::VariantChangeType(&var, &var, 0, VT_INT) == S_OK)
      ? var.lVal : false;
  }

  operator __int64() const
  {
    VARIANT var;
    return (jmeta_get(jmeta_node(this), &var) &&
      ::VariantChangeType(&var, &var, 0, VT_I8) == S_OK)
      ? var.cyVal.int64 : false;
  }

  operator VARIANT() const
  {
    VARIANT var = {0};
    jmeta_get(jmeta_node(this), &var);
    return var;
  }

#ifdef _STRING_
  operator std::string() const
  {
      VARIANT var;
      std::string retval;

      if ( !jmeta_get(jmeta_node(this), &var) )
      {
          return retval;
      }
      
      if ( (var.vt&VT_TYPEMASK)!=VT_BSTR )
      {
          if (::VariantChangeType(&var, &var, 0, VT_BSTR)!=S_OK)
          {
              return retval;
          }
      }
      
      BSTR bstr = ((var.vt&VT_BYREF)!=VT_BYREF )
          ? var.bstrVal
          : ((var.pbstrVal!=nullptr) ? *var.pbstrVal : nullptr);

      if (bstr!=nullptr)
      {
          unsigned nstr = ::SysStringLen(bstr);
          retval.resize(::WideCharToMultiByte(CP_ACP,
              0, bstr, nstr, nullptr, 0, nullptr, nullptr));

          if (!retval.empty())
          {
              ::WideCharToMultiByte(CP_ACP,
                  0, bstr, nstr, &retval[0], retval.length(), nullptr, nullptr);
          }      
      }

      VariantClear(&var);
      return retval;
  }

  operator std::wstring() const
  {
      VARIANT var;
      std::wstring retval;

      if ( !jmeta_get(jmeta_node(this), &var) )
      {
          return retval;
      }

      if ( (var.vt&VT_TYPEMASK)!=VT_BSTR )
      {
          if (::VariantChangeType(&var, &var, 0, VT_BSTR)!=S_OK)
          {
              return retval;
          }
      }

      BSTR bstr = ((var.vt&VT_BYREF)!=VT_BYREF )
          ? var.bstrVal
          : ((var.pbstrVal!=nullptr) ? *var.pbstrVal : nullptr);

      if (bstr!=nullptr){ retval.assign(bstr); }
      VariantClear(&var);
      return retval;
  }
#endif _STRING_

public:
  bool isnan() const    { return jmeta_isnan(this); }
  bool isdef() const    { return jmeta_isdefault(jmeta_node(this)); }
  bool isnode() const   { return this->jtype == jnode; }
  bool isnill() const   { return jmeta_node(this)->jtype == jnull;  } 
  bool isleaf() const   { return jmeta_isleaf(jmeta_node(this)); }
  bool isarray() const  { return jmeta_node(this)->jtype == jarray; }
  bool iskeymap() const { return jmeta_node(this)->jtype == jkeymap;}

public:

  jmeta * getnode()
  {
      return jmeta_node(this);
  }
    
  const jmeta * getnode() const
  {
      return jmeta_node(this);

//       jmeta r;
//       jmeta_make(jnode, &r, jmeta_node(this));
//       return r;
  }

  LPCWSTR getkey() const
  { 
    return jmeta_node(this)->jkey;
  }

  long  gettype() const { return jmeta_node(this)->jtype; }

  unsigned length() const 
  { return jmeta_length(jmeta_node(this)); }

  json at(unsigned pos)
  { return json(jmeta_index(jmeta_node(this), pos)); }

  const json at(unsigned pos) const
  { return json(jmeta_index(jmeta_node(this), pos)); }

  json at(LPCSTR key) { return at(search(key)); }
  
  const json at(LPCWSTR key) const { return at(search(key)); }

  unsigned insert(unsigned pos, LPCSTR key, const json & var)
  {
    BSTR wkey; mbstobs(key, wkey);
    unsigned r = insert(pos, wkey, var);
    ::SysFreeString(wkey); return r;
  }

  unsigned insert(unsigned pos, LPCWSTR key, const json & var)
  {
    __debug_assert(iskeymap() || isarray());
    jmeta t = *jmeta_node(&var); t.jkey = (BSTR)key;
    __debug_assert(jmeta_node(&var)!=nullptr);
    return jmeta_insert(jmeta_node(this), pos, &t, 1);
  }

  unsigned insert(unsigned pos, const json & var)
  {
      return insert(pos, (LPCWSTR)nullptr, var);
  }

  unsigned insert(LPCWSTR key, const json & var)
  {
    return insert(0, key, var);
  }

  unsigned insert(LPCSTR key, const json & var)
  {
    return insert(0, key, var);
  }

  json replace(unsigned pos, LPCSTR key, const json & var = json())
  {
    BSTR wkey; mbstobs(key, wkey);
    json r = replace(pos, wkey, var);
    ::SysFreeString(wkey); return r;
  }

  json replace(unsigned pos, LPCWSTR key, const json & var = json())
  {
    __debug_assert(iskeymap() || isarray());
    __debug_assert(jmeta_node(&var)!=nullptr);
    jmeta t = *jmeta_node(&var); t.jkey = (BSTR)key;
    return at(jmeta_replace(jmeta_node(this), pos, &t));
  }

  unsigned append(const json & var)
  {
    return insert(iskeymap() ? 0 : length(), (LPCWSTR)NULL, var);
  }

  unsigned append(LPCWSTR key, const json & var)
  {
    return insert(iskeymap() ? 0 : length(), key, var);
  }

  unsigned append(LPCSTR key, const json & var)
  {
    return insert(iskeymap() ? 0 : length(), key, var);
  }

  unsigned search(LPCWSTR key, unsigned pos=0) const
  {
    __debug_assert(iskeymap() || isarray());
    return jmeta_search(jmeta_node(this), pos, key);
  }

  unsigned search(LPCSTR key, unsigned pos = 0) const
  {
    BSTR wkey; mbstobs(key, wkey);
    unsigned r = search(wkey, pos);
    ::SysFreeString(wkey); return r;
  }

  unsigned remove(unsigned pos, unsigned len = 1)
  {
    __debug_assert(iskeymap() || isarray());
    return jmeta_remove(jmeta_node(this), pos, len);
  }

  unsigned remove(LPCWSTR key)
  {
    __debug_assert(iskeymap() || isarray());
    return remove(search(key));
  }

  unsigned remove(LPCSTR key)
  {
    __debug_assert(iskeymap() || isarray());
    return remove(search(key));
  }

public:

    bool operator !() const
    {
        return !(operator bool());
    }

    bool operator==(const json & var) const
    {
        return jmeta_compare(jmeta_node(this), jmeta_node(&var), true)==0;
    }

public:

  json operator[](signed i) { return at(i); }

  const json operator[](signed i) const { return at(i); }

  json operator[](LPCWSTR key)
  {
    unsigned i = search(key);
    return at(i < length() ? i : insert(key, json()));
  }

  const json operator[](LPCWSTR key) const  { return at(search(key)); }

  json operator[](LPCSTR key)
  {
    unsigned i = search(key);
    return at(i < length() ? i : insert(key, json()));
  }

  const json operator[](LPCSTR key) const  
  { return at(search(key)); }

#ifdef _INC_COMUTIL
  public:

    json(const _bstr_t & v)
    {
      jmeta_init(this); operator=((LPCWSTR)v); 
    }

    operator _bstr_t() const 
    {
      VARIANT var;
      if ( !jmeta_get(jmeta_node(this), &var) )
      {
          return _bstr_t();
      }

      if ( (var.vt&VT_TYPEMASK)!=VT_BSTR )
      {
          if (::VariantChangeType(&var, &var, 0, VT_BSTR)!=S_OK)
          {
              return _bstr_t();
          }
      }

      return ((var.vt&VT_BYREF)==VT_BYREF && var.pbstrVal!=nullptr)
          ? _bstr_t(*var.pbstrVal) : _bstr_t(var.bstrVal, true);
    }

    json& operator=(const _bstr_t& v)
    { 
      return operator = ((LPCWSTR)v); 
    }

    json operator[](const _bstr_t & key)
    {
      unsigned i = search(LPCWSTR(key));
      return at(i < length() ? i : insert(LPCWSTR(key), json()));
    }

    const json operator[](const _bstr_t & key) const
    {
      return at(search((LPCWSTR)key));
    }

    unsigned insert(const _bstr_t & key, const json & var)
    {
      return insert((LPCWSTR)key, var);
    }

    unsigned insert(unsigned pos, const _bstr_t & key, const json & var)
    {
      return insert(pos, (LPCWSTR)key, var);
    }

    unsigned append(const _bstr_t & key, const json & var)
    {
      return append((LPCWSTR)key, var);
    }

    json replace(unsigned pos, const _bstr_t & key, const json & var = json())
    {
      return replace(pos, (LPCWSTR)key, var);
    }

    unsigned search(const _bstr_t & key, unsigned pos = 0) const
    {
      return search((LPCWSTR)key, pos);
    }

    unsigned remove(const _bstr_t & key)
    {
      return remove((LPCWSTR)key);
    }

    operator _variant_t() const
    {
      VARIANT var = { 0 };
      jmeta_get(jmeta_node(this), &var);
      return _variant_t(var, false);
    }

    _bstr_t gettext() const
    {
        _bstr_t retval;
        if ( !isnan() )
        { 
            BSTR r = jmeta_encode(jmeta_node(this), 0);
            if (r!=nullptr)
            {
                retval = (LPCSTR)r;
                SysFreeString(r);
            }
        }
        else
        {
            __debug_break(); // 无效json 
            
        }
        return retval;
    }

    json & puttext(const _bstr_t & text)
    {
        if ( !jmeta_decodeW(jmeta_node(this), text, text.length()) )
        {
            jmeta * p = jmeta_node(this);
            jmeta_free(p); jmeta_init(p);
            __debug_break(); // 解析错误 
        }
        return *this;
    }

    __declspec(property(get=gettext,put=puttext))  _bstr_t text;
#endif

public:

  json & swap(json & source, bool iskeyswap = false)
  {
    jmeta_swap(jmeta_node(this), jmeta_node(&source), iskeyswap);
    return *this;
  }

  bool cast_array()
  {
    return jmeta_cast(jmeta_node(this), jarray);
  }

  bool cast_keymap()
  {
    return jmeta_cast(jmeta_node(this), jkeymap);
  }

  bool copy(json & r, unsigned p = 0, unsigned n = -1)
  {
    json retval;
    if (!jmeta_combine(jmeta_node(this), p, n, nullptr, 0, 0, &retval))
    {
      return false;
    }
    retval.swap(r); 
    return true;
  }

  json & attach(jmeta * p)
  {
      jmeta_free(this);
      if (p==nullptr)
      {
          jmeta_make(jnode, this, p);
      }
      else
      {
          *(jmeta *)this = *p;
          jmeta_init(p);
      }
      return *this;
  }

  jmeta detach()
  {
      jmeta r = *this; jmeta_init(this); return r;
  }

public:

  const json & make_node(jmeta * p)
  {
      jmeta_free(this);
      jmeta_make(jnode, this, (p!=nullptr) ? jmeta_node(p) : p);
      return *this;
  }

  const json & make_node(const json & s)
  {
      jmeta_free(this);
      jmeta_make(jnode, this, jmeta_node(&s));
      return *this;
  }

  json & make_array(unsigned n=0, json * p=nullptr)
  {
      jmeta t; 
      jmeta_make(jarray, &t, jmeta_makenode(n));
      if (t.jvalue.node!=nullptr && p!=nullptr)
      {
          for(unsigned i=0; i<n; ++i)
          {
              jmeta * src = jmeta_node(&p[i]);
              jmeta * des = jmeta_index(&t, i);
              
              des->jkey = jmeta_makekey(src->jkey);
              jmeta_swap(des, src, false);
          }
      }
      jmeta_swap(jmeta_node(this), &t, false);
      jmeta_free(&t);
      return *this;
  }

  json & make_keymap(unsigned n=0, json * p=nullptr)
  {
      jmeta t; 
      jmeta_make(jkeymap, &t, jmeta_makenode(n));
      if (t.jvalue.node!=nullptr && p!=nullptr)
      {
          for(unsigned i=0; i<n; ++i)
          {
              jmeta * src = jmeta_node(&p[i]);
              jmeta * des = jmeta_index(&t, i);
              
              des->jkey = jmeta_makekey(src->jkey);
              jmeta_swap(des, src, false);
          }
      }
      jmeta_swap(jmeta_node(this), &t, false);
      jmeta_free(&t);
      return *this;
  }

  bool encode(std::string & str, int codepage = 0) const
  {
      if ( isnan() ) { return false; }

      BSTR r = jmeta_encode(jmeta_node(this), codepage);
      if (r!=nullptr)
      {
          str.assign((LPCSTR)r, ::SysStringByteLen(r));
          SysFreeString(r);
          return true;
      }
      return false;
  }

  /*
  std::string textA(int codepage = 0) const
  {
      std::string retval;
      if ( !isnan() ) 
      { 
          BSTR r = jmeta_encode(jmeta_node(this), codepage);
          if (r!=nullptr)
          {
              retval.assign((LPCSTR)r, ::SysStringByteLen(r));
              SysFreeString(r);
          }
      }
      else
      {
          __debug_break(); // 无效json 
          
      }

      return retval;
  }

  std::wstring textW() const
  {
      std::wstring retval;
      if ( !isnan() ) 
      { 
          BSTR r = jmeta_encode(jmeta_node(this), CP_UTF8);
          if (r!=nullptr)
          {
              int l = ::SysStringByteLen(r);
              retval.resize(::MultiByteToWideChar(CP_UTF8, 0, 
                  (LPCSTR)r, l, nullptr, 0));
              if (!retval.empty())
              {
                  ::MultiByteToWideChar(CP_UTF8, 0, 
                      (LPCSTR)r, l, &retval[0], retval.length());
              }
              SysFreeString(r);
          }
      }
      else
      {
          __debug_break(); // 无效json 
          
      }
      return retval;
  }*/

  bool decode(LPCSTR s, int l = -1, int codepage = 0)
  {
      return jmeta_decodeA(jmeta_node(this), s, l, codepage);
  }

  bool decode(LPCWSTR s, int l = -1)
  {
      return jmeta_decodeW(jmeta_node(this), s, l);
  }

#ifdef __REWRITER_H

  bool decode(rewriter & o, int codepage = 0)
  {
      bool r;
      unsigned __int64 prev = o.get_position(), next = prev;

      REWRITER * p = o.lease();
      if (r = jmeta_decodeF(jmeta_node(this), p, codepage))
      {
          p->Tell(p, &next);
          o.resume(p, true, next - prev);
      }
      else
      {
          o.resume(p, false, 0); 
      }

      return r;
  }
#endif
};

#ifdef __REWRITER_H

inline rewriter & operator>>(rewriter & _O, json & _V)
{
    jmeta * pmeta = _V.getnode();
    if (pmeta!=nullptr)
    {
        unsigned n = 0;
        REWRITER * p = _O.lease();
        if ( jmeta_recv(pmeta, p, &n) )
        {
           _O.resume(p, true, n);
        }
        else
        {
           _O.resume(p, false, 0);
        }
    }
    return _O;
}

inline rewriter & operator<<(rewriter & _O, const json & _V)
{
    const jmeta * pmeta = _V.getnode();
    if (pmeta!=nullptr)
    {
        unsigned n = 0;
        REWRITER * p = _O.lease();
        if ( jmeta_send(pmeta, p, &n) )
        {
            _O.resume(p, true, n);
        }
        else
        {
            _O.resume(p, false, 0);
        }
    }
    return _O;
}

#endif // __REWRITER_H


#endif __JSON_H
