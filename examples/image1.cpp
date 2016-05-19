#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "agg_rendering_buffer.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_ellipse.h"
#include "agg_trans_affine.h"
#include "agg_conv_transform.h"
#include "agg_span_image_filter_rgb24.h"
#include "agg_scanline_u.h"
#include "agg_renderer_scanline.h"
#include "agg_span_interpolator_linear.h"
#include "ctrl/agg_slider_ctrl.h"
#include "platform/agg_platform_support.h"

enum { flip_y = true };



class the_application : public agg::platform_support
{
    agg::slider_ctrl<agg::rgba8> m_angle;
    agg::slider_ctrl<agg::rgba8> m_scale;

public:
    the_application(agg::pix_format_e format, bool flip_y) :
        agg::platform_support(format, flip_y),
        m_angle(5,  5,    300, 12,    !flip_y),
        m_scale(5,  5+15, 300, 12+15, !flip_y)
    {
        add_ctrl(m_angle);
        add_ctrl(m_scale);
        m_angle.label("Angle=%3.2f");
        m_scale.label("Scale=%3.2f");
        m_angle.range(-180.0, 180.0);
        m_angle.value(0.0);
        m_scale.range(0.1, 5.0);
        m_scale.value(1.0);
    }

    virtual ~the_application()
    {
    }

    virtual void on_draw()
    {
        typedef agg::pixfmt_rgb24 pixfmt; 
        typedef agg::renderer_base<pixfmt> renderer_base;
        typedef agg::renderer_scanline_u_solid<renderer_base> renderer_solid;
       
        pixfmt pixf(rbuf_window());
        renderer_base rb(pixf);
        renderer_solid rs(rb);

        rb.clear(agg::rgba(1.0, 1.0, 1.0));

        agg::trans_affine src_mtx;
        src_mtx *= agg::trans_affine_translation(-initial_width()/2 - 10, -initial_height()/2 - 20 - 10);
        src_mtx *= agg::trans_affine_rotation(m_angle.value() * agg::pi / 180.0);
        src_mtx *= agg::trans_affine_scaling(m_scale.value());
        src_mtx *= agg::trans_affine_translation(initial_width()/2, initial_height()/2 + 20);
        src_mtx *= trans_affine_resizing();

        agg::trans_affine img_mtx;
        img_mtx *= agg::trans_affine_translation(-initial_width()/2 + 10, -initial_height()/2 + 20 + 10);
        img_mtx *= agg::trans_affine_rotation(m_angle.value() * agg::pi / 180.0);
        img_mtx *= agg::trans_affine_scaling(m_scale.value());
        img_mtx *= agg::trans_affine_translation(initial_width()/2, initial_height()/2 + 20);
        img_mtx *= trans_affine_resizing();
        img_mtx.invert();

        typedef agg::span_allocator<agg::rgba8> span_alloc_type;

        span_alloc_type sa;
        typedef agg::span_interpolator_linear<> interpolator_type;
        interpolator_type interpolator(img_mtx);


/*
        // Version without filtering (nearest neighbor)
        //------------------------------------------
        typedef agg::span_image_filter_rgb24_nn<agg::order_rgb24, 
                                                interpolator_type> span_gen_type;
        typedef agg::renderer_scanline_u<renderer_base, span_gen_type> renderer_type;

        span_gen_type sg(sa, 
                         rbuf_img(0), 
                         agg::rgba(0, 0.4, 0, 0.5),
                         interpolator);
        //------------------------------------------
*/



        // Version with "hardcoded" bilinear filter
        //------------------------------------------
        typedef agg::span_image_filter_rgb24_bilinear<agg::order_rgb24, 
                                                      interpolator_type> span_gen_type;
        typedef agg::renderer_scanline_u<renderer_base, span_gen_type> renderer_type;

        span_gen_type sg(sa, 
                         rbuf_img(0), 
                         agg::rgba(0, 0.4, 0, 0.5),
                         interpolator);
        //------------------------------------------



/*
        // Version with arbitrary filter
        //------------------------------------------
        typedef agg::span_image_filter_rgb24<agg::order_rgb24, 
                                             interpolator_type> span_gen_type;
        typedef agg::renderer_scanline_u<renderer_base, span_gen_type> renderer_type;

        agg::image_filter<agg::image_filter_spline36> filter;

        span_gen_type sg(sa, 
                         rbuf_img(0), 
                         agg::rgba(0, 0.4, 0, 0.5),
                         interpolator, 
                         filter);
        //------------------------------------------
*/


        renderer_type ri(rb, sg);

        agg::rasterizer_scanline_aa<> pf;
        agg::scanline_u8 sl;
        double r = initial_width();
        if(initial_height() - 60 < r) r = initial_height() - 60;
        agg::ellipse ell(initial_width()  / 2.0 + 10, 
                         initial_height() / 2.0 + 20 + 10, 
                         r / 2.0 + 16.0, 
                         r / 2.0 + 16.0, 200);


        agg::conv_transform<agg::ellipse> tr(ell, src_mtx);

        pf.add_path(tr);
        pf.render(sl, ri);

        pf.render_ctrl(sl, rs, m_angle);
        pf.render_ctrl(sl, rs, m_scale);
    }

};





int agg_main(int argc, char* argv[])
{
    the_application app(agg::pix_format_rgb24, flip_y);
    app.caption("Image Affine Transformations with filtering");

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

    if(app.init(app.rbuf_img(0).width() + 20, app.rbuf_img(0).height() + 40 + 20, agg::window_resize))
    {
        return app.run();
    }
    return 0;
}


