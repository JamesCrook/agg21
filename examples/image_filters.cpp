#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "agg_rendering_buffer.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_ellipse.h"
#include "agg_trans_affine.h"
#include "agg_conv_transform.h"
#include "agg_scanline_u.h"
#include "agg_scanline_p.h"
#include "agg_renderer_scanline.h"
#include "agg_span_image_filter_rgba32.h"
#include "agg_span_interpolator_linear.h"
#include "ctrl/agg_slider_ctrl.h"
#include "ctrl/agg_rbox_ctrl.h"
#include "ctrl/agg_cbox_ctrl.h"
#include "platform/agg_platform_support.h"

enum { flip_y = true };



class the_application : public agg::platform_support
{
    agg::slider_ctrl<agg::rgba8> m_angle;
    agg::slider_ctrl<agg::rgba8> m_step;
    agg::rbox_ctrl<agg::rgba8>   m_filters;
    agg::cbox_ctrl<agg::rgba8>   m_run;
    agg::cbox_ctrl<agg::rgba8>   m_refresh;

    double  m_cur_angle;
    int     m_cur_filter;
    int     m_num_steps;
    double  m_num_pix;
    clock_t m_time1;
    clock_t m_time2;

public:
    the_application(agg::pix_format_e format, bool flip_y) :
        agg::platform_support(format, flip_y),
        m_angle(5,  5,    300, 12,    !flip_y),
        m_step (5,  5+15, 300, 12+15, !flip_y),
        m_filters(0.0, 30.0, 110.0, 215.0, !flip_y),
        m_run(8.0,    230.0, "RUN Test!", !flip_y),
        m_refresh(8.0, 265.0, "Refresh", !flip_y),
        m_cur_angle(0.0),
        m_cur_filter(1),
        m_num_steps(0),
        m_num_pix(0.0),
        m_time1(0),
        m_time2(0)
    {
        add_ctrl(m_angle);
        add_ctrl(m_step);
        add_ctrl(m_filters);
        add_ctrl(m_run);
        add_ctrl(m_refresh);
        m_angle.label("Angle=%3.2f");
        m_step.label("Step=%3.2f");
        m_angle.range(20.0, 360.0);
        m_angle.value(360.0);
        m_step.range(1.0, 10.0);
        m_step.value(5.0);

        m_filters.add_item("simple (NN)");
        m_filters.add_item("bilinear");
        m_filters.add_item("bicubic");
        m_filters.add_item("spline16");
        m_filters.add_item("spline36");
        m_filters.add_item("sinc64");
        m_filters.add_item("sinc144");
        m_filters.add_item("sinc256");
        m_filters.add_item("blackman64");
        m_filters.add_item("blackman144");
        m_filters.add_item("blackman256");
        m_filters.cur_item(1);

        m_filters.border_width(0, 0);
        m_filters.background_color(agg::rgba(0.0, 0.0, 0.0, 0.1));
        m_filters.text_size(8.0);
        m_filters.text_thickness(1.0);
    }

    virtual ~the_application()
    {
    }

    virtual void on_draw()
    {
//        double width = rbuf_window().width();
//        double height = rbuf_window().height();
    
        typedef agg::pixfmt_bgra32 pixfmt;
        typedef agg::renderer_base<pixfmt> renderer_base;
        typedef agg::renderer_scanline_p_solid<renderer_base> renderer_solid;

        pixfmt pixf(rbuf_window());
        renderer_base rb(pixf);
        renderer_solid rs(rb);

        rb.clear(agg::rgba(1.0, 1.0, 1.0));
        rb.copy_from(rbuf_img(0), 0, 110, 35);

        agg::rasterizer_scanline_aa<> ras;
        agg::scanline_p8 sl;

        char buf[64]; 
        sprintf(buf, "NSteps=%d", m_num_steps);
        agg::gsv_text t;
        t.start_point(10.0, 295.0);
        t.size(10.0);
        t.text(buf);

        agg::conv_stroke<agg::gsv_text> pt(t);
        pt.width(1.5);

        ras.add_path(pt);
        rs.color(agg::rgba8(0,0,0));
        ras.render(sl, rs);

        if(m_time1 != m_time2 && m_num_pix > 0.0)
        {
            sprintf(buf, "%3.2f Kpix/sec", m_num_pix / 
                                          1000.0 /
                                          (double(m_time2 - m_time1) / CLOCKS_PER_SEC));
            t.start_point(10.0, 310.0);
            t.text(buf);
            ras.add_path(pt);
            ras.render(sl, rs);
        }

        ras.render_ctrl(sl, rs, m_angle);
        ras.render_ctrl(sl, rs, m_step);
        ras.render_ctrl(sl, rs, m_filters);
        ras.render_ctrl(sl, rs, m_run);
        ras.render_ctrl(sl, rs, m_refresh);
    }



