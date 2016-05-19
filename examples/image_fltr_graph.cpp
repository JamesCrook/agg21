#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "agg_rendering_buffer.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_ellipse.h"
#include "agg_trans_affine.h"
#include "agg_conv_transform.h"
#include "agg_conv_stroke.h"
#include "agg_pixfmt_rgb24.h"
#include "agg_scanline_p.h"
#include "agg_renderer_scanline.h"
#include "agg_image_filters.h"
#include "ctrl/agg_slider_ctrl.h"
#include "ctrl/agg_rbox_ctrl.h"
#include "ctrl/agg_cbox_ctrl.h"
#include "platform/agg_platform_support.h"


enum { flip_y = true };


class the_application : public agg::platform_support
{
    agg::cbox_ctrl<agg::rgba8>  m_bilinear;
    agg::cbox_ctrl<agg::rgba8>  m_bicubic;
    agg::cbox_ctrl<agg::rgba8>  m_spline16;
    agg::cbox_ctrl<agg::rgba8>  m_spline36;
    agg::cbox_ctrl<agg::rgba8>  m_sinc36;
    agg::cbox_ctrl<agg::rgba8>  m_blackman36;
    agg::cbox_ctrl<agg::rgba8>  m_sinc64;
    agg::cbox_ctrl<agg::rgba8>  m_blackman64;
    agg::cbox_ctrl<agg::rgba8>  m_sinc100;
    agg::cbox_ctrl<agg::rgba8>  m_blackman100;
    agg::cbox_ctrl<agg::rgba8>  m_sinc144;
    agg::cbox_ctrl<agg::rgba8>  m_blackman144;
    agg::cbox_ctrl<agg::rgba8>  m_sinc196;
    agg::cbox_ctrl<agg::rgba8>  m_blackman196;
    agg::cbox_ctrl<agg::rgba8>  m_sinc256;
    agg::cbox_ctrl<agg::rgba8>  m_blackman256;
    agg::cbox_ctrl<agg::rgba8>* m_filters[32];

    agg::image_filter<agg::image_filter_bilinear>    m_filter_bilinear;
    agg::image_filter<agg::image_filter_bicubic>     m_filter_bicubic;
    agg::image_filter<agg::image_filter_spline16>    m_filter_spline16;
    agg::image_filter<agg::image_filter_spline36>    m_filter_spline36;
    agg::image_filter<agg::image_filter_sinc36>      m_filter_sinc36;
    agg::image_filter<agg::image_filter_blackman36>  m_filter_blackman36;
    agg::image_filter<agg::image_filter_sinc64>      m_filter_sinc64;
    agg::image_filter<agg::image_filter_blackman64>  m_filter_blackman64;
    agg::image_filter<agg::image_filter_sinc100>     m_filter_sinc100;
    agg::image_filter<agg::image_filter_blackman100> m_filter_blackman100;
    agg::image_filter<agg::image_filter_sinc144>     m_filter_sinc144;
    agg::image_filter<agg::image_filter_blackman144> m_filter_blackman144;
    agg::image_filter<agg::image_filter_sinc196>     m_filter_sinc196;
    agg::image_filter<agg::image_filter_blackman196> m_filter_blackman196;
    agg::image_filter<agg::image_filter_sinc256>     m_filter_sinc256 ;
    agg::image_filter<agg::image_filter_blackman256> m_filter_blackman256;
    agg::image_filter_base*                          m_filter_func[32];

