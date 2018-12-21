#ifndef __PQPARAMTER_H
#define __PQPARAMTER_H

#include <map>
#include <list>
#include <vector>

#define MAX_PQPARAMTER 0x4000

class CPQParamter
{
protected:
    long             m_current;
    long             m_previous;
    const long       m_maxinum;
    const long       m_groupsize;
    const long       m_threshold;
    std::wstring     m_strbuffer;
    
public:
    
    CPQParamter(
        long groupsize, // 组中的元素个数  
        long totalsize, // 元素总数
        long maxsupport // 支持的最大个数
        )
        : m_maxinum( ( min(maxsupport, totalsize<0 ? maxsupport : totalsize)
                    / groupsize)  * groupsize )
        , m_threshold( totalsize>0 ? totalsize%m_maxinum : 0 )
        , m_groupsize(groupsize)
        , m_current(0)
        , m_previous(0)
    {
        std::wstring nsize = xsprintfW(L"%d", totalsize);
        // ,($,$,$,$) =  (2n+2) * k
        m_strbuffer.reserve(m_maxinum * (nsize.length()+2) + (m_maxinum /m_groupsize) * 2);
    }
    
    bool push(unsigned group = 1)
    {
      //  long cur = InterlockedIncrement(&m_current);
        bool bret = ((m_current+=(group!=0 ? group : m_groupsize))<m_maxinum)
            ? m_current==m_threshold : (m_current - m_threshold)%m_maxinum==0;
        
        if (!bret) { return false; }

        return splice();
    }

    bool flush()
    {
        return (m_current - m_threshold)%m_maxinum==0 ? false : splice();
    }

    LPCWSTR data() const
    {
        return m_strbuffer.c_str();
    }

protected:

    bool splice()
    {
        __debug_assert(m_current%m_groupsize==0);
        if (m_current%m_groupsize !=0 || m_current==0) { return false; }

        unsigned reversed = m_current>m_threshold 
            ? ( (m_current - m_threshold - 1) % m_maxinum + 1 )
            : m_current;
        if (reversed<m_previous)
        {
            m_previous = 0; m_strbuffer.erase();
        }

        if (m_groupsize!=1)
        {
            if (m_previous==0)
            {
                m_strbuffer.append(xsprintfW(L"($%d", ++m_previous));
                for(long i=2; i<m_groupsize; ++i)
                {
                    m_strbuffer.append(xsprintfW(L",$%d", ++m_previous));
                }
                m_strbuffer.append(xsprintfW(L",$%d)", ++m_previous)); 
            }

            while(m_previous<reversed)
            {
                m_strbuffer.append(1, ',').append(xsprintfW(L"($%d", ++m_previous));
                for(long i=2; i<m_groupsize; ++i)
                {
                    m_strbuffer.append(xsprintfW(L",$%d", ++m_previous));
                }
                m_strbuffer.append(xsprintfW(L",$%d)", ++m_previous)); 
            }
        }
        else
        {
            if (m_previous==0)
            {
                m_strbuffer.append(xsprintfW(L"($%d)", ++m_previous));
            }

            while(m_previous<reversed)
            {
                m_strbuffer.append(xsprintfW(L",($%d)", ++m_previous));
            }
        }

        return true;
    }

};

#endif // __PQPARAMTER_H