INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/gpc -I$(top_srcdir)/font_freetype `freetype-config --cflags` 

bin_PROGRAMS = agg_aa_demo agg_alpha_mask agg_alpha_mask2 agg_alpha_mask3 \
			   agg_bspline agg_circles agg_component_rendering agg_conv_contour \
			   agg_conv_dash_marker agg_conv_stroke agg_distortions agg_gamma_correction \
			   agg_gamma_ctrl agg_gouraud agg_gpc_test agg_gradients agg_graph_test \
			   agg_idea agg_image1 agg_image_alpha agg_image_filters agg_image_fltr_graph \
			   agg_image_perspective agg_image_transforms agg_lion agg_lion_lens \
			   agg_lion_outline agg_mol_view agg_multi_clip agg_pattern_fill \
			   agg_perspective agg_polymorphic_renderer agg_raster_text agg_rasterizers \
			   agg_rasterizers2 agg_rounded_rect agg_scanline_boolean agg_scanline_boolean2 \
			   agg_simple_blur agg_trans_polar agg_freetype_test

agg_aa_demo_SOURCES = aa_demo.cpp
agg_aa_demo_LDADD = $(top_builddir)/src/libagg.la \
					$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_alpha_mask_SOURCES = alpha_mask.cpp parse_lion.cpp
agg_alpha_mask_LDADD = $(top_builddir)/src/libagg.la \
					   $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_alpha_mask2_SOURCES = alpha_mask2.cpp parse_lion.cpp
agg_alpha_mask2_LDADD = $(top_builddir)/src/libagg.la \
						$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_alpha_mask3_SOURCES = alpha_mask3.cpp make_gb_poly.cpp make_arrows.cpp
agg_alpha_mask3_LDADD = $(top_builddir)/src/libagg.la \
						$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_bspline_SOURCES = bspline.cpp interactive_polygon.cpp
agg_bspline_LDADD = $(top_builddir)/src/libagg.la \
					$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_circles_SOURCES = circles.cpp
agg_circles_LDADD = $(top_builddir)/src/libagg.la \
					$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_component_rendering_SOURCES = component_rendering.cpp
agg_component_rendering_LDADD = $(top_builddir)/src/libagg.la \
								$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_conv_contour_SOURCES = conv_contour.cpp
agg_conv_contour_LDADD = $(top_builddir)/src/libagg.la \
						 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_conv_dash_marker_SOURCES = conv_dash_marker.cpp
agg_conv_dash_marker_LDADD = $(top_builddir)/src/libagg.la \
							 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_conv_stroke_SOURCES = conv_stroke.cpp
agg_conv_stroke_LDADD = $(top_builddir)/src/libagg.la \
						$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_distortions_SOURCES = distortions.cpp
agg_distortions_LDADD = $(top_builddir)/src/libagg.la \
						$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_gamma_correction_SOURCES = gamma_correction.cpp
agg_gamma_correction_LDADD = $(top_builddir)/src/libagg.la \
							 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_gamma_ctrl_SOURCES = gamma_ctrl.cpp
agg_gamma_ctrl_LDADD = $(top_builddir)/src/libagg.la \
					   $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_gouraud_SOURCES = gouraud.cpp
agg_gouraud_LDADD = $(top_builddir)/src/libagg.la \
					$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_gpc_test_SOURCES = gpc_test.cpp make_gb_poly.cpp make_arrows.cpp
agg_gpc_test_LDADD = $(top_builddir)/src/libagg.la \
					 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_gradients_SOURCES = gradients.cpp
agg_gradients_LDADD = $(top_builddir)/src/libagg.la \
					  $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_graph_test_SOURCES = graph_test.cpp
agg_graph_test_LDADD = $(top_builddir)/src/libagg.la \
					   $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_idea_SOURCES = idea.cpp
agg_idea_LDADD = $(top_builddir)/src/libagg.la \
				 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_image1_SOURCES = image1.cpp