    unsigned                                         m_num_filters;


public:
    the_application(agg::pix_format_e format, bool flip_y) :
        agg::platform_support(format, flip_y),
        m_bilinear   (8.0, 10.0,     "bilinear",    !flip_y),
        m_bicubic    (8.0, 10.0+20,  "bicubic",     !flip_y),
        m_spline16   (8.0, 10.0+40,  "spline16",    !flip_y),
        m_spline36   (8.0, 10.0+60,  "spline36",    !flip_y),
        m_sinc36     (8.0, 10.0+80,  "sinc36",      !flip_y),
        m_blackman36 (8.0, 10.0+100, "blackman36",  !flip_y),
        m_sinc64     (8.0, 10.0+120, "sinc64",      !flip_y),
        m_blackman64 (8.0, 10.0+140, "blackman64",  !flip_y),
        m_sinc100    (8.0, 10.0+160, "sinc100",     !flip_y),
        m_blackman100(8.0, 10.0+180, "blackman100", !flip_y),
        m_sinc144    (8.0, 10.0+200, "sinc144",     !flip_y),
        m_blackman144(8.0, 10.0+220, "blackman144", !flip_y),
        m_sinc196    (8.0, 10.0+240, "sinc196",     !flip_y),
        m_blackman196(8.0, 10.0+260, "blackman196", !flip_y),
        m_sinc256    (8.0, 10.0+280, "sinc256",     !flip_y),
        m_blackman256(8.0, 10.0+300, "blackman256", !flip_y),
        m_num_filters(0)
    {
        m_filters[m_num_filters++] = &m_bilinear;
        m_filters[m_num_filters++] = &m_bicubic;
        m_filters[m_num_filters++] = &m_spline16;
        m_filters[m_num_filters++] = &m_spline36;
        m_filters[m_num_filters++] = &m_sinc36;
        m_filters[m_num_filters++] = &m_blackman36;
        m_filters[m_num_filters++] = &m_sinc64;
        m_filters[m_num_filters++] = &m_blackman64;
        m_filters[m_num_filters++] = &m_sinc100;
        m_filters[m_num_filters++] = &m_blackman100;
        m_filters[m_num_filters++] = &m_sinc144;
        m_filters[m_num_filters++] = &m_blackman144;
        m_filters[m_num_filters++] = &m_sinc196;
        m_filters[m_num_filters++] = &m_blackman196;
        m_filters[m_num_filters++] = &m_sinc256;
        m_filters[m_num_filters++] = &m_blackman256;

        unsigned i = 0;

        m_filter_func[i++] = &m_filter_bilinear;
        m_filter_func[i++] = &m_filter_bicubic;
        m_filter_func[i++] = &m_filter_spline16;
        m_filter_func[i++] = &m_filter_spline36;
        m_filter_func[i++] = &m_filter_sinc36;
        m_filter_func[i++] = &m_filter_blackman36;
        m_filter_func[i++] = &m_filter_sinc64;
        m_filter_func[i++] = &m_filter_blackman64;
        m_filter_func[i++] = &m_filter_sinc100;
        m_filter_func[i++] = &m_filter_blackman100;
        m_filter_func[i++] = &m_filter_sinc144;
        m_filter_func[i++] = &m_filter_blackman144;
        m_filter_func[i++] = &m_filter_sinc196;
        m_filter_func[i++] = &m_filter_blackman196;
        m_filter_func[i++] = &m_filter_sinc256 ;
        m_filter_func[i++] = &m_filter_blackman256;

        for(i = 0; i < m_num_filters; i++)
        {
            add_ctrl(*m_filters[i]);
        }
    }

    virtual ~the_application()
    {
    }

    virtual void on_draw()
    {
        typedef agg::pixfmt_bgr24 pixfmt; 
        typedef agg::renderer_base<pixfmt> renderer_base;
        typedef agg::renderer_scanline_p_solid<renderer_base> renderer_solid;
       
        pixfmt pixf(rbuf_window());
        renderer_base rb(pixf);
        renderer_solid rs(rb);

        rb.clear(agg::rgba(1.0, 1.0, 1.0));
        agg::rasterizer_scanline_aa<> ras;
        agg::scanline_p8 sl;

        double x_start = 125.0;
        double x_end   = initial_width() - 15.0;
        double y_start = 10.0;
        double y_end   = initial_height() - 10.0;

        unsigned i;

        agg::path_storage p;
        agg::conv_stroke<agg::path_storage> pl(p);
        agg::conv_transform<agg::conv_stroke<agg::path_storage> > tr(pl, trans_affine_resizing());

        for(i = 0; i <= 16; i++)
        {
            double x = x_start + (x_end - x_start) * i / 16.0;
            p.remove_all();
            p.move_to(x+0.5, y_start);
            p.line_to(x+0.5, y_end);
            ras.add_path(tr);
            rs.color(agg::rgba8(0, 0, 0, i == 8 ? 255 : 100));
            ras.render(sl, rs);
        }

        double ys = y_start + (y_end - y_start) / 6.0;

        p.remove_all();
        p.move_to(x_start, ys);
        p.line_to(x_end,   ys);
        ras.add_path(tr);
        rs.color(agg::rgba8(0, 0, 0));
        ras.render(sl, rs);

        rs.color(agg::rgba8(100, 0, 0));

        pl.width(2.0);
        
        for(i = 0; i < m_num_filters; i++)
        {
            if(m_filters[i]->status())
            {
                unsigned j;

                double dy = y_end - ys;

                double xs = (x_end + x_start)/2.0 - (m_filter_func[i]->dimension() * (x_end - x_start) / 32.0);
                double dx = (x_end - x_start) * m_filter_func[i]->dimension() / 16;

                p.remove_all();
                p.move_to(xs+0.5, ys + dy * m_filter_func[i]->weight_array_dbl()[0]);
                for(j = 1; j < m_filter_func[i]->dimension() * 256; j++)
                {
                    p.line_to(xs + dx * j / (m_filter_func[i]->dimension() * 256) + 0.5,
                              ys + dy * m_filter_func[i]->weight_array_dbl()[j]);
                }
                ras.add_path(tr);
                ras.render(sl, rs);
            }
        }

        for(i = 0; i < m_num_filters; i++)
        {
            ras.render_ctrl(sl, rs, *m_filters[i]);
        }
    }
};







int agg_main(int argc, char* argv[])
{
    the_application app(agg::pix_format_bgr24, flip_y);
    app.caption("Image filters' shape comparison");

    if(app.init(780, 330, agg::window_resize))
    {
        return app.run();
    }
    return 0;
}


