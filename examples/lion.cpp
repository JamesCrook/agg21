#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "agg_basics.h"
#include "agg_rendering_buffer.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_scanline_p.h"
#include "agg_renderer_scanline.h"
#include "agg_path_storage.h"
#include "agg_vertex_iterator.h"
#include "agg_conv_transform.h"
#include "agg_bounding_rect.h"
#include "ctrl/agg_slider_ctrl.h"
#include "platform/agg_platform_support.h"

#define AGG_BGR24 
//#define AGG_RGB24
//#define AGG_BGRA32 
//#define AGG_RGBA32 
//#define AGG_ARGB32 
//#define AGG_ABGR32
//#define AGG_RGB565
//#define AGG_RGB555
#include "pixel_formats.h"

enum { flip_y = true };

agg::rasterizer_scanline_aa<> g_rasterizer;
agg::scanline_p8  g_scanline;
agg::path_storage g_path;
agg::rgba8        g_colors[100];
unsigned          g_path_idx[100];
unsigned          g_npaths = 0;
double            g_x1 = 0;
double            g_y1 = 0;
double            g_x2 = 0;
double            g_y2 = 0;
double            g_base_dx = 0;
double            g_base_dy = 0;
double            g_angle = 0;
double            g_scale = 1.0;
double            g_skew_x = 0;
double            g_skew_y = 0;
int               g_nclick = 0;

unsigned parse_lion(agg::path_storage& ps, agg::rgba8* colors, unsigned* path_idx);
void parse_lion()
{
    g_npaths = parse_lion(g_path, g_colors, g_path_idx);
    agg::bounding_rect(g_path, g_path_idx, 0, g_npaths, &g_x1, &g_y1, &g_x2, &g_y2);
    g_base_dx = (g_x2 - g_x1) / 2.0;
    g_base_dy = (g_y2 - g_y1) / 2.0;
}



class the_application : public agg::platform_support
{
    agg::slider_ctrl<agg::rgba8> m_alpha_slider;

public:
    typedef agg::renderer_base<pixfmt> renderer_base;
    typedef agg::renderer_scanline_p_solid<renderer_base> renderer_solid;

    the_application(agg::pix_format_e format, bool flip_y) :
        agg::platform_support(format, flip_y),
        m_alpha_slider(5, 5, 150, 12, !flip_y)
    {
        parse_lion();
        add_ctrl(m_alpha_slider);
        m_alpha_slider.no_transform();
        m_alpha_slider.label("Alpha%3.2f");
    }

    virtual void on_resize(int cx, int cy)
    {
        pixfmt pf(rbuf_window());
        renderer_base r(pf);
        r.clear(agg::rgba(1, 1, 1));
    }

    virtual void on_draw()
    {
        int width = rbuf_window().width();
        int height = rbuf_window().height();

        unsigned i;
        unsigned alpha = unsigned(m_alpha_slider.value() * 255.0);
        for(i = 0; i < g_npaths; i++)
        {
           g_colors[i].a = (agg::int8u)alpha;
        }

        pixfmt pixf(rbuf_window());
        renderer_base rb(pixf);
        renderer_solid r(rb);

        agg::trans_affine mtx;
        mtx *= agg::trans_affine_translation(-g_base_dx, -g_base_dy);
        mtx *= agg::trans_affine_scaling(g_scale, g_scale);
        mtx *= agg::trans_affine_rotation(g_angle + agg::pi);
        mtx *= agg::trans_affine_skewing(g_skew_x/1000.0, g_skew_y/1000.0);
        mtx *= agg::trans_affine_translation(width/2, height/2);

        // This code renders the lion:

        // Variant with template converter classes - static pipeline
        //-------------------------------
        agg::conv_transform<agg::path_storage, agg::trans_affine> trans(g_path, mtx);
        //-------------------------------


        // Variant with static pipeline and the vertex source adaptor that
        // uses path_storage::const_iterator. 
        //-------------------------------
        //typedef agg::vertex_source_adaptor_with_id<agg::path_storage> source;
        //source src(g_path);
        //typedef agg::conv_transform<source, agg::trans_affine> transform;
        //transform trans(src, mtx);

        g_rasterizer.render_all_paths(g_scanline, r, trans, g_colors, g_path_idx, g_npaths);
        g_rasterizer.render_ctrl(g_scanline, r, m_alpha_slider);
    }


    void transform(double width, double height, double x, double y)
    {
        x -= width / 2;
        y -= height / 2;
        g_angle = atan2(y, x);
        g_scale = sqrt(y * y + x * x) / 100.0;
    }


    virtual void on_mouse_button_down(int x, int y, unsigned flags)
    {
        if(flags & agg::mouse_left)
        {
            int width = rbuf_window().width();
            int height = rbuf_window().height();
            transform(width, height, x, y);
            force_redraw();
        }

        if(flags & agg::mouse_right)
        {
            g_skew_x = x;
            g_skew_y = y;
            force_redraw();
        }
    }


    virtual void on_mouse_move(int x, int y, unsigned flags)
    {
        on_mouse_button_down(x, y, flags);
    }

};






int agg_main(int argc, char* argv[])
{
    the_application app(pix_format, flip_y);
    app.caption("AGG Example. Lion");

    if(app.init(512, 400, agg::window_resize))
    {
        return app.run();
    }
    return 1;
}






