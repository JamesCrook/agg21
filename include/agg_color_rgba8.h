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
// color type rgba8
//
//----------------------------------------------------------------------------

#ifndef AGG_COLOR_RGBA8_INCLUDED
#define AGG_COLOR_RGBA8_INCLUDED

#include "agg_basics.h"
#include "agg_color_rgba.h"

namespace agg
{

    //==================================================================rgba8
    struct rgba8 
    {
        enum order { rgb, bgr };

        int8u r;
        int8u g;
        int8u b;
        int8u a;

        //--------------------------------------------------------------------
        rgba8() {}

        //--------------------------------------------------------------------
        rgba8(unsigned r_, unsigned g_, unsigned b_, unsigned a_=255) :
            r(int8u(r_)), g(int8u(g_)), b(int8u(b_)), a(int8u(a_)) {}

        //--------------------------------------------------------------------
        rgba8(const rgba& c) :
            r(int8u(c.r * 255.0 + 0.5)), 
            g(int8u(c.g * 255.0 + 0.5)), 
            b(int8u(c.b * 255.0 + 0.5)), 
            a(int8u(c.a * 255.0 + 0.5)) {}
        
        //--------------------------------------------------------------------
        rgba8(const rgba8& c, unsigned a) :
            r(int8u(c.r)), 
            g(int8u(c.g)), 
            b(int8u(c.b)), 
            a(int8u(a)) {}

        //--------------------------------------------------------------------
        rgba8(unsigned packed, order o) : 
            r(int8u((o == rgb) ? ((packed >> 16) & 0xFF) : (packed & 0xFF))),
            g(int8u((packed >> 8)  & 0xFF)),
            b(int8u((o == rgb) ? (packed & 0xFF) : ((packed >> 16) & 0xFF))),
            a(255) {}

        //--------------------------------------------------------------------
        void clear()
        {
            r = g = b = a = 0;
        }
        
        //--------------------------------------------------------------------
        const rgba8& transparent()
        {
            a = 0;
            return *this;
        }

        //--------------------------------------------------------------------
        const rgba8& opacity(double a_)
        {
            if(a_ < 0.0) a_ = 0.0;
            if(a_ > 1.0) a_ = 1.0;
            a = int8u(a_ * 255.0 + 0.5);
            return *this;
        }

        //--------------------------------------------------------------------
        double opacity() const
        {
            return double(a) / 255.0;
        }

        //--------------------------------------------------------------------
        const rgba8& premultiply()
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
        const rgba8& premultiply(unsigned a_)
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
        const rgba8& demultiply()
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
        rgba8 gradient(rgba8 c, double k) const
        {
            rgba8 ret;
            int ik = int(k * 256);
            ret.r = int8u(int(r) + (((int(c.r) - int(r)) * ik) >> 8));
            ret.g = int8u(int(g) + (((int(c.g) - int(g)) * ik) >> 8));
            ret.b = int8u(int(b) + (((int(c.b) - int(b)) * ik) >> 8));
            ret.a = int8u(int(a) + (((int(c.a) - int(a)) * ik) >> 8));
            return ret;
        }

        //--------------------------------------------------------------------
        static rgba8 no_color() { return rgba8(0,0,0,0); }
    };


}




#endif