    void transform_image(double angle)
    {
        double width = rbuf_img(0).width();
        double height = rbuf_img(0).height();

        typedef agg::pixfmt_bgra32 pixfmt;
        typedef agg::renderer_base<pixfmt> renderer_base;

        pixfmt pixf(rbuf_img(0));
        renderer_base rb(pixf);

        rb.clear(agg::rgba(1.0, 1.0, 1.0));

        agg::rasterizer_scanline_aa<> ras;
        agg::scanline_u8 sl;
        agg::span_allocator<agg::rgba8> sa;

        agg::trans_affine src_mtx;
        src_mtx *= agg::trans_affine_translation(-width/2.0, -height/2.0);
        src_mtx *= agg::trans_affine_rotation(angle * agg::pi / 180.0);
        src_mtx *= agg::trans_affine_translation(width/2.0, height/2.0);

        agg::trans_affine img_mtx = src_mtx;
        img_mtx.invert();

        double r = width;
        if(height < r) r = height;

        r *= 0.5;
        r += 4.0;
        agg::ellipse ell(width  / 2.0, 
                         height / 2.0, 
                         r, r, 200);
        agg::conv_transform<agg::ellipse> tr(ell, src_mtx);

        m_num_pix += r * r * agg::pi;

        typedef agg::span_interpolator_linear<> interpolator_type;
        interpolator_type interpolator(img_mtx); 

        switch(m_filters.cur_item())
        {
        case 0:
            {
                typedef agg::span_image_filter_rgba32_nn<agg::order_bgra32,
                                                         interpolator_type> span_gen_type;
                typedef agg::renderer_scanline_u<renderer_base, span_gen_type> renderer_type;

                span_gen_type sg(sa, rbuf_img(1), agg::rgba(1,1,1,0), interpolator);
                renderer_type ri(rb, sg);
                ras.add_path(tr);
                ras.render(sl, ri);
            }
            break;

        case 1:
            {
                typedef agg::span_image_filter_rgba32_bilinear<agg::order_bgra32,
                                                               interpolator_type> span_gen_type;
                typedef agg::renderer_scanline_u<renderer_base, span_gen_type> renderer_type;

                span_gen_type sg(sa, rbuf_img(1), agg::rgba(1,1,1,0), interpolator);
                renderer_type ri(rb, sg);
                ras.add_path(tr);
                ras.render(sl, ri);
            }
            break;

//        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            {
                agg::image_filter_base* filter = 0;
                switch(m_filters.cur_item())
                {
                case 1:  filter = new agg::image_filter<agg::image_filter_bilinear>;    break; 
                case 2:  filter = new agg::image_filter<agg::image_filter_bicubic>;     break; 
                case 3:  filter = new agg::image_filter<agg::image_filter_spline16>;    break; 
                case 4:  filter = new agg::image_filter<agg::image_filter_spline36>;    break; 
                case 5:  filter = new agg::image_filter<agg::image_filter_sinc64>;      break; 
                case 6:  filter = new agg::image_filter<agg::image_filter_sinc144>;     break; 
                case 7:  filter = new agg::image_filter<agg::image_filter_sinc256>;     break; 
                case 8:  filter = new agg::image_filter<agg::image_filter_blackman64>;  break; 
                case 9:  filter = new agg::image_filter<agg::image_filter_blackman100>; break; 
                case 10: filter = new agg::image_filter<agg::image_filter_blackman256>; break; 
                }

                typedef agg::span_image_filter_rgba32<agg::order_bgra32,
                                                      interpolator_type> span_gen_type;
                typedef agg::renderer_scanline_u<renderer_base, span_gen_type> renderer_type;

                span_gen_type sg(sa, rbuf_img(1), agg::rgba(1,1,1,0), interpolator, *filter);
                renderer_type ri(rb, sg);
                ras.add_path(tr);
                ras.render(sl, ri);
                delete filter;

            }
            break;
        }

    }


    void on_ctrl_change()
    {
        if(m_run.status())
        {
            m_time1 = m_time2 = clock();
            m_num_pix = 0.0;
            wait_mode(false);
        }
        if(m_refresh.status() || m_filters.cur_item() != m_cur_filter)
        {
            m_time1 = m_time2 = clock();
            m_num_pix = 0.0;
            copy_img_to_img(1, 2);
            transform_image(0.0);
            m_refresh.status(false);
            m_cur_filter = m_filters.cur_item();
            m_num_steps = 0;
            force_redraw();
        }
    }

    void on_idle()
    {
        if(m_run.status())
        {
            if(m_cur_angle < m_angle.value())
            {
                m_cur_angle += m_step.value();
                copy_img_to_img(1, 0);
                transform_image(m_step.value());
                m_num_steps++;
            }
            else
            {
                m_cur_angle = 0.0;
                m_time2 = clock();
                wait_mode(true);
                m_run.status(false);
            }
            force_redraw();
        }
        else
        {
            wait_mode(true);
        }
    }


};







int agg_main(int argc, char* argv[])
{
    the_application app(agg::pix_format_bgra32, flip_y);
    app.caption("Image transformation filters comparison");

    const char* img_name = "spheres";
    if(argc >= 2) img_name = argv[1];
    if(!app.load_img(0, img_name)) 
    {
        char buf[256];
        if(strcmp(img_name, "spheres") == 0)
        {
            sprintf(buf, "File not found: %s%s. Download http://www.antigrain.com/%s%s\n"
                         "or copy it from another directory if available.",
                    img_name, app.img_ext(), img_name, app.img_ext());
        }
        else
        {
            sprintf(buf, "File not found: %s%s", img_name, app.img_ext());
        }
        app.message(buf);
        return 1;
    }

    app.copy_img_to_img(1, 0);
    app.copy_img_to_img(2, 0);
    app.transform_image(0.0);

    unsigned w = app.rbuf_img(0).width() + 110;
    unsigned h = app.rbuf_img(0).height() + 40;

    if(w < 305) w = 305;
    if(h < 325) h = 325;

    if(app.init(w, h, 0))
    {
        return app.run();
    }
    return 0;
}


