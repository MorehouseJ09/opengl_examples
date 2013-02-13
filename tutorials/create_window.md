http://ogldev.atspace.co.uk/www/tutorial01/tutorial01.html

OpenGL spec doesn't specify any API in order to create and manipulate windows. Modern windowing systems that support OpenGL include a sub-system that binds between an OpenGL context and the windowing system. GLUT is this library that we use on mac / linux generally. 

GLUT provides a simplified API for window management as well as event handling, IO control and a few other services 

Source Walkthru
=

Initializes GLUT 
passing -sync and -gldebug are passed to glut	
-gldebug stops the asynchronouse nature of X and automatically checks for GL errors / displays them

	glutInit(&argc, argv)
	// can pass in -sync or -gldebug

GLUT_DOUBLE enables double buffering

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA)

configure glut options, double buffering and use rgb color schema 

double buffering = drawing to a background buffer while another buffer is visible

specify a function for running the program

	glutDisplayFunc(renderSceneCB)
	//use one callback to do the rendering of one frame -- this is continuously called by the GLUT internal loop

since we are working in a windowing system, most of the interaction with the running program occurs via event callback functions. GLUT takes care of interacting with the underlying windowing system and provides us with a few callback options


OpenGL State
=

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f)

OpenGL state is the concept behind rendering complex tasks
Cannot be treated as a function call that recieves a few parameters
Need to specify shaders, buffers, and various flags that effect how rendering will take place
Want to keep the same configuration across multiple rendering operations
Thus you set flags and values in the OpenGL state machine and the rendering calls themselves are usually limited to the few parameters that revolve around the number of vertices to draw and their starting offset
Once you call a single state change, that change remains intact and is used until it is overwritten by another 

ClearColor is what is used to draw the screen between frames when clearing all of the elements
Color has four channels (RGBA) and it is specified as a normal value between 0.0 and 1.0

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f)

Call to pass control to GLUT which will begin its own internal loop. This loop listens to events from the windowing system and passes them via callbacks that are configured	
GLUT will only call the function we registered as a display callback RenderSceneCB to give us a chance to render the frame

	glutMainLoop()

	glClear(GL_COLOR_BUFFER_BIT)
	glutSwapBuffers()

Only thing we do in our render function is to clear the framebuffer. The second call tells GLUT to swap the rol of the backbuffer and the frontbuffer. 



			



