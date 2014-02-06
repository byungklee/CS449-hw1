#include <GL/glut.h>
#include <math.h>
#define PI 3.1415

void init() {
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,150.0);
}

void flag() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	int x,y;

	//TOP LEFT
	glBegin(GL_POLYGON);
	 	x=20;
	 	y=110;	 	
		glVertex2i(x,y);
		glVertex2i(x+30,y+30);
		glVertex2i(x+35,y+25);
		glVertex2i(x+5,y-5);
	glEnd();
	glBegin(GL_POLYGON);
	 	x=27;
	 	y=103; 	
		glVertex2i(x,y);
		glVertex2i(x+30,y+30);
		glVertex2i(x+35,y+25);
		glVertex2i(x+5,y-5);
	glEnd();
	glBegin(GL_POLYGON);
	 	x=34;
	 	y=96;	 	
		glVertex2i(x,y);
		glVertex2i(x+30,y+30);
		glVertex2i(x+35,y+25);
		glVertex2i(x+5,y-5);
	glEnd();

	//Bottom left
	glBegin(GL_POLYGON);
	 	x=20;
	 	y=40;	 	
		glVertex2i(x,y);
		glVertex2i(x+30,y-30);
		glVertex2i(x+35,y-25);
		glVertex2i(x+5,y+5);
	glEnd();
	glBegin(GL_POLYGON);
	 	x=27;
	 	y=47; 	
		glVertex2i(x,y);
		glVertex2i(x+12,y-12);
		glVertex2i(x+17,y-7);
		glVertex2i(x+5,y+5);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2i(x+12+6,y-12-6);
		glVertex2i(x+30,y-30);
		glVertex2i(x+35,y-25);
		glVertex2i(x+12+6+5,y-12-6+5);
	glEnd();
	glBegin(GL_POLYGON);
	 	x=34;
	 	y=54;	 	
		glVertex2i(x,y);
		glVertex2i(x+30,y-30);
		glVertex2i(x+35,y-25);
		glVertex2i(x+5,y+5);
	glEnd();

	//TOP right
	glBegin(GL_POLYGON);
	 	x=180;
	 	y=110;	 	
		glVertex2i(x,y);
		glVertex2i(x-12,y+12);
		glVertex2i(x-17,y+7);
		glVertex2i(x-5,y-5);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2i(x-12-6,y+12+6);
		glVertex2i(x-30,y+30);
		glVertex2i(x-35,y+25);
		glVertex2i(x-12-6-5, y+12+6-5);
	glEnd();
	glBegin(GL_POLYGON);
	 	x=173;
	 	y=103; 	
		glVertex2i(x,y);
		glVertex2i(x-30,y+30);
		glVertex2i(x-35,y+25);
		glVertex2i(x-5,y-5);
	glEnd();	
	glBegin(GL_POLYGON);
	 	x=166;
	 	y=96;	 	
		glVertex2i(x,y);
		glVertex2i(x-12,y+12);
		glVertex2i(x-17,y+7);
		glVertex2i(x-5,y-5);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2i(x-12-6,y+12+6);
		glVertex2i(x-30,y+30);
		glVertex2i(x-35,y+25);
		glVertex2i(x-12-6-5, y+12+6-5);
	glEnd();

	//Bottom Right		
	glBegin(GL_POLYGON);
		x=180;
		y=40;
		glVertex2i(x,y);
		glVertex2i(x-12,y-12);
		glVertex2i(x-17,y-7);
		glVertex2i(x-5,y+5);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2i(x-12-6, y-12-6);
		glVertex2i(x-30,y-30);
		glVertex2i(x-35,y-25);
		glVertex2i(x-12-6-5, y-12-6+5);
	glEnd();
	glBegin(GL_POLYGON);
		x=173;
		y=47;
		glVertex2i(x,y);
		glVertex2i(x-12,y-12);
		glVertex2i(x-17,y-7);
		glVertex2i(x-5,y+5);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2i(x-12-6, y-12-6);
		glVertex2i(x-30,y-30);
		glVertex2i(x-35,y-25);
		glVertex2i(x-12-6-5, y-12-6+5);
	glEnd();
	glBegin(GL_POLYGON);
		x=166;
		y=54;
		glVertex2i(x,y);
		glVertex2i(x-12,y-12);
		glVertex2i(x-17,y-7);
		glVertex2i(x-5,y+5);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2i(x-12-6, y-12-6);
		glVertex2i(x-30,y-30);
		glVertex2i(x-35,y-25);
		glVertex2i(x-12-6-5, y-12-6+5);
	glEnd();

	//Circle in the middle! Center: 100, 75
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
		for(int i = 0; i <= 180; i++) {
			glVertex2f(100 + 40 * cos(i*PI/180), 75 + 40 * sin(i*PI/180));
		}	
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
		for(int i = 180; i <= 360; i++) {
			glVertex2f(100 + 40 * cos(i*PI/180), 75 + 40 * sin(i*PI/180));
		}
	glEnd();
	glBegin(GL_POLYGON);
	for(int i = 0; i <= 180; i++) {
			glVertex2f(120 + 20 * cos(i*PI/180), 75 + 20 * sin(i*PI/180));
	}
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
	for(int i = 180; i<=360; i++) {
			glVertex2f(80 + 20 * cos(i*PI/180), 75 + 20 * sin(i*PI/180));
	}
	glEnd();
	glFlush();
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(400,300);
	glutCreateWindow("FLAG");
	init();
	glutDisplayFunc(flag);
	glutMainLoop();
	return 0;
}