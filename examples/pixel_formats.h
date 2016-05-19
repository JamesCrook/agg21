#ifndef PIXEL_FORMATS_INCLUDED
#define PIXEL_FORMATS_INCLUDED

#if defined(AGG_GRAY8)

#include "agg_pixfmt_gray8.h"
#define pix_format agg::pix_format_gray8
typedef agg::pixfmt_gray8 pixfmt;
typedef agg::gray8 color_type;

#elif defined(AGG_BGR24)

#include "agg_pixfmt_rgb24.h"
#define pix_format agg::pix_format_bgr24
typedef agg::pixfmt_bgr24 pixfmt;
typedef agg::rgba8 color_type;
typedef agg::order_bgr24 component_order;

#elif defined(AGG_RGB24)

#include "agg_pixfmt_rgb24.h"
#define pix_format agg::pix_format_rgb24
typedef agg::pixfmt_rgb24 pixfmt;
typedef agg::rgba8 color_type;
typedef agg::order_rgb24 component_order;

#elif defined(AGG_BGRA32)

#include "agg_pixfmt_rgba32.h"
#define pix_format agg::pix_format_bgra32
typedef agg::pixfmt_bgra32 pixfmt;
typedef agg::rgba8 color_type;
typedef agg::order_bgra32 component_order;

#elif defined(AGG_RGBA32)

#include "agg_pixfmt_rgba32.h"
#define pix_format agg::pix_format_rgba32
typedef agg::pixfmt_rgba32 pixfmt;
typedef agg::rgba8 color_type;
typedef agg::order_rgba32 component_order;

#elif defined(AGG_ARGB32)

#include "agg_pixfmt_rgba32.h"
#define pix_format agg::pix_format_argb32
typedef agg::pixfmt_argb32 pixfmt;
typedef agg::rgba8 color_type;
typedef agg::order_argb32 component_order;

#elif defined(AGG_ABGR32)

#include "agg_pixfmt_rgba32.h"
#define pix_format agg::pix_format_abgr32
typedef agg::pixfmt_abgr32 pixfmt;
typedef agg::rgba8 color_type;
typedef agg::order_argb32 component_order;

#elif defined(AGG_RGB565)

#include "agg_pixfmt_rgb565.h"
#define pix_format agg::pix_format_rgb565
typedef agg::pixfmt_rgb565 pixfmt;
typedef agg::rgba8 color_type;

#elif defined(AGG_RGB555)

#include "agg_pixfmt_rgb555.h"
#define pix_format agg::pix_format_rgb555
typedef agg::pixfmt_rgb555 pixfmt;
typedef agg::rgba8 color_type;

#else
#error Please define pixel format: \
AGG_GRAY8, AGG_BGR24, AGG_RGB24, \
AGG_BGRA32, AGG_RGBA32, AGG_ARGB32, \
AGG_ABGR32, AGG_RGB565, or AGG_RGB555
#endif

#endif
