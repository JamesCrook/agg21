# agg21

Maxim Shemanarev's "Antigrain Geometry Library", Version 2.1

#Uses

The antigrain library will do antialiased lines fast and beautifully.  At its core the scan line algorithms depend on antialiased font 
rendering code written by David Turner and collaborators for FreeType.  Those algorithms work exactly for two-colour antialiasing.  
When three colours meet at a pixel the pixel colour may not be perfect - but relatively few pixels are affected.  One literally edge case
is drawing a thin line over an existing boundary between regions.

Antialiased lines are essential for drawing tick marks at arbitrary spacing.  Without them you are forced to space them at whole pixel 
intervals, which then prevents continuous zooming.

Max's library gives a great deal of flexibility, but at a cost.  It uses templates for efficiency, and designing those correctly,  
so that they work on different platforms and with different colour buffers orders is fiddly.  

Using agg in wxWidgets we can get antialiasing where we want it, without paying the perfromance penalty of using 'wxGraphicContext'  
everywhere.  We can mix antialiassed code with regular wxWidgets code that draws at pixels boundaries on the same wxDC GDI context.
