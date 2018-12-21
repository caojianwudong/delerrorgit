#ifndef __JMETA_H
#define __JMETA_H

/*

#define jmeta_refer(x, s) do { \
(x)->jclass = jmeta::jnode; (x)->jval = s; (x)->jkey = nullptr; } while (0)

#define jmeta_isnan(x) ((x)->jclass==jmeta::jnode && (x)->jval== nullptr)
#define jmeta_node(x) \
  (((x)->jclass == jmeta::jnode) ? (x)->jval : (jmeta *)(x))
*/

#ifndef JMETA_EXPORTS
#pragma comment(lib, "jmeta")
#endif

extern "C"
{
#ifndef __JMETA_TAG
#define __JMETA_TAG
    struct jmeta
    {
        long jtype;
        
        BSTR jkey;

        union {
            VARIANT_BOOL b;
            char         c;
            short        i;
            long         l;
            __int64      ll;
            double       d;
            BSTR         s;
            LPSAFEARRAY  p;
            jmeta    *   node;
        } jvalue;
    };
#endif

#ifndef nullptr
#ifndef NULL
#define NULL 0
#endif
#define nullptr NULL
#endif // nullptr

// bool jme

//  (((x)->jclass==jmeta::jnode &&(x)->jval!=nullptr) ?  (x)->jval : (x))

#define jmeta_init(x) \
    (x)->jtype = 0; (x)->jkey = nullptr;

#define jmeta_make(t, x, s) do { \
    (x)->jtype = (t); (x)->jkey = nullptr; (x)->jvalue.node = (s); \
    } while (0)

#define jmeta_node(x) \
    (((x)->jtype == jnode) ? (x)->jvalue.node : (jmeta *)(x))

#define jmeta_isnan(x) \
    ((x)->jtype == jnode && (x)->jvalue.node== nullptr)

#define jmeta_isleaf(x) \
    ((x)->jtype != jarray && (x)->jtype!= jkeymap)

bool     jmeta_set(jmeta * t, const VARIANT * v);
bool     jmeta_get(const jmeta * t, LPVARIANT v);
unsigned jmeta_insert(jmeta * t, unsigned p, const jmeta * s, unsigned n);
unsigned jmeta_remove(jmeta * t, unsigned p, unsigned n);
unsigned jmeta_replace(jmeta * t, unsigned p, const jmeta * s);
void     jmeta_clone(const jmeta * t, jmeta * s);
unsigned jmeta_length(const jmeta * t);
unsigned jmeta_search(const jmeta * t, unsigned p, const wchar_t * k);
jmeta *  jmeta_index(const jmeta * t, unsigned p);
long     jmeta_compare(const jmeta * t, const jmeta * s, bool nullAsDef);
void     jmeta_swap(jmeta * t, jmeta * s, bool swapkey);
bool     jmeta_cast(jmeta * t, long jtype);
void     jmeta_free(const jmeta * t);
BSTR     jmeta_encode(const jmeta * t, int codepage);
bool     jmeta_decodeA(jmeta * t, const char * p, int n, int codepage);
bool     jmeta_decodeW(jmeta * t, const wchar_t * p, int n);
bool     jmeta_combine(const jmeta * t, unsigned pt, unsigned nt,
                       const jmeta * s, unsigned ps, unsigned ns,
                       jmeta * r);
BSTR     jmeta_makekey(LPCWSTR k);
jmeta *  jmeta_makenode(unsigned n);
bool     jmeta_isdefault(const jmeta * t);


#ifdef __REWRITER_H
bool jmeta_decodeF(jmeta * t, REWRITER * p, int codepage);
bool jmeta_recv(jmeta * t, REWRITER * p, unsigned * n);
bool jmeta_send(const jmeta * t, REWRITER * p, unsigned * n);
#endif // __REWRITER_H


// utf8 string

//bool     jmeta_write(jmeta * t, REWRITER * writer);
//bool     jmeta_read(jmeta * t, REWRITER * reader);


/*
void     jmeta_freenode(jmeta * p, unsigned n);
void     jmeta_copynode(jmeta * s, jmeta * e, jmeta * t);
*/
};
#endif
