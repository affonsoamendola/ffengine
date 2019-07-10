# TODO LIST

## Audio.cpp/hpp
	Make it work.
	Software Synthesizer.
	Play samples (.wav and others)
	Play Music (.ogg and others)

## Engine.cpp/hpp
	Better way of counting m_time.
	Does delta_time() actually work as intended?

## Engine_System.cpp/hpp
	Add base engine system functionalities
	Pointer list to other subsystems loaded?

## Graphics.cpp/hpp
	Can I just write directly to the framebuffer to gain some speed?
	Add font variants, change how m_default_font works, maybe turn it into an array of possible bitmapped fonts.
	Add drawing functions of simple shapes, like lines, triangles, rectangles, polygons
	Most draw functions use int x, and int y, make them use Point2's for consistency.

## GUI.cpp/hpp GUI_Elements.cpp/hpp
	Make drawing GUI_Object's children a task for the default GUI_Object Render function, and call it AFTER drawing the inherited object render.
	
	Make more GUI_Object types,
		Text boxes
		Buttons
		Scrolling panels
		Input textboxes
