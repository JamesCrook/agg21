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
// bounding_rect function template
//
//----------------------------------------------------------------------------
#ifndef AGG_BOUNDING_RECT_INCLUDED
#define AGG_BOUNDING_RECT_INCLUDED

#include "agg_basics.h"

namespace agg
{

    //-----------------------------------------------------------bounding_rect
    template<class VertexSource, class GetId> 
    bool bounding_rect(VertexSource& vs, GetId& gi, 
                       unsigned start, unsigned num, 
                       double* x1, double* y1, double* x2, double* y2)
    {
        unsigned i;
        double x;
        double y;

        *x1 =  1e100;
        *y1 =  1e100;
        *x2 = -1e100;
        *y2 = -1e100;

        for(i = 0; i < num; i++)
        {
            vs.rewind(gi[start + i]);
            unsigned cmd;
            while(!is_stop(cmd = vs.vertex(&x, &y)))
            {
                if(is_vertex(cmd))
                {
                    if(x < *x1) *x1 = x;
                    if(y < *y1) *y1 = y;
                    if(x > *x2) *x2 = x;
                    if(y > *y2) *y2 = y;
                }
            }
        }
        return *x1 <= *x2 && *y1 <= *y2;
    }


    //-----------------------------------------------------bounding_rect_single
    template<class VertexSource> 
    bool bounding_rect_single(VertexSource& vs, unsigned path_id,
                              double* x1, double* y1, double* x2, double* y2)
    {
        double x;
        double y;

        *x1 =  1e100;
        *y1 =  1e100;
        *x2 = -1e100;
        *y2 = -1e100;

        vs.rewind(path_id);
        unsigned cmd;
        while(!is_stop(cmd = vs.vertex(&x, &y)))
        {
            if(is_vertex(cmd))
            {
                if(x < *x1) *x1 = x;
                if(y < *y1) *y1 = y;
                if(x > *x2) *x2 = x;
                if(y > *y2) *y2 = y;
            }
        }
        return *x1 <= *x2 && *y1 <= *y2;
    }


}

#endif
