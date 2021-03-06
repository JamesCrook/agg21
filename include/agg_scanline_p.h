//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.1
// Copyright (C) 2002-2004 Maxim Shemanarev (http://www.antigrain.com)
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//----------------------------------------------------------------------------
//
// Class scanline_p - a general purpose scanline container with packed spans.
//
//----------------------------------------------------------------------------
#ifndef AGG_SCANLINE_P_INCLUDED
#define AGG_SCANLINE_P_INCLUDED

#include "agg_basics.h"

namespace agg
{

    //==============================================================scanline_p
    // 
    // This is a general purpose scaline container which supports the interface 
    // used in the rasterizer::render(). See description of agg_scanline_u
    // for details.
    // 
    //------------------------------------------------------------------------
    template<class T> class scanline_p
    {
    public:
        typedef T cover_type;

        struct span
        {
            int16    x;
            int16    len; // If negative, it's a solid span, covers is valid
            const T* covers;
        };

        typedef span* iterator;
        typedef const span* const_iterator;

        ~scanline_p()
        {
            delete [] m_spans;
            delete [] m_covers;
        }

        scanline_p() :
            m_max_len(0),
            m_last_x(0x7FFFFFF0),
            m_covers(0),
            m_cover_ptr(0),
            m_spans(0),
            m_cur_span(0)
        {
        }

        void reset(int min_x, int max_x);
        void add_cell(int x, unsigned cover);
        void add_cells(int x, unsigned len, const T* covers);
        void add_span(int x, unsigned len, unsigned cover);
        void finalize(int y) { m_y = y; }
        void reset_spans();

        int            y()         const { return m_y; }
        unsigned       num_spans() const { return unsigned(m_cur_span - m_spans); }
        const_iterator begin()     const { return m_spans + 1; }

    private:
        scanline_p(const scanline_p<T>&);
        const scanline_p<T>& operator = (const scanline_p<T>&);

        unsigned m_max_len;
        int      m_last_x;
        int      m_y;
        T*       m_covers;
        T*       m_cover_ptr;
        span*    m_spans;
        span*    m_cur_span;
    };


    //------------------------------------------------------------------------
    template<class T> 
    void scanline_p<T>::reset(int min_x, int max_x)
    {
        unsigned max_len = max_x - min_x + 3;
        if(max_len > m_max_len)
        {
            delete [] m_spans;
            delete [] m_covers;
            m_covers  = new T [max_len];
            m_spans   = new span [max_len];
            m_max_len = max_len;
        }
        m_last_x    = 0x7FFFFFF0;
        m_cover_ptr = m_covers;
        m_cur_span  = m_spans;
        m_cur_span->len = 0;
    }


    //------------------------------------------------------------------------
    template<class T> 
    void scanline_p<T>::reset_spans()
    {
        m_last_x    = 0x7FFFFFF0;
        m_cover_ptr = m_covers;
        m_cur_span  = m_spans;
        m_cur_span->len = 0;
    }


    //------------------------------------------------------------------------
    template<class T> 
    void scanline_p<T>::add_cell(int x, unsigned cover)
    {
        *m_cover_ptr = (T)cover;
        if(x == m_last_x+1 && m_cur_span->len > 0)
        {
            m_cur_span->len++;
        }
        else
        {
            m_cur_span++;
            m_cur_span->covers = m_cover_ptr;
            m_cur_span->x = (int16)x;
            m_cur_span->len = 1;
        }
        m_last_x = x;
        m_cover_ptr++;
    }


    //------------------------------------------------------------------------
    template<class T> 
    void scanline_p<T>::add_cells(int x, unsigned len, const T* covers)
    {
        memcpy(m_cover_ptr, covers, len * sizeof(T));
        if(x == m_last_x+1 && m_cur_span->len > 0)
        {
            m_cur_span->len += (int16)len;
        }
        else
        {
            m_cur_span++;
            m_cur_span->covers = m_cover_ptr;
            m_cur_span->x = (int16)x;
            m_cur_span->len = (int16)len;
        }
        m_cover_ptr += len;
        m_last_x = x + len - 1;
    }


    //------------------------------------------------------------------------
    template<class T> 
    void scanline_p<T>::add_span(int x, unsigned len, unsigned cover)
    {
        if(x == m_last_x+1 && 
           m_cur_span->len < 0 && 
           cover == *m_cur_span->covers)
        {
            m_cur_span->len -= (int16)len;
        }
        else
        {
            *m_cover_ptr = (T)cover;
            m_cur_span++;
            m_cur_span->covers = m_cover_ptr++;
            m_cur_span->x      = (int16)x;
            m_cur_span->len    = -((int16)len);
        }
        m_last_x = x + len - 1;
    }


    //=============================================================scanline_p8
    typedef scanline_p<int8u> scanline_p8;

    //============================================================scanline_p16
    typedef scanline_p<int16u> scanline_p16;

    //============================================================scanline_p32
    typedef scanline_p<int32u> scanline_p32;
}


#endif

