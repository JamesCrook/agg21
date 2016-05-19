#include <math.h>
#include <stdio.h>
#include "agg_basics.h"
#include "agg_rendering_buffer.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_conv_stroke.h"
#include "agg_conv_dash.h"
#include "agg_conv_curve.h"
#include "agg_conv_contour.h"
#include "agg_conv_smooth_poly1.h"
#include "agg_conv_marker.h"
#include "agg_arrowhead.h"
#include "agg_vcgen_markers_term.h"
#include "agg_scanline_u.h"
#include "agg_renderer_scanline.h"
#include "agg_pixfmt_rgb24.h"
#include "ctrl/agg_slider_ctrl.h"
#include "ctrl/agg_rbox_ctrl.h"
#include "ctrl/agg_cbox_ctrl.h"
#include "platform/agg_platform_support.h"


enum { flip_y = true };



class the_application : public agg::platform_support
{
    double m_x[3];
    double m_y[3];
    double m_dx;
    double m_dy;
    int    m_idx;
    agg::rbox_ctrl<agg::rgba8>   m_cap;
    agg::slider_ctrl<agg::rgba8> m_width;
    agg::slider_ctrl<agg::rgba8> m_smooth;
    agg::cbox_ctrl<agg::rgba8>   m_close;
    agg::cbox_ctrl<agg::rgba8>   m_even_odd;


public:
    the_application(agg::pix_format_e format, bool flip_y) :
        agg::platform_support(format, flip_y),
        m_idx(-1),
        m_cap(10.0, 10.0, 130.0, 80.0, !flip_y),
        m_width(130 + 10.0, 10.0 + 4.0, 130 + 150.0, 10.0 + 8.0 + 4.0, !flip_y),
        m_smooth(130 + 150.0 + 10.0, 10.0 + 4.0, 500 - 10.0, 10.0 + 8.0 + 4.0, !flip_y),
        m_close(130 + 10.0, 10.0 + 4.0 + 16.0,    "Close Polygons", !flip_y),
        m_even_odd(130 + 150.0 + 10.0, 10.0 + 4.0 + 16.0, "Even-Odd Fill", !flip_y)
    {
        m_x[0] = 57  + 100; m_y[0] = 60;
        m_x[1] = 369 + 100; m_y[1] = 170;
        m_x[2] = 143 + 100; m_y[2] = 310;

        add_ctrl(m_cap);
        m_cap.add_item("Butt Cap");
        m_cap.add_item("Square Cap");
        m_cap.add_item("Round Cap");
        m_cap.cur_item(0);
        m_cap.no_transform();

        add_ctrl(m_width);
        m_width.range(0.0, 10.0);
        m_width.value(3.0);
        m_width.label("Width=%1.2f");
        m_width.no_transform();

        add_ctrl(m_smooth);
        m_smooth.range(0.0, 2.0);
        m_smooth.value(1.0);
        m_smooth.label("Smooth=%1.2f");
        m_smooth.no_transform();

        add_ctrl(m_close);
        m_close.no_transform();

        add_ctrl(m_even_odd);
        m_even_odd.no_transform();
    }

    virtual void on_init()
    {
    }

