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

#ifndef AGG_COLOR_RGBA8_PRE_INCLUDED
#define AGG_COLOR_RGBA8_PRE_INCLUDED

#include "agg_color_rgba8.h"

namespace agg
{

    //==============================================================rgba8_pre
    // A separate color type for the premultiplied RGBA 8-bit per pixel 
    // color space. Essentially it's the same as rgba8 type, but with 
    // automatic premultiplication when creating from types rgba and rgba8.
    // Note that the constructor with (r, g, b, a) doesn't do any 
    // premultiplications, it assumes the components are already 
    // premultiplied. For automatic premultiplication use:
    // agg::rgba8_pre(agg::rgba8(r, g, b, a)) or 
    // agg::rgba8_pre(agg::rgba(r, g, b, a)).
    //------------------------------------------------------------------------
    struct rgba8_pre
    {
        enum order { rgb, bgr };

        int8u r;
        int8u g;
        int8u b;
        int8u a;

        //--------------------------------------------------------------------
        rgba8_pre() {}

        //--------------------------------------------------------------------
        rgba8_pre(unsigned r_, unsigned g_, unsigned b_, unsigned a_=255) :
            r(int8u(r_)), g(int8u(g_)), b(int8u(b_)), a(int8u(a_)) 
        {}

        //--------------------------------------------------------------------
        rgba8_pre(const rgba& c) :
            r(int8u(c.r*255.0)), 
            g(int8u(c.g*255.0)), 
            b(int8u(c.b*255.0)), 
            a(int8u(c.a*255.0)) 
        {
            premultiply();
        }

        //--------------------------------------------------------------------
        rgba8_pre(const rgba8& c) :
            r(int8u(c.r)), 
            g(int8u(c.g)), 
            b(int8u(c.b)), 
            a(int8u(c.a)) 
        {
            premultiply();
        }

        //--------------------------------------------------------------------
        rgba8_pre(const rgba8_pre& c, unsigned a) :
            r(int8u(c.r)), 
            g(int8u(c.g)), 
            b(int8u(c.b))
        {
            premultiply(a);
        }

        //--------------------------------------------------------------------
        rgba8_pre(unsigned packed, order o) : 
            r(int8u((o == rgb) ? ((packed >> 16) & 0xFF) : (packed & 0xFF))),
            g(int8u((packed >> 8)  & 0xFF)),
            b(int8u((o == rgb) ? (packed & 0xFF) : ((packed >> 16) & 0xFF))),
            a(255) 
        {
        }

        //--------------------------------------------------------------------
        operator rgba8() const 
        {
            return rgba8(r, g, b, a);
        }

        //--------------------------------------------------------------------
        void clear()
        {
            r = g = b = a = 0;
        }
        
        //--------------------------------------------------------------------
        const rgba8_pre& transparent()
        {
            r = g = b = a = 0;
            return *this;
        }

        //--------------------------------------------------------------------
        const rgba8_pre& opacity(double a_)
        {
            if(a_ < 0.0) a_ = 0.0;
            if(a_ > 1.0) a_ = 1.0;
            premultiply(int8u(a_ * 255.0));
            return *this;
        }

        //--------------------------------------------------------------------
        double opacity() const
        {
            return double(a) / 255.0;
        }

        //--------------------------------------------------------------------
        rgba8_pre gradient(rgba8_pre c, double k) const
        {
            int ik = int(k * 256);
            c.r = int8u(int(r) + (((int(c.r) - int(r)) * ik) >> 8));
            c.g = int8u(int(g) + (((int(c.g) - int(g)) * ik) >> 8));
            c.b = int8u(int(b) + (((int(c.b) - int(b)) * ik) >> 8));
            c.a = int8u(int(a) + (((int(c.a) - int(a)) * ik) >> 8));
            return c;
        }

        //--------------------------------------------------------------------
        const rgba8_pre& premultiply()
        {
            if(a == 255) return *this;
            if(a == 0)
            {
                r = g = b = 0;
                return *this;
            }
            r = (r * a) >> 8;
            g = (g * a) >> 8;
            b = (b * a) >> 8;
            return *this;
        }

        //--------------------------------------------------------------------
        const rgba8_pre& premultiply(unsigned a_)
        {
            if(a == 255 && a_ == 255) return *this;
            if(a == 0   || a_ == 0)
            {
                r = g = b = a = 0;
                return *this;
            }
            unsigned r_ = (r * a_) / a;
            unsigned g_ = (g * a_) / a;
            unsigned b_ = (b * a_) / a;
            r = (r_ > 255) ? 255 : r_;
            g = (g_ > 255) ? 255 : g_;
            b = (b_ > 255) ? 255 : b_;
            a = a_;
            return *this;
        }

        //--------------------------------------------------------------------
        const rgba8_pre& demultiply()
        {
            if(a == 255) return *this;
            if(a == 0)
            {
                r = g = b = 0;
                return *this;
            }
            unsigned r_ = (r * 255) / a;
            unsigned g_ = (g * 255) / a;
            unsigned b_ = (b * 255) / a;
            r = (r_ > 255) ? 255 : r_;
            g = (g_ > 255) ? 255 : g_;
            b = (b_ > 255) ? 255 : b_;
            return *this;
        }

        //--------------------------------------------------------------------
        static rgba8_pre no_color() { return rgba8_pre(0,0,0,0); }
    };


}


#endif
