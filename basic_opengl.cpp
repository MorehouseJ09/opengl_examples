#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <pic.h>

// create vertices of cube about the origin point
GLfloat vertices[8][3] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}};

// now assign the proper colors to the different vertices
// these colors are just rgb
GLfloat colors[8][3] = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};

// reshape callback -- set the project and viewport -- preserver the aspect ratio etc
void myReshape(int w, int h) {

	GLfloat aspect = (GLfloat) w / (GLfloat) h;

	// set the viewport
	glViewport(0, 0, w, h);

	//  
	glMatrixMode(GL_PROJECTION);
	// 
	glLoadIdentity();

	if (w <= h) //aspect <= 1
		glOrtho(-2.0, 2.0, -2.0/aspect, 2.0/aspect, -10.0, 10.0);

	else //otherwise aspect > 1
		glOrtho(-2.0 * aspect, 2.0 * aspect, -2.0, 2.0, -10.0, 10.0);

	// end gl matrix mode?
	glMatrixMode(GL_MODELVIEW);
}

//display callback -- clear rotate, draw flush and swap
GLfloat theta[3] = {0.0, 0.0, 0.0};

// drawing a face -- use form of primitives and attributes
void face(int a, int b, int c, int d) {

	glBegin(GL_POLYGON);

	// begin the drawing the faces
	// draw the colors of this particular element
	glColor3fv(colors[a]);
	// initialize the vertex
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]); 
	glVertex3fv(vertices[b]); 
	glColor3fv(colors[c]); 
	glVertex3fv(vertices[c]); 
	glColor3fv(colors[d]); 
	glVertex3fv(vertices[d]);

	// end gl call
	glEnd();
}

// draw facess
// call face (a,b,c,d) with vertex index
// orient consistently throughout
void colorcube(void) {



	face(0,3,2,1);
	face(2,3,7,6);
	face(0,4,7,3);
	face(1,2,6,5);
	face(4,5,6,7);
	face(0,1,5,4);
}


// display caller
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	colorcube();
	glutSwapBuffers();
}

// animation -- set the idle callback

GLfloat delta = 2.0;
GLint axis = 2;
void spinCube() {

	//spin the cube delta degrees about selected axis
	theta[axis] += delta;

	// normalize degrees
	if (theta[axis] > 360) theta[axis] -= 360.0;

	// display result of the change
	glutPostRedisplay();

}

// Change axis of rotation -- mouse callback
void mouse(int btn, int state, int x, int y) {

	// check if left button and make the axis zero
	if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) 
			axis = 0;

	// check if middle button
	if ((btn == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN)) 
			axis = 1;

	// check if the right button is clicked
	if ((btn == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) 
			axis = 2;
}

// toggle rotation / exit -- listen for keyboard callback
void keyboard(unsigned char key, int x, int y) {

	bool stop;

	if (key == 'q' || key == 'Q') 
		exit(0);

	if (key == ' ')
		stop = !stop;

	if (stop)
		glutIdleFunc(NULL);

	else 
		glutIdleFunc(spinCube);
}


// initialize the application
int main(int argc, char ** argv) {

	glutInit(&argc, argv);

	//enable double buffering for smoother animation
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	// Install callbacks, create teh window and install all the proper callbacks 
	glutInitWindowSize(500, 500);

	// name the title
	glutCreateWindow("Cube Demo");

	// initialize the various functions for open gl ... are these meta programmed functions or passed pointers?
	glutReshapeFunc(myReshape);

	// pass in a display function -- this shows the display of the entire element?
	glutDisplayFunc(display);

	// pass in an idling function to open gl
	glutIdleFunc(spinCube);

	// pass the mouse function to openGL
	glutMouseFunc(mouse);

	// pass a keyboard function to opengl event loop
	glutKeyboardFunc(keyboard);

	// enable the depth testing etc
	glEnable(GL_DEPTH_TEST);

	// enter the main event loop
	glutMainLoop();
	return(0);
}