    virtual void on_draw()
    {
        typedef agg::renderer_base<agg::pixfmt_bgr24> ren_base;
        typedef agg::renderer_scanline_u_solid<ren_base> renderer;

        agg::pixfmt_bgr24 pixf(rbuf_window());
        ren_base renb(pixf);
        renderer ren(renb);
        renb.clear(agg::rgba(1, 1, 1));

        agg::rasterizer_scanline_aa<> ras;
        agg::scanline_u8 sl;

        agg::vcgen_stroke::line_cap_e cap = agg::vcgen_stroke::butt_cap;
        if(m_cap.cur_item() == 1)   cap = agg::vcgen_stroke::square_cap;
        if(m_cap.cur_item() == 2)   cap = agg::vcgen_stroke::round_cap;

        agg::path_storage path;

        path.move_to(m_x[0], m_y[0]);
        path.line_to(m_x[1], m_y[1]);
        path.line_to((m_x[0]+m_x[1]+m_x[2]) / 3.0, (m_y[0]+m_y[1]+m_y[2]) / 3.0);
        path.line_to(m_x[2], m_y[2]);
        if(m_close.status()) path.close_polygon();

        path.move_to((m_x[0] + m_x[1]) / 2, (m_y[0] + m_y[1]) / 2);
        path.line_to((m_x[1] + m_x[2]) / 2, (m_y[1] + m_y[2]) / 2);
        path.line_to((m_x[2] + m_x[0]) / 2, (m_y[2] + m_y[0]) / 2);
        if(m_close.status()) path.close_polygon();

        if(m_even_odd.status()) ras.filling_rule(agg::fill_even_odd);

        // (1)
        ras.add_path(path);
        ren.color(agg::rgba(0.7, 0.5, 0.1, 0.5));
        ras.render(sl, ren);
        // (1)

        // Start of (2, 3, 4)
        agg::conv_smooth_poly1<agg::path_storage> smooth(path);
        smooth.smooth_value(m_smooth.value());

        // (2)
        ras.add_path(smooth);
        ren.color(agg::rgba(0.1, 0.5, 0.7, 0.1));
        ras.render(sl, ren);
        // (2)


        // (3)
        agg::conv_stroke<agg::conv_smooth_poly1<agg::path_storage> > smooth_outline(smooth);
        ras.add_path(smooth_outline);
        ren.color(agg::rgba(0.0, 0.6, 0.0, 0.8));
        ras.render(sl, ren);
        // (3) 

        // (4)
        agg::conv_curve<agg::conv_smooth_poly1<agg::path_storage> > curve(smooth);
        agg::conv_dash<agg::conv_curve<agg::conv_smooth_poly1<agg::path_storage> >, agg::vcgen_markers_term> dash(curve);
        agg::conv_stroke<agg::conv_dash<agg::conv_curve<agg::conv_smooth_poly1<agg::path_storage> >, agg::vcgen_markers_term> > stroke(dash);
        stroke.line_cap(cap);
        stroke.width(m_width.value());

        double k = ::pow(m_width.value(), 0.7);

        agg::arrowhead ah;
                              ah.head(4 * k, 4   * k, 3 * k, 2 * k);
        if(!m_close.status()) ah.tail(1 * k, 1.5 * k, 3 * k, 5 * k);

        agg::conv_marker<agg::vcgen_markers_term, agg::arrowhead> arrow(dash.markers(), ah);

        dash.add_dash(20.0, 5.0);
        dash.add_dash(5.0, 5.0);
        dash.add_dash(5.0, 5.0);
        dash.dash_start(10);

        ras.add_path(stroke);
        ras.add_path(arrow);
        ren.color(agg::rgba(0.0, 0.0, 0.0));
        ras.render(sl, ren);
        // (4)


        ras.filling_rule(agg::fill_non_zero);
        ras.render_ctrl(sl, ren, m_cap);
        ras.render_ctrl(sl, ren, m_width);
        ras.render_ctrl(sl, ren, m_smooth);
        ras.render_ctrl(sl, ren, m_close);
        ras.render_ctrl(sl, ren, m_even_odd);
    }


    virtual void on_mouse_button_down(int x, int y, unsigned flags)
    {
        if(flags & agg::mouse_left)
        {
            unsigned i;
            for (i = 0; i < 3; i++)
            {
                if(sqrt( (x-m_x[i]) * (x-m_x[i]) + (y-m_y[i]) * (y-m_y[i]) ) < 20.0)
                {
                    m_dx = x - m_x[i];
                    m_dy = y - m_y[i];
                    m_idx = i;
                    break;
                }
            }
            if(i == 3)
            {
                if(agg::point_in_triangle(m_x[0], m_y[0], 
                                          m_x[1], m_y[1],
                                          m_x[2], m_y[2],
                                          x, y))
                {
                    m_dx = x - m_x[0];
                    m_dy = y - m_y[0];
                    m_idx = 3;
                }

            }
        }
    }


    virtual void on_mouse_move(int x, int y, unsigned flags)
    {
        if(flags & agg::mouse_left)
        {
            if(m_idx == 3)
            {
                double dx = x - m_dx;
                double dy = y - m_dy;
                m_x[1] -= m_x[0] - dx;
                m_y[1] -= m_y[0] - dy;
                m_x[2] -= m_x[0] - dx;
                m_y[2] -= m_y[0] - dy;
                m_x[0] = dx;
                m_y[0] = dy;
                force_redraw();
                return;
            }

            if(m_idx >= 0)
            {
                m_x[m_idx] = x - m_dx;
                m_y[m_idx] = y - m_dy;
                force_redraw();
            }
        }
        else
        {
            on_mouse_button_up(x, y, flags);
        }
    }

    virtual void on_mouse_button_up(int x, int y, unsigned flags)
    {
        m_idx = -1;
    }

    
    virtual void on_key(int x, int y, unsigned key, unsigned flags)
    {
        double dx = 0;
        double dy = 0;
        switch(key)
        {
        case agg::key_left:  dx = -0.1; break;
        case agg::key_right: dx =  0.1; break;
        case agg::key_up:    dy =  0.1; break;
        case agg::key_down:  dy = -0.1; break;
        }
        m_x[0] += dx;
        m_y[0] += dy;
        m_x[1] += dx;
        m_y[1] += dy;
        force_redraw();
    }

};



int agg_main(int argc, char* argv[])
{
    the_application app(agg::pix_format_bgr24, flip_y);
    app.caption("AGG Example. Line Join");

    if(app.init(500, 330, 0))
    {
        return app.run();
    }
    return 1;
}