agg_image1_LDADD = $(top_builddir)/src/libagg.la \
				   $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_image_alpha_SOURCES = image_alpha.cpp
agg_image_alpha_LDADD = $(top_builddir)/src/libagg.la \
						$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_image_filters_SOURCES = image_filters.cpp
agg_image_filters_LDADD = $(top_builddir)/src/libagg.la \
						  $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_image_fltr_graph_SOURCES = image_fltr_graph.cpp
agg_image_fltr_graph_LDADD = $(top_builddir)/src/libagg.la \
							 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_image_perspective_SOURCES = image_perspective.cpp interactive_polygon.cpp
agg_image_perspective_LDADD = $(top_builddir)/src/libagg.la \
							  $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_image_transforms_SOURCES = image_transforms.cpp parse_lion.cpp
agg_image_transforms_LDADD = $(top_builddir)/src/libagg.la \
							$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_lion_SOURCES = lion.cpp parse_lion.cpp
agg_lion_LDADD = $(top_builddir)/src/libagg.la \
				 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_lion_lens_SOURCES = lion_lens.cpp parse_lion.cpp
agg_lion_lens_LDADD = $(top_builddir)/src/libagg.la \
					  $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_lion_outline_SOURCES = lion_outline.cpp parse_lion.cpp
agg_lion_outline_LDADD = $(top_builddir)/src/libagg.la \
						 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_mol_view_SOURCES = mol_view.cpp
agg_mol_view_LDADD = $(top_builddir)/src/libagg.la \
					 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_multi_clip_SOURCES = multi_clip.cpp parse_lion.cpp
agg_multi_clip_LDADD = $(top_builddir)/src/libagg.la \
					   $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_pattern_fill_SOURCES = pattern_fill.cpp
agg_pattern_fill_LDADD = $(top_builddir)/src/libagg.la \
						 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_perspective_SOURCES = perspective.cpp parse_lion.cpp interactive_polygon.cpp
agg_perspective_LDADD = $(top_builddir)/src/libagg.la \
						$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_polymorphic_renderer_SOURCES = polymorphic_renderer.cpp
agg_polymorphic_renderer_LDADD = $(top_builddir)/src/libagg.la \
								 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_raster_text_SOURCES = raster_text.cpp
agg_raster_text_LDADD = $(top_builddir)/src/libagg.la \
						$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_rasterizers_SOURCES = rasterizers.cpp
agg_rasterizers_LDADD = $(top_builddir)/src/libagg.la \
						$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_rasterizers2_SOURCES = rasterizers2.cpp
agg_rasterizers2_LDADD = $(top_builddir)/src/libagg.la \
						 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_rounded_rect_SOURCES = rounded_rect.cpp
agg_rounded_rect_LDADD = $(top_builddir)/src/libagg.la \
						 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_scanline_boolean_SOURCES = scanline_boolean.cpp interactive_polygon.cpp
agg_scanline_boolean_LDADD = $(top_builddir)/src/libagg.la \
							 $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_scanline_boolean2_SOURCES = scanline_boolean2.cpp make_gb_poly.cpp make_arrows.cpp
agg_scanline_boolean2_LDADD = $(top_builddir)/src/libagg.la \
							  $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_simple_blur_SOURCES = simple_blur.cpp parse_lion.cpp
agg_simple_blur_LDADD = $(top_builddir)/src/libagg.la \
						$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_trans_polar_SOURCES = trans_polar.cpp
agg_trans_polar_LDADD = $(top_builddir)/src/libagg.la \
						$(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la

agg_freetype_test_SOURCES = freetype_test.cpp
agg_freetype_test_LDADD = $(top_builddir)/src/libagg.la \
						  $(top_builddir)/font_freetype/libaggfontfreetype.la \
						  $(top_builddir)/src/platform/$(AGG_PLATFORM)/libaggplatform$(AGG_PLATFORM).la